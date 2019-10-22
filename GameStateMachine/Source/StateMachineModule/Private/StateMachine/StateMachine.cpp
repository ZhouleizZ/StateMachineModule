#include "StateMachine.h"
#include "SMMCommon.h"
/*----------------------------------------------------------------------------------------------------------------------*/
AbilityStateMachine::AbilityStateMachine(AStateMachineCharacter* InCharacter, EAbilityStateGroup InStateGroup)
	: OwnerCharacter(InCharacter)
	, StateGroup(InStateGroup)
	, CurrentState(nullptr)
{

}

AbilityStateMachine::~AbilityStateMachine()
{

}

void AbilityStateMachine::RegisterState(AbilityStateBase* State)
{
	return_if_nullptr(State);
	StateMap.Add(State->GetStateID(), State);
	State->SetOwnerCharacter(OwnerCharacter);
}

void AbilityStateMachine::UnregisterState(AbilityStateBase* State)
{
	return_if_nullptr(State);
	if (State == CurrentState)
	{
		if (OwnerCharacter->Role >= ROLE_AutonomousProxy)
		{
			CurrentState->Leave(nullptr);
			CurrentState = nullptr;

			OwnerCharacter->UpdateStateMutex();
		}
		else
		{
			CurrentState->SimulateLeave();
			CurrentState = nullptr;
		}
	}

	StateMap.Remove(State->GetStateID());
	State->SetOwnerCharacter(nullptr);
}

void AbilityStateMachine::Tick(float DeltaTime)
{
	if (OwnerCharacter->Role >= ROLE_AutonomousProxy)
	{
		UpdateBestState();
	}

	if (CurrentState)
	{
		if (OwnerCharacter->Role >= ROLE_AutonomousProxy)
		{
			CurrentState->Tick(DeltaTime);
		}
		else
		{
			CurrentState->SimulateTick(DeltaTime);
		}
	}
}

void AbilityStateMachine::UpdateBestState()
{
	bool NeedReselectState = true;
	if (CurrentState)
	{
		CurrentState->CalcPriority();
		//������һ���Ż����ж����̣������ǰ״̬�Ѿ���������ȼ�������Ա��״̬���ж�
		if (CurrentState->GetPriority() == EAbilityStatePriority_Must
			&& OwnerCharacter->CheckStateMutex(CurrentState->GetStateID()))
		{
			NeedReselectState = false;
		}
	}

	if (NeedReselectState)
	{
		TArray<AbilityStateBase*> SortArray;
		for (TMap<int32, AbilityStateBase*>::TIterator StateIt = StateMap.CreateIterator(); StateIt; ++StateIt)
		{
			AbilityStateBase* State = StateIt.Value();
			State->CalcPriority();
			if (State->GetPriority() > EAbilityStatePriority_None)
			{
				SortArray.Push(State);
			}
		}

		bool FoundBestState = false;
		if (SortArray.Num() > 0)
		{
			SortArray.Sort([](const AbilityStateBase& A, const AbilityStateBase& B) {return A.GetPriority() > B.GetPriority(); });

			for (int32 i = 0; i < SortArray.Num(); ++i)
			{
				AbilityStateBase* NewState = SortArray[i];
				if (OwnerCharacter->CheckStateMutex(NewState->GetStateID()) && NewState->CheckCanEnter())
				{
					if (NewState != CurrentState)
					{
						if (CurrentState != nullptr)
						{
							CurrentState->Leave(NewState);
						}

						AbilityStateBase* LastState = CurrentState;
						CurrentState = NewState;
						OwnerCharacter->UpdateCurrentStateIDs();

						NewState->Enter(LastState);

						OwnerCharacter->UpdateStateMutex();

						////״̬�ı��ˣ��˶�ϵͳ����Ҳ�ı��ˣ���Ҫ�������Ϳͻ����ƶ��������������򻺴���˶�֡�ڷ���˻��в�һ�µļ�����
						//if (OwnerCharacter->Role == ROLE_AutonomousProxy)
						//{
						//	OwnerCharacter->GameCharacterMovement->FlushServerMoves();
						//}
						//TODO  �˴���Ҫ����˼��
					}

					FoundBestState = true;
					break;
				}
			}
		}

		if (!FoundBestState)
		{
			if (CurrentState != nullptr)
			{
				CurrentState->Leave(nullptr);
				CurrentState = nullptr;
				OwnerCharacter->UpdateCurrentStateIDs();
				OwnerCharacter->UpdateStateMutex();
			}
		}
	}
}

