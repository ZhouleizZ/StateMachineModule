// Copyright 2004-2017 Perfect World Co.,Ltd. All Rights Reserved.P520

#pragma once

#include "CoreMinimal.h"
#include "UIWidgetHead.generated.h"

DECLARE_STATS_GROUP(TEXT("PWWidget"), STATGROUP_PWWidget, STATCAT_Advanced);
DECLARE_CYCLE_STAT(TEXT("DamageInstigate Tick"), STAT_DamageInstigate_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("BeginningLoading Tick"), STAT_BeginningLoading_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("Compass Tick"), STAT_Compass_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("Countdown Tick"), STAT_Countdown_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("MainMap Tick"), STAT_MainMap_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("Marker Tick"), STAT_Marker_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("MiniMap Tick"), STAT_MiniMap_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("PaintsOfMainMap Tick"), STAT_PaintsOfMainMap_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("Parachute Tick"), STAT_Parachute_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("PlayerBadge Tick"), STAT_PlayerBadge_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("PlayerLocation Tick"), STAT_PlayerLocation_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("QuickMessage Tick"), STAT_QuickMessage_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("RegularMap Tick"), STAT_RegularMap_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("SafeAreaInfo Tick"), STAT_SafeAreaInfo_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("Vehicle Tick"), STAT_Vehicle_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("WeaponInfo Tick"), STAT_WeaponInfo_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("EdgeInfo Tick"), STAT_EdgeInfo_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("PutInLocation Tick"), STAT_PutInLocation_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("TeammateEdgeInfo Tick"), STAT_TeammateEdgeInfo_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("TeammateSlot Tick"), STAT_TeammateSlot_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("OnShowMapActorsWidget Tick"), STAT_ShowMapActors_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("UPWMapGrideWidget Tick"), STAT_MapGride_UMGTick, STATGROUP_PWWidget);
DECLARE_CYCLE_STAT(TEXT("UPWMapCricleWidget Tick"), STAT_MapCricle_UMGTick, STATGROUP_PWWidget);

UENUM(BlueprintType)
enum class EUMGID : uint8
{
	EUMGID_None,
	EUMGID_Login,
	EUMGID_CreateChar,
	// 	EUMGID_Lobby,
	EUMGID_LoadBattle,
	// 	EUMGID_BeginningNotice,
	EUMGID_Countdown,	//����ʱ��ȦȦ

	EUMGID_Interaction,		//F������ʾ
	EUMGID_OperationNotice,
	EUMGID_Map,
	EUMGID_MiniMap,
	// 	EUMGID_Inventory,
	EUMGID_MainWidget,
	// 	EUMGID_Vehicle,
	// 	EUMGID_TeleScope,
	// 	EUMGID_KillInfo,		//��ɱ����
	EUMGID_CharacterInfo,

	EUMGID_WeaponInfo,
	EUMGID_DamageInstigator,
	EUMGID_SafeAreaInfo,
	EUMGID_SafeAreaNotice,
	// 	EUMGID_QuickMsg,
	// 	EUMGID_Lung,
	//  	EUMGID_Killcam,
	// 	EUMGID_KillcamPlayerLocation,
	EUMGID_ESCMatch,
	// 	EUMGID_ESCLobby,
	// 	EUMGID_EndingTip,		//������ʾ����
	EUMGID_Ending,
	// 	EUMGID_EndingReward,
	EUMGID_Offline,
	// 	EUMGID_BugReport,
	EUMGID_Settings,
	// 	EUMGID_ExitGame,
	// 	EUMGID_BackToLobby,
	// 	EUMGID_Observe,
	EUMGID_SkillTest,

	EUMGID_TeamInfo,
	EUMGID_KillNotice,
	// 	EUMGID_DrugPreview,
	// 	EUMGID_GamePadPromptSmall,
	EUMGID_GamePadPromptLarge,
	// 	EUMGID_DebugMessage,
	// 	EUMGID_Entrance,
	// 	EUMGID_ThreeArymLobby,
	// 	EUMGID_SelectLobby,
	EUMGID_AutoPickup,

	EUMGID_Mail,
	EUMGID_Connecting,
	// 	EUMGID_ReceivedInvite,			//����������루�°棩
	// 	EUMGID_TeamReady,				//����Ready
	// 	EUMGID_Matching,				//ƥ����
	// 	EUMGID_ExplodeCountdown, 
	// 	EMUGID_Activity,
	// 	EMUGID_FirstChargeInfo,
	// 	
	// 	EMUGID_FirstChargeBonus,
	EUMGID_UserAgreement,
	EUMGID_PrivacyPolicy,
	EUMGID_LoginOld,
	EUMGID_Queue,	//�Ŷӽ���
	EUMGID_MoviePlayer,
	EUMGID_StandaloneNotice,
	EUMGID_Log,	// Log����


