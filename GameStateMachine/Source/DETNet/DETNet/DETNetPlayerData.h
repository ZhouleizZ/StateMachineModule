#pragma once
#include "DETNetCmn.h"
#include "DETNetStruct.h"

class DETNET_EXPORT PlayerData
{
public:
	int64 CharId;
	int CreateTime;
	int OnlineTime;
	int Level;
	int Exp;
	int Sex;
	int Race;
	int Money;						//D��
	int MoneyBound;					//��D��
	int Gold;						//���
	int GoldBound;					//�󶨽��
	int LegendGold;					//�����
	int DetMedal;					//Det����
	FString Acct;
	FString Name;
	TArray<int> Flags;
	TMap<int64, FSItem> ItemList;
	TMap<int64, FSAch> AchList;
	TMap<int64, FSCD> CDList;
	TMap<int64, FSSkill> SkillList;
	TMap<int64, FSState> StateList;
	TMap<int64, FCupInfo> CupList;
	TArray<int>   AchieveCupList;
	TMap<int64, FSQuest> QuestList;
	TMap<int64, FSAdditionPurchase> APList;
	TMap<int64, FSUAV> UAVList;
	void Clear()
	{
		CharId = 0;
		CreateTime = 0;
		OnlineTime = 0;
		Level = 0;
		Exp = 0;
		Sex = 0;
		Race = 0;
		Money = 0;
		MoneyBound = 0;
		Gold = 0;
		GoldBound = 0;
		LegendGold = 0;
		DetMedal = 0;
		Acct.Empty();
		Name.Empty();
		Flags.Empty();
		ItemList.Empty();
		AchList.Empty();
		CDList.Empty();
		SkillList.Empty();
		StateList.Empty();
		CupList.Empty();
		AchieveCupList.Empty();
		QuestList.Empty();
		APList.Empty();
		UAVList.Empty();
	}
};

enum Login_Rst
{
	LoginRst_NoChar = 1,
	LoginRst_Ok = 0,

	LoginRst_NoArea = -1,			//��������û��׼����ɣ�û�п��õķ�����
	LoginRst_Ban = -2,				//����������ֹ��½
	LoginRst_LoginDBErr = -3,		//��½ʧ�ܣ������룩
	LoginRst_VerifyFailed = -4,		//ƽ̨��ps4��У��ʧ��

	LoginRst_Ver = -11,				//�ͻ�����������汾��һ��
	LoginRst_EntryWrongStatus = -12,//��½ʧ�ܣ������룩
	LoginRst_OnEntry = -13,			//��½ʧ�ܣ������룩
	LoginRst_EntryDBErr = -14,		//��½ʧ�ܣ������룩
	LoginRst_EntryJson = -15,		//��½ʧ�ܣ������룩
	LoginRst_InvalidOkey = -16,		//��½ʧ�ܣ������룩
	LoginRst_EntryTimeout = -17,	//��½ʧ�ܣ������룩

	LoginRst_Online = -21,			//�Ѿ����ߣ�������
	LoginRst_NoLobby = -22,			//��½ʧ�ܣ������룩
	LoginRst_CentreTimeout = -23,	//��½ʧ�ܣ������룩

	LoginRst_LobbyWrongStatus = -31,//��½ʧ�ܣ������룩
	LoginRst_LobbyWrongStatus2 = -32,//��½ʧ�ܣ������룩
	LoginRst_LobbyWrongStatus3 = -33,//��½ʧ�ܣ������룩
	LoginRst_LobbyTimeout = -34,	//��½ʧ�ܣ������룩
	LoginRst_LostPlayer = -35,		//��½ʧ�ܣ������룩
	LoginRst_InvalidPwd = -36,		//��½ʧ�ܣ������룩
	LoginRst_LobbyDBErr = -37,		//��½ʧ�ܣ������룩
	LoginRst_LobbyDBErr2 = -38,		//��½ʧ�ܣ������룩
	LoginRst_LobbyDBErr3 = -39,		//��½ʧ�ܣ������룩
	LoginRst_LobbyDBErr4 = -40,		//��½ʧ�ܣ������룩
};

enum Drop_Type
{
	DropType_Normal = 0,				//�Ѿ�������Ϸ�ˣ�Ȼ����������Ͽ�����
	DropType_GetHttpFailed = 1,			//��½�׶Σ�����ʧ�ܣ������룩
	DropType_ConnectLoginFailed = 2,	//��½�׶Σ�����ʧ�ܣ������룩
	DropType_ConnectEntryFailed = 3,	//��½�׶Σ�����ʧ�ܣ������룩
	DropType_ConnectLobbyFailed = 4,	//��½�׶Σ�����ʧ�ܣ������룩
};

enum Create_Rsp
{
	CreateRst_OK = 0,					//�ɹ�
	CreateRst_Err_Wrong_Status = -1,	//����״̬
	CreateRst_Err_Lost_Item = -2,		//����װ��
	CreateRst_Err_Wrong_Sex = -4,		//װ���Ա����
	CreateRst_Err_Wrong_BodyPart = -5,	//��λ����
	CreateRst_Err_Wrong_Data = -6,		//���ݴ���
	CreateRst_Err_Other = -10,			//��������
};

enum VNT
{
	VNT_Invalid,
	VNT_CreateTime,
	VNT_OnlineTime,
	VNT_CharName,
	VNT_Acct,
	VNT_Level,
	VNT_Exp,
	VNT_Sex,
	VNT_Race,
	VNT_Money,
	VNT_MoneyBound,
	VNT_Gold,
	VNT_GoldBound,
	VNT_LegendGold,
	VNT_DetMedal,
	VNT_Flagint32,
	VNT_ItemList,
	VNT_AchList,
	VNT_CDList,
	VNT_SkillList,
	VNT_StateList,
	VNT_CupList,
	VNT_QuestList,
	VNT_APList,
	VNT_UAVList,
};