void AbilityStateMachine::ChangeSimulatedState(int32 StateID)
{
	AbilityStateBase* NewState = StateMap.FindRef(StateID);
	if (nullptr == NewState)
		return;

	if (NewState == CurrentState)
		return;

	if (CurrentState)
	{
		CurrentState->SimulateLeave();
	}

	NewState->SimulateEnter();
	CurrentState = NewState;
}

void AbilityStateMachine::ResetState()
{
	if (OwnerCharacter->Role >= ROLE_AutonomousProxy)
	{
		if (CurrentState)
		{
			CurrentState->Leave(nullptr);
			CurrentState = nullptr;
		}
	}
}

int32 AbilityStateMachine::GetStateID()
{
	if (CurrentState)
	{
		return CurrentState->GetStateID();
	}
	return INDEX_NONE;
}
/*----------------------------------------------------------------------------------------------------------------------*/

UAbilityStateSystem::UAbilityStateSystem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UAbilityStateSystem::~UAbilityStateSystem()
{
	for (int32 i = 0; i < StateMachineList.Num(); ++i)
	{
		delete StateMachineList[i];
	}
	StateMachineList.Empty();
}

void UAbilityStateSystem::BindOwnerCharacter(class AStateMachineCharacter* OwnerActor)
{
	OwnerCharacter = OwnerActor;
}

void UAbilityStateSystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UAbilityStateSystem, CurrentStateIDs);
}

void UAbilityStateSystem::RegisterState(AbilityStateBase* State)
{
	for (int32 i = 0; i < StateMachineList.Num(); ++i)
	{
		if (StateMachineList[i]->GetStateGroup() == State->GetStateGroup())
		{
			StateMachineList[i]->RegisterState(State);
			return;
		}
	}

	AbilityStateMachine* NewMachine = new AbilityStateMachine(OwnerCharacter, State->GetStateGroup());
	NewMachine->RegisterState(State);

	//ȷ��״̬��������
	int32 InsertIndex = 0;
	for (InsertIndex = 0; InsertIndex < StateMachineList.Num(); ++InsertIndex)
	{
		if (NewMachine->GetStateGroup() < StateMachineList[InsertIndex]->GetStateGroup())
		{
			StateMachineList.Insert(NewMachine, InsertIndex);
			break;
		}
	}

	if (InsertIndex == StateMachineList.Num())
	{
		StateMachineList.Push(NewMachine);
	}
}

void UAbilityStateSystem::UnregisterState(AbilityStateBase* State)
{
	for (int32 i = 0; i < StateMachineList.Num(); ++i)
	{
		if (StateMachineList[i]->GetStateGroup() == State->GetStateGroup())
		{
			StateMachineList[i]->UnregisterState(State);
			if (!StateMachineList[i]->IsValid())
			{
				delete StateMachineList[i];
				StateMachineList.RemoveAt(i);
			}
		}
	}
}

void UAbilityStateSystem::ResetAllState()
{
	//������״̬ȫ���ÿգ���һ��Tick��ʱ������¼���
	if (OwnerCharacter->Role >= ROLE_AutonomousProxy)
	{
		for (int32 i = 0; i < StateMachineList.Num(); ++i)
		{
			StateMachineList[i]->ResetState();
			OwnerCharacter->UpdateStateMutex();
		}
	}
}

