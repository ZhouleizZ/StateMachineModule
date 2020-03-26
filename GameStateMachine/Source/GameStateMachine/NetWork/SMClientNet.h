// Copyright 2004-2018 Perfect World Co.,Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DHCommon.h"
#include "PWGameInstance.h"
#include "System/Trophy/PWTrophyDataTableStruct.h"
#include "DETNet/DETNetClient.h"
#include "PWLobbyDataDefine.h"
#include "PWClientNet.generated.h"

/**
 *
 */
UCLASS()
class PWGAME_API UPWClientNet : public UObject, public DHGameInstance<UPWClientNet>
{
	GENERATED_BODY()
public:
	UPWClientNet() {}

	void Init();

	void Close();

	void LoginReq(const FString& Account, const FString& Token, bool PlusAccess, const FString& Lang);
	void CreateCharReq(const FString& Name, int32 Sex, int32 Race, const TArray<int32>& BodyPartIds);
	void ModifyPlayerFlagValue(int32 Flag, int32 NewValue);
	void ApplyReq(int32 MatchType, int32 Single);
	void ApplyWolfReq(int32 CharacterType);
	void UnapplyWolfReq();
	void SelectModuleReq(int32 Module);
	void LeaveBattleUnExcepted(int64 InBattleID);
	void GetPlayerInfoReq(int64 InCharID);
	void ChangeClothsReq(TMap<FString, int>& Flags);
	/**��������Ϳװ��<int64, int>-- ��GUID,0/1�Ƿ�װ����*/
	void ChangeWeaponSkinReq(TMap<int64, int32>& InItems);
	void PS4ChargeSuccess(const FString& code, const FString& label);
	//void ChangeLanguageReq(const FString& Lang);
	/**
	* TrophyId ����id
	* InProgress ��������
	* bActive �Ƿ����
	*/
	void SendServerAcquireTrophy(TArray<TrophyProcessItem>& TrophyProcessList);
	// �̳�
	void GetShopInfoReq(const EPWLobbyShopType InShopType);
	void BuyInShop(int32 ID);
	void OpenChestReq(int32 Type);
	void GetChestInfoReq(int32 Type);

	//���
	void SendPlayerUseItem(int64 id);

	void SendSetItemNotNew(int64 id);

	// ���ף�����һ���
	void SendDonateReq(const TMap<FString, int>& Items);


	// �ʼ�ϵͳ
	/**
	* @item MailID
	*/
	void SendDelMailReq(TArray<int64>& MailIDs);

	/**
	*@item MailID
	*/
	void SendPlayerReadMailReq(int64 MailID);

	/**
	*@item MailID
	*/
	void SendPlayerGetMailAttachReq(int64 MailID);


	// GM
	void AddItemReq(int32 ItemID, int32 Num);
	void SetServerTimestamp(int64 inTimestamp);
	void GMUDReq(FString CmdID, int32 Param1, int32 Param2);

	/**
	*@item Send wait time
	*/
	void SendWaitingReq();

	//Team
	void CreateTeamReq();
	void JoinTeamReq(int64 TeamID);
	void LeaveTeamReq();

	//quest
	void AddQuestSlotNum(int64 QuestID, int32 SlotID, int32 Count);
	void SetQuestSlotNum(int64 QuestID, int32 SlotID, int32 Count);
	void GetQuestAward(const TArray<int64>& QuestList);

	//battlePass
	void BuyBattlePassLevel(int32 ID, int32 Num);

	void SendSetUAVFlagReq(int32 InCompanionID, int32 InSkinItemID);

	void OnBattlePassEndAfterSecReq();

private:
	void _RegistEventHandler();
	void _RegistMsgHandler();
	uint8  _bInited = false;
private:
	void OnHttpRequestDone();
	void OnCharInfoModified(int32 Type, int64 Value);
	void OnCharInfoDeleted(int32 Type, int64 Value);
	void OnDropped(int32 Reason);
	void OnBulletinRefreshed();
	void OnAdvanceNoticeRefreshed();
	void OnStopServiceRefreshed();
	void OnBattlePassBulletinRefreshed();
	void OnSynWaitInfo(const FString& Data);
	void OnLoginRsp(int Rst);
	void OnCreateCharRsp(const FString& Data);
	void OnKickNotify(const FString& Data);
	void OnApplyResultNotify(const FString& Data);
	void OnApplyRsp(const FString& Data);
	void OnApplyWolfRsp(const FString& Data);
	void OnTeamMemberNotify(const FString& Data);
	void OnMatchBattleNotify(const FString& Data);
	void OnUnApplyWolfRsp(const FString& Data);
	void OnPlayerInfoRsp(const FString& Data);
	void OnSelectMoudleRsp(const FString& Data);

	void OnWeaponSkinNotify(const FString& Data);

	// ���ף�����һ���
	void OnDecomposeItemRsp(const FString& Data);

	// �̳�
	void OnGetShopInfoRsp(const FString& Data);
	void OnBuyInShopRsp(const FString& Data);
	/**�̳ǻ�����������*/
	void ShopActivityStartRsp(const FString& Data);
	/**�̳ǻ�����������*/
	void ShopActivityEndRsp(const FString& Data);
	/**��ȡ����ṹ��*/
	void OnOpenChestRsp(const FString& Data);
	/**��ȡ������Ϣ��*/
	void OnGetChestInfoRsp(const FString& Data);

	// ����
	void OnBattleRewardNotify(const FString& Data);

	//��ֵ
	void OnLobbyChargeInifoNotify(const FString& Data);

	//����ƥ���ɢ����
	void OnTeamDissolveNotify(const FString& Data);

	//��ֵʧ��/�ɹ�
	void OnLobbyChargeResult(const FString& Data);
	/**
	*@���ã� ͬ���ʼ�
	*/
	void OnSyncMails(const FString& Data);

	/**
	*@����: ɾ���ʼ����ؽ��
	*/
	void OnDelMail(const FString& Data);
	/**
	*@����: �Ķ��ʼ����ؽ��
	*/
	void OnPlayerReadMail(const FString& Data);
	/**
	*@����: �����ʼ��������ؽ��
	*/
	void OnPlayerGetMailAttach(const FString& Data);

	/**
	*@����: ����ʹ�ý������ؽ��
	*/
	void OnPlayerUseAwardResult(const FString& Data);

	/**
	*@����: ����������������ؽ��
	*/
	void OnSetItemNotNewResult(const FString& Data);

	void OnShowConsumedResult(const FString& Data);
	/**
	*@����: ÿ��60���ȡԤ��ʱ��
	*/
	void OnWolfWaitingRsp(const FString& Data);

	//Team
	void CreateTeamRsp(const FString& Data);
	void JoinTeamRsp(const FString& Data);
	void LeaveTeamRsp(const FString& Data);

	//Quest
	void OnQuestUpdated(int64 QuestID);

	// ����
	void OnActivityStartRsp(const FString& Data);
	void OnActivityEndRsp(const FString& Data);

	bool _IsLoginSended = false;
	/**���������ص���ʾ��Ϣ��*/
	void OnServerRspTips(const FString& Data);

	void OnCurrentQuestStatusUpdated(const FString& Data);
	/**cfg Net Resource changed.*/
	void OnCfgNotifyUpdated(const FString& Data);

	void OnBPExp2GoldNotify(const FString& Data);

	//AdditionPurchase
	void OnAdditionPurchaseUpdated(int64 AdditionPurchaseID);

	void OnSetUAVFlagRsp(const FString& InData);

	void OnCompanionUpdated(int64 CompanionID);

	void OnBattlePassEndAfterSecRsp(const FString& Data);
};
