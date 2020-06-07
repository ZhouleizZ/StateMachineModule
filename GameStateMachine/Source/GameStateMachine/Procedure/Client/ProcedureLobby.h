// Copyright 2016 P906, Perfect World, Inc.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInfo.h"
#include "PWLobbyTeam.h"
#include "Procedure/PWProcedureBase.h"
#include "DETNet/DETNetPlayerData.h"
#include "PWProcedureLobby.generated.h"

class UPWLobbyTeamManager;

DECLARE_MULTICAST_DELEGATE_OneParam(FPWOnCharacterLvChanged, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FPWOnCharacterExpChanged, int32);

UENUM()
enum class EBeastType : uint8
{
	Werewolf = 1,
	Leopard = 2,
};

/**
 *
 */
UCLASS(BlueprintType)
class PWGAME_API UPWProcedureLobby : public UPWProcedureBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		int32 MaxSessionPlayerCount = 8;
	// ����ƽ���ȴ�ʱ��
	FTimespan AvgWaitTime;
public:
	virtual ProcedureState GetState() { return ProcedureState::ProcedureState_Lobby; }
	virtual void Enter();
	virtual void Leave();

public:
	void SetIsOffline() { m_bOffline = true; }
	void InitSelfPlayerInfo(const PlayerData& data);

	void UpdatePlayerSex(const PlayerData& data);

	void ModifyFlagInt32(uint8 FlagIndex, int32 value);
	void UpdateCompanionData(const FSUAV& CompanionData);

	int32 GetMoney() const;

	UFUNCTION(BlueprintPure, Category = "LobbyPlayerInfo")
		FPWFullPlayerInfo GetFullPlayerInfo();

	UFUNCTION(BlueprintCallable, Category = "Lobby TeamInfo")
		void GetLoginoutTimeString(bool& bShowTime, FString& LoginTimeStr, FString& LogoutTimeStr);

	UFUNCTION(BlueprintPure, Category = "Lobby TeamInfo")
		const bool IsTeamMemberReady(int32 Index = 0) const;

	UFUNCTION(BlueprintCallable, Category = "LobbyWidget")
		void ShowInviteDialog();

	void CheckStopServiceMsg();

	// werewolf mode
	// ��ģʽ����Ӫ��
	UFUNCTION(BlueprintPure, Category = "Lobby")
		bool GetIfBeastModeNow() const { return bIfInBeastMode; }
	bool ToggleBeastOrHumanMode();

	// ����Ӫ�µ�������
	EBeastType GetBeastTypeNow() const { return BeastType; }
	void SetBeastType(EBeastType InBeastType);

	// Lobby Refresh Character
	void SetDisableRefreshCharacter(bool bInDisable) { bDisableRefreshCharacter = bInDisable; }
	bool GetDisableRefreshCharacter() const { return bDisableRefreshCharacter; }

	void SetLoginoutTime(int LoginTime, int LogoutTime);

	//��ʾƥ�����
	//void ChangeMatchingState(bool bStart);


	void UpdatePlayerLevel(int32 Level);
	void UpdatePlayerExp(int32 Exp);

	void UpdatePlayerScore(int32 Score);
	UFUNCTION(BlueprintPure, Category = "Lobby PlayerInfo")
		int32 GetPlayerScore() { return FullInfo.BasicPlayerInfo.Score; }

	UFUNCTION()
		void CheckFriendInviteData();

	void UpdateTranscriptsFlag(int32 value);

	UFUNCTION()
		void PullStopService();

	UFUNCTION()
		void PullAdvanceNotice();

	void CheckAdvanceNotice();

private:
	FPWFullPlayerInfo	FullInfo;

	FPWOnCharacterLvChanged OnCharacterLvChangedDelegate;
	FPWOnCharacterExpChanged OnCharacterExpChangedDelegate;

public:
	void SelectGameMoudles(int32 nMoudles);
	int32 GetGameMoudles() { return m_nMoudles; }

	int32 GetModule() { return m_nMoudles; }

	UFUNCTION()
		void AutoApply();

private:
	FTimerHandle AutoApplyHandle;

	FTimerHandle PullStopServiceHandle;
	FTimerHandle StopServicePromptHandle;

	int32	m_nMoudles = 0;

	bool	m_bOffline = false;

	bool	m_bFirstTimeIntoLobby = true;

	// �Ƿ�������Ӫ
	bool bIfInBeastMode = false;
	// ����Ӫ��������
	EBeastType BeastType = EBeastType::Werewolf;

	// �ڷ��������ظ���Flag��Ϣ��ʱ���Ƿ��ֹˢ�� Character
	bool bDisableRefreshCharacter = false;

	UPROPERTY()
		UPWLobbyTeamManager* TeamManager = nullptr;

public:
	void ShowWaitingLoadingWidget();

	void HideWaitingLoadingWidget();
};