void UAbilityStateSystem::Tick(float DeltaTime)
{
	for (int32 i = 0; i < StateMachineList.Num(); ++i)
	{
		StateMachineList[i]->Tick(DeltaTime);
	}

	if (OwnerCharacter->Role == ROLE_Authority)
	{
		bool bChanged = false;
		for (int32 i = 0; i < StateMachineList.Num(); ++i)
		{
			if (i < CurrentStateIDs.Num())
			{
				if (CurrentStateIDs[i] != StateMachineList[i]->GetStateID())
				{
					CurrentStateIDs[i] = StateMachineList[i]->GetStateID();
					bChanged = true;
				}
			}
			else
			{
				CurrentStateIDs.Add(StateMachineList[i]->GetStateID());
				bChanged = true;
			}
		}

		/*if (bChanged)
		{
			MarkRepPropertyDirty();
		}*/
	}
}

void UAbilityStateSystem::GetStateMutexFlags(TMap<int32, int8>& CharMutexFlags)
{
	for (int32 i = 0; i < StateMachineList.Num(); ++i)
	{
		AbilityStateBase* AbilityState = StateMachineList[i]->GetCurrentState();
		if (AbilityState)
		{
			const TArray<ECharacterPlayerState>* OneStateMutexFlags = OwnerCharacter->GetMutexFlagByStateID(AbilityState->GetStateID());
			if (OneStateMutexFlags)
			{
				for (int32 FlagIdx = 0; FlagIdx < OneStateMutexFlags->Num(); ++FlagIdx)
				{
					//״̬����������õĶ��Ǳ������״̬��û���õ�˵��������
					int32 StateID = (int32)(*OneStateMutexFlags)[FlagIdx];
					int8* OldMutexFlag = CharMutexFlags.Find(StateID);
					if (!OldMutexFlag)
					{
						OldMutexFlag = &CharMutexFlags.Add(StateID, 0);
					}
					else
					{
						*OldMutexFlag = 0;
					}
				}
			}
		}
	}
}

void UAbilityStateSystem::GetStateTags(TSet<ECharStateTagType>& StateTags) const
{
	for (int32 i = 0; i < StateMachineList.Num(); ++i)
	{
		AbilityStateBase* AbilityState = StateMachineList[i]->GetCurrentState();
		if (AbilityState)
		{
			//��ȡC++������д��Tag
			AbilityState->GetStateTags(StateTags);

			//�Ӷ������Զ����л�ȡ״̬����ĸ���Tag
			const TArray<ECharStateTagType>* Tags = OwnerCharacter->GetTagsByStateID(AbilityState->GetStateID());
			if (Tags)
			{
				StateTags.Append(*Tags);
			}
		}
	}
}

bool UAbilityStateSystem::CheckInState(int32 StateID)
{
	for (int32 i = 0; i < StateMachineList.Num(); ++i)
	{
		if (StateMachineList[i]->GetStateID() == StateID)
		{
			return true;
		}
	}

	return false;
}

void UAbilityStateSystem::OnRep_CurrentStateIDs()
{
	if (OwnerCharacter->Role == ROLE_SimulatedProxy)
	{
		check(StateMachineList.Num() == CurrentStateIDs.Num());
		for (int32 i = 0; i < StateMachineList.Num(); ++i)
		{
			StateMachineList[i]->ChangeSimulatedState(CurrentStateIDs[i]);
		}

		if (OwnerCharacter)
		{
			OwnerCharacter->UpdateCurrentStateIDs();
			//if (OwnerCharacter->CurrentOptimizationState.OptAbilityStateTickDisabled)
			{
				OwnerCharacter->UpdateStateTags();
			}
		}
	}
	else if (OwnerCharacter->Role == ROLE_AutonomousProxy)
	{
#if 0
		if (OwnerCharacter->HasActorBegunPlay())
		{
			check(StateMachineList.Num() == CurrentStateIDs.Num());
			for (int32 i = 0; i < StateMachineList.Num(); ++i)
			{
				//���ƶ������˵�״̬��һ�£����ñ���״̬�������ָ��������һ��״̬
				if (StateMachineList[i]->GetStateID() != CurrentStateIDs[i])
				{
					check(false);
					ResetAllState();
					break;
				}
			}
		}
#endif
	}
}

