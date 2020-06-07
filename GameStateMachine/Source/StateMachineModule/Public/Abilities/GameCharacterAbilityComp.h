#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterTypeDefine.h"
#include "GameCharacterAbilityComp.generated.h"


USTRUCT(BlueprintType)
struct FCharBPCommandFuncInfo
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere)
		FName CmdName;

	UPROPERTY(EditAnywhere)
		FName FuncName;

	UPROPERTY(EditAnywhere)
		bool bNeedActive;
};


UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class STATEMACHINEMODULE_API UGameCharacterAbilityComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UGameCharacterAbilityComponent(const FObjectInitializer& ObjectInitializer);
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	virtual void Activate(bool bReset = false) override;
	virtual void Deactivate() override;
	virtual void OnRep_IsActive() override;

	// ���ڷ��������������ʼ����ʱ�򣬲����ܻ�ȡ��ɫ�����ԣ������漰��ɫ���ԵĲ�����������������г�ʼ����zhijie
	virtual void AfterInitPlayer();

	//����AbilityComponent��Tick�����͹رգ�����һ���Ż�ѡ��
	virtual void UpdateDisableTickState(bool bDisabled);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	virtual void GetStateTags(TSet<ECharStateTagType>& StateTags) const;

	UFUNCTION(BlueprintCallable)
		virtual void RegisterBlueprintFunctionCommand(const FName& Command, const FName& FuncName);

	UFUNCTION(BlueprintCallable)
		virtual void UnregisterBlueprintFunctionCommand(const FName& Command, const FName& FuncName);

	UFUNCTION(BlueprintCallable)
		AStateMachineCharacter* GetOwnerCharacter() { return OwnerCharacter; };

	UFUNCTION(BlueprintCallable)
		void MarkRepPropertyDirty()
	{
		DirtyRepChannels.Empty();
	}

	void ClearRepPropertyDirty(UActorChannel* Channel);
	bool IsRepPropertyDirty(UActorChannel* Channel);

	bool ReplicateSelf(UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags);

	virtual void ComponentRegistCommondInfo(FName CommandName, FString FunctionName);
	virtual void ComponentUnRegistCommondInfo(FName CommandName, FString FunctionName);
protected:

	virtual void RegisterStates() { }
	virtual void RegisterActiveStates() { }
	virtual void RegisterCommands() { }
	virtual void RegisterActiveCommands() { }
	virtual void RegisterBPCommands(bool InNeedActive);

	virtual void UnregisterStates() { }
	virtual void UnregisterActiveStates() { }
	virtual void UnregisterCommands() { }
	virtual void UnregisterActiveCommands() { }
	virtual void UnregisterBPCommands(bool InNeedActive);

	TSet< TWeakObjectPtr<UActorChannel> > DirtyRepChannels;
public:
	UPROPERTY(BlueprintReadOnly, Transient)
		AStateMachineCharacter* OwnerCharacter;

	bool bActiveStateRegisterd;

	UPROPERTY(EditAnywhere)
		TArray<FCharBPCommandFuncInfo> BPCommandFuncs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSet<ECharStateTagType> ActiveStateTags;

	bool CachedPrimitiveTickEnabled;
};