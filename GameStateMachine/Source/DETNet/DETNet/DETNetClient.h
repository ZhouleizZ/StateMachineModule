#pragma once
#include "DETNetWS.h"
#include "DETNetPlayerData.h"
#include "Delegates/DelegateCombinations.h"
#include "OnlineError.h"
#include "DHHttpClient.h"

//���״̬ö��
enum
{
	sPlayer_Normal,
	sPlayer_ConnectLogin,		//����login
	sPlayer_VerifyLogin,		//��login������֤
	sPlayer_WaitLoginClose,
	sPlayer_ConnectEntry,		//����entry
	sPlayer_VerifyEntry,		//��entry������֤��¼
	sPlayer_WaitEntryClose,
	sPlayer_ConnectLobby,		//����lobby
	sPlayer_VerifyLobby,		//��lobby������֤��¼
	sPlayer_EnterLobby,			//��¼�ɹ�
	sPlayer_Closing,			//�ر���
};
class DETNET_EXPORT DETNetClient : public DETNetWS
{
	DETNetClient();
	static DETNetClient Ins;
public:
	static DETNetClient& Instance();

	enum class HttpServeStatus
	{
		Ok,                 // һ������
		InMaintenance,      // ά����
		HttpServeError,     // Http�������
		NetUnavailable,     // �������
		JsonParseFailed,    // Json�������� 
		VersionOrAccountNotSupported
	};

private:
	void OnConnected()override;
	void OnConnectionError(const FString& Error)override;
	void OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean)override;
	void OnTick(float DeltaTime)override;
private:
	//���綼���첽�ģ��ر�Ҳ���첽�ģ�����ÿ�����Ӷ�Ū������
	FString Acct;
	FString Token;
	bool PlusAccess = false;
	int64 CharId;
	FString Okey;
	FString Ver;
	FString Pwd;
	FString LoginUrl;
	FString Url;
	FString HttpUrl;
	FString Language;

public:
	int State;					//״̬
	PlayerData Data;			//����
	FString UpdateUrl;			//���µ�ַ
	FString UserAgreementUrl;
	FString PrivacyPolicyUrl;
	FClientAddrObj RealAddr;
	FClientBulletinList BulletinList; // �����б�
	FClientBulletinList AdvanceNoticeList; // Ԥ���б�
	FClientBulletinList StopServiceList; // ͣ���㲥�б�
	FClientBulletinList BattlePassBulletinList;//BattlePass �����б�
	FString DefaultAnnouncementUrl;

	TMap<FString, FCfgObj> CfgMap;
	FString GetLogAddress();
	TArray<FAddrObj>& GetAreaList();

	FString GetVer() { return Ver; }

	int64 SrvTimestamp;		//���������͹�����ʱ���
	int64 RcvSrvTime;		//����������ʱ���ʱ����ʱ��
public:
	void Disconnect();
	void Close();
	void SetState(int _State);
	void SetLoginUrl(const FString& Url)
	{
		LoginUrl = Url;
	}
	DECLARE_MULTICAST_DELEGATE_OneParam(FBeginConnectV2, HttpServeStatus);
	typedef FBeginConnectV2::FDelegate FBeginConnectV2Delegate;
	void BeginConnectV2(const FString& _Url, const std::initializer_list<DHHttpField>& fields, FBeginConnectV2Delegate Delegate);
	void ConnectLogin(const FString& _Acct, const FString& _Token, bool _PlusAccess, const FString& _Language);
	void ConnectEntry(const FString& _Url, const int64 _CharId, const FString& _Acct, const FString& _Okey);
	void ConnectLobby(const FString& _Url, const FString& _Pwd);

	void PullBulletin(const FString Culture);
	void PullAdvanceNotice(const FString Culture);
	void PullStopService(const FString Culture);
	void PullBattlePassBulletin(const FString Culture);
	void SetDefaultAnnounceUrl(const FString DefaultUrl, FString Version);

	const int64 GetCharId()
	{
		return CharId;
	}
	const int64 GetTime();
};
