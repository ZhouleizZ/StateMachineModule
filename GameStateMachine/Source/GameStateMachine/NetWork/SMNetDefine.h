#pragma once

#define MAX_FLAG_INT32	256

#define ITEM_BOUNDGOLD_ID		10001		// �󶨽��
#define ITEM_GOLD_ID	10002				// ���
#define ITEM_MONEYBOUND_ID	10003			// ��D��
#define ITEM_MONEY_ID	10004				// D�����ֻ�г�ֵ
#define ITEM_LEGENDGOLD_ID 10005			// �����
#define ITEM_EXP_ID		10006				// ���飨��ʱû�ã�

#define ITEM_BATTLEPASS_EXP_ID 10010		// Battlepass ����
#define ITEM_WEEK_ACTIVE_ID 10011			// �ܻ�Ծ��
#define ITEM_DAILY_ACTIVE_ID 10012			// �ջ�Ծ��

#define PSN_LABEL_TYPE_CHARGE 0
#define PSN_LABEL_TYPE_DLC 1


enum PLAYER_FLAG32
{
	//���븳ֵ����Ϊ����̣���;���ܸ�������
	player_flag32_head = 0,
	player_flag32_chest_shirt = 1,
	player_flag32_hands_gloves = 2,
	player_flag32_coat = 3,
	player_flag32_crotch_pants_shorts_skirt = 4,
	player_flag32_lowerLeg_leggings_socks = 5,
	player_flag32_feet_shoes = 6,
	player_flag32_hat = 7,
	player_flag32_hair = 8,
	player_flag32_beard = 9,
	player_flag32_glasses = 10,
	player_flag32_necklace = 11,
	player_flag32_earrings = 12,
	player_flag32_watch_bracelet = 13,
	player_flag32_tatoo = 14,
	player_flag32_helm = 15,//
	player_flag32_vest = 16,//
	player_flag32_backpack = 17,//
	player_flag32_raceskin = 18,
	player_flag32_painting = 19,
	player_flag32_behaivorcontroller = 20,
	player_flag32_belt = 21,

	Player_Flag32_HeadSuit = 27,				//ͷ����װ
	Player_Flag32_BodySuit = 28,				//������װ
	Player_Flag32_WholeSuit = 29,				//������װ

	player_flag32_noSexBegin = 30,
	player_flag32_wolf = 30,				//��Ƥ��
	player_flag32_parachute = 31,				//����ɡ
	player_flag32_smog = 32,					//β��
	Player_Flag32_BusinessCard = 33,			//��Ƭ
	Player_Flag32_Leopard = 34,					//����Ƥ��
	player_flag32_noSexEnd = 40,


	player_flag32_body_max = 60,				//�����Ǹ����



	//����Ԥ��
	player_flag32_act_begin = 61,
	player_flag32_act_1 = 61,
	player_flag32_act_2 = 62,
	player_flag32_act_3 = 63,
	player_flag32_act_4 = 64,
	player_flag32_act_5 = 65,
	player_flag32_act_end = 65,

	//����Ԥ��
	player_flag32_points_begin = 71,
	player_flag32_points_used = 71,
	player_flag32_points_unused = 72,
	player_flag32_points_end = 72,


	//ƥ�����
	player_flag32_score = 73,

	player_flag32_gc_mail_id = 74,

	//����ۼƳ�ֵ����player_data����̫�鷳�ˣ�����д�����
	player_flag32_mall_all_recharge = 75,
	//�����Ҵ���ĸ���(�������������ô�����ģ����Ǹ�����ɫ��صı��)
	player_flag32_transcripts = 76,

	player_flag32_user_agreement_version = 77,
	player_flag32_privacy_version = 78,

	Player_Flag32_Human_Kill_Human = 81,  // ��ɱ������
	Player_Flag32_Human_Kill_Wolf = 82,  // ��ɱ������
	Player_Flag32_Human_Win = 83,  // ����ʤ������
	Player_Flag32_Wolf_Kill_Human = 84,  // ��ɱ������
	Player_Flag32_Wolf_Prevent_Evacuate = 85,  // ������ֹ���೷��Ĵ���
	Player_Flag32_Wolf_Kill_All_Human = 86,  // ����ȫ���������

	Player_Flag32_BattlePass_ID = 94,
	Player_Flag32_BattlePass_Exp = 95,
	Player_Flag32_BattlePass_lv = 96,
	Player_Flag32_BattlePass_Plus = 97,

	player_flag32_max = MAX_FLAG_INT32,

	//����ĵ����Ϳ����ˣ�����Ҫ��ֵ
	player_flag32_tmp_begin = player_flag32_max,//����Ҫ���̵���ʱ����

	player_flag32_tmp_match_type,					//ƥ������
	player_flag32_tmp_match_status,					//����ƥ����״̬


	player_flag32_tmp_end
};

enum
{
	//����ս���ı������ �����ȡ�ñ��λ�е�ָ������
	TRANSCRIPT_BEGIN = -1,
	TRANSCRIPT_1 = 0,
	TRANSCRIPT_END,
};

//ƥ�����ͣ����31�����ͣ� ģʽ->��ͼ  ÿ��ģʽ�¿����в�ͬ�ĵ�ͼ
enum
{
	/////////////////////////����ģʽ//////////////////////////////
	MATCH_TYPE_MIN = 0,
	MATCH_TYPE_QUICK = 1,			//����ƥ��
	MATCH_TYPE_SOLO = 2,			//soloƥ��
	MATCH_TYPE_2GROUP = 3,			//2�����
	MATCH_TYPE_4GROUP = 4,			//4�����  

	////////////////////////����ģʽ////////////////////////////////////////
	MATCH_TYPE_THREEARMY_10GROUP = 5,			//10�����

	///////////////////////8����ɱģʽ//////////////////////////////////////
	MATCH_TYPE_ICU_QUICK = 6,          //8����ɱ����ƥ��
	MATCH_TYPE_ICU_2GROUP = 7,         //8����ɱ2�����

	MATCH_TYPE_MAX,
};

enum
{
	MOUDLES_MIN = 0,
	MOUDLES_NORMAL = 1,
	MOUDLES_THREEARMY = 2,
};

struct FMailAttach
{
	int8 item_Type;
	int32 item_id;
	int32 item_num;
};

struct FNetMail
{
	int64 mailguid;
	int32 mailID;
	FString title;
	FString content;
	FString mailsender;
	FString filepath; //now just include img path
	int mailType;
	TArray<FMailAttach> attacharr;
	int64 sendtime;
	int64 effectiveTime;
	int8 HaveRead;
};

enum STATE_TYPE
{
	STATE_TYPE_GOLD_PLUS_50 = 1,
};