	// ����

	EUMGID_WW_Lobby,
	EUMGID_WW_BroadcastMessage,
	EUMGID_WW_BattleHumanItem,
	EUMGID_WaittingToStartFight,
	EUMGID_TeamMessage,
	EUMGID_WW_Loading,
	EUMGID_WW_GamePadOperation,

	EUMGID_TestInfoWidget,

	EUMGID_WW_BornOperation,
	EUMGID_WW_PlayerList,

	EUMGID_WW_PostLoginVideo,
	EUMGID_WW_PINGWidget,

	EUMGID_LoginBulletinWidget, // ��½���湫��
	EUMGID_LobbyShutDownBroadcastWidget, //����ͣ���㲥
	EUMGID_InGameShutDownBroadcastWidget, //��Ϸ��ͣ���㲥

	EUMGID_WW_GoSpectating,
	EUMGID_WW_Spectating,
	EUMGID_WW_WaitingLoading,
	EUMGID_WW_SurroundingGrenadeInfo,

	EUMGID_WW_HitNotice, // ������ʾ
	EUMGID_LobbyBulletinWidget, // �������湫��
	EUMGID_ReleaseNotesWidget, // �汾˵������
	EUMGID_LobbyTaskWidget, // �����������
	EUMGID_InGameTaskWidget, // ��Ϸ���������

	EUMGID_QuestPreviewWidget,

	EUMGID_CompanionInfo,//�����������Ϣ
	EUMGID_SpecificationInBattle,//���ڽ�ѧ

	EUMGID_Max,
};

UENUM(BlueprintType)
enum class EUMGLoadingSceneType : uint8
{
	EUMGLoadingSceneType_None,
	EUMGLoadingSceneType_BeforeBattle,
	EUMGLoadingSceneType_AfterBattle,
	EUMGLoadingSceneType_BeforeAndAfterBattle,
};

UENUM(BlueprintType)
enum class EUMGLoadingUsedCareerType : uint8
{
	EUMGLoadingUsedCareerType_None,
	EUMGLoadingUsedCareerType_Human,
	EUMGLoadingUsedCareerType_Wolf,
	EUMGLoadingUsedCareerType_All,
};

UENUM(BlueprintType)
enum class EUMGIDLobby : uint8
{
	EUMGIDLobby_None,

	EUMGIDLobby_Shop,
	EUMGIDLobby_MilitaryChest,
	EUMGIDLobby_LegendaryTreasure UMETA(DisplayName = "���汦��ҳ��"),
	EUMGIDLobby_ItemsDisplayByQuality,
	EUMGIDLobby_DisplayItem,
	EUMGIDLobby_PassportPlus,
	EUMGIDLobby_BattlePass UMETA(DisplayName = "BattlePassҳ��"),
	EUMGIDLobby_PreviewAllReward,
	EUMGIDLobby_PurchaseLevel,
	EUMGIDLobby_GetReward,
	EUMGIDLobby_OpenChest,
	EUMGIDLobby_PreviewAward,

	EUMGIDLobby_LimitedShop UMETA(DisplayName = "��ʱ�̳�ҳ��"),
	EUMGIDLobby_LimitedPage,
	EUMGIDLobby_LegendaryShop UMETA(DisplayName = "�����̳�ҳ��"),
	EUMGIDLobby_ClothesPage,
	EUMGIDLobby_SkinPage,
	EUMGIDLobby_BoxPage,
	EUMGIDLobby_PaintPage,
	EUMGIDLobby_InterfacePage,
	EUMGIDLobby_Face,
	EUMGIDLobby_PassportPlusDetail,

	EUMGIDLobby_Donate,
	EUMGIDLobby_DonateConfirm,

	EUMGIDLobby_InventoryHumanBody,
	EUMGIDLobby_InventoryHumanClothes,
	EUMGIDLobby_InventoryWerewolfSkin,
	EUMGIDLobby_InventoryPainting,
	EUMGIDLobby_InventoryBonus,
	EUMGIDLobby_InventoryInterface,

	EUMGIDLobby_Bank,
	EUMGIDLobby_BuyGold,
	EUMGIDLobby_BuyGoldConfirm,
	EUMGIDLobby_BuyDCoin,
	EUMGIDLobby_BuyDCoinConfirm,

	EUMGIDLobby_LobbyTask,
	EUMGIDLobby_BPBullentinBoar,

	EUMGIDLobby_LobbyActivity,
	EUMGIDLobby_BuyDLC,
	EUMGIDLobby_BuyDLCResult,

	EUMGIDLobby_InventoryBeastPainting,

	EUMGIDLobby_LegendaryBundle,

	EUMGIDLobby_MAX
};