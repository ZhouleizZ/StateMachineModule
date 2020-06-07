// Copyright 2016 P906, Perfect World, Inc.

#include "PWProcedureBattleDS.h"
#include "Utility/PWLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "PWDropManager.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformMisc.h"
#include "PWAirDropManager.h"
#include "PWCharacterManager.h"
#include "PWRouteManager.h"
#include "PWSafeCircleManager.h"
#include "PWLevelMgr.h"
#include "PWDoubleCircleManager.h"
#include "DHPlayerStartManangement/DHPlayerStartManager.h"
#include "DHEvacuateManagement/DHEvacuateManager.h"
#include "PWGameSettings.h"
#include "PWDSNet.h"
#include "PWEnvTempManager/PWEnvTempManager.h"
#include "PWDynamicActorManager/PWDynamicActorManager.h"
#include "PWInteractRegisterManager.h"
#include "PWAirForteManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CharacterSkill/PWCharacterSkillManager.h"
#include "PWPhysicalPowerManager/PWPhysicalPowerManager.h"
#include "PWAssetManager.h"
#include "PWLimousineDataManager.h"


UPWProcedureBattleDS::UPWProcedureBattleDS()
{
}

void UPWProcedureBattleDS::Enter()
{
	//只需要初始化一次的放在这里
	UPWAssetManager::Get(this)->Init();
	UPWLimousineDataManager::Get(this)->Init();
	UPWCharacterSkillManager::GetInstance(this)->Init();

	if (UPWGameSettings::Get()->MatchSetting.bEnableSafeCircle) {
		EMapType MapType = UPWBlueprintLibrary::GetMapType(this);
		if (MapType == EMapType::EMapType_Corps) {
			UPWDoubleCircleManager::Get(this)->Init();
		}
		else/* if(MapType != EMapType::EMapType_WereWolf)*/ {
			UPWSafeCircleManager::Get(this)->Init();
		}
	}

	//change to battle map
	if (GetWorld()->IsPlayInEditor() == true)
	{
		OnPostLoadMap(GetWorld());
		return;
	}

	FString MapName;
#if WITH_EDITOR
	FParse::Value(FCommandLine::Get(), TEXT("MapName="), MapName);
#endif
	if (MapName.IsEmpty()) {
		FPWMapConfig cfg;
		if (UPWBlueprintLibrary::GetMapConfig(this, cfg) == true) {
			MapName = cfg.MapName.ToString();
		}
	}
	if (GetWorld()->ServerTravel(MapName, false) == false) {
		check(0);
	}
}

void UPWProcedureBattleDS::Leave()
{
	UPWCharacterSkillManager::GetInstance(this)->Release();
}

void UPWProcedureBattleDS::OnPostLoadMap(UWorld* LoadedWorld)
{
	UPWLevelMgr::Get(this)->BeginLoadSubLevels();
}

void UPWProcedureBattleDS::OnPostLoadAllMaps()
{
	if (m_IsRestarting)
	{
		FGenericPlatformMisc::RequestExit(false);
		return;
	}
	//每次战场启动都需要初始化的放在这里
	UPWCharacterManager::Get(this)->Init();
	UPWAirDropManager::Get(this)->Init();
	// some pickup actors are generated by UPWDynamicActorManager, used by UPWDropManager
	UPWDynamicActorManager::Get(this)->Init();
	// UPWDynamicActorManager must initial before this.
	UPWDropManager::Get(this)->Init();
	UDHPlayerStartManager::Get(this)->Init();
	UPWAirForteManager::Get(this)->Init();
	UDHEvacuateManager::Get(this)->Init();
	if (m_IsRestarting)
	{
		UPWDSNet::GetInstance(this)->SendCanWorkNotify();
		m_IsRestarting = false;
	}
	else
	{
		UPWDSNet::GetInstance(this)->Init();
	}

#if WITH_EDITOR
	UPWCharacterManager::Get(this)->AddAICharacterForStandAloneMode();
#endif
}

void UPWProcedureBattleDS::StartRestart()
{
	m_IsRestarting = true;
	//战场释放前需要清除数据的放在这里
	UPWDropManager::Get(this)->Clear();
	UPWCharacterManager::Get(this)->Clear();
}
