#pragma once
#include "DETNetCmn.h"
#include "DETNetCode.h"
#include "DETNetStruct.h"
class FSocket;
class ISocketSubsystem;

class DETTcpStreamBuffer
{
protected:
	TArray<uint8> Buffer;					// �����������ݻ�����
	int	MaxSize;							// ���Դ�ŵ�������ݳ���
	int	Size;								// �Ѿ���ŵ������ܳ���
	int	Begin;								// ���ݿ�ʼ��λ��
	int	ScrollSize;							// ��ȡ�����ݵ���Begin����ScrollSize���ͽ��������ݹ�������ͷ��
	int	BaseMaxSize;
	int MaxExtendCount;						// �������������
	int	CurrentExtend;						// ��ǰ�������
public:
	uint8* GetBuf(); 						// Ŀǰ���ݵĿ�ʼָ�룬����һ���������(Free)ǰ��Ч
	int	GetMaxSize();
	int	GetSize(); 							// ����Ѿ����ڵ����ݳ���
	uint8* GetTail(); 						// ���βָ��
	int	GetSizeLeft();						// ��û�������ӵ����ݳ���
public:
	DETTcpStreamBuffer();
	~DETTcpStreamBuffer();
	int		Init(int nMaxSize, int nScrollSize);
	int		Release();								// �ս�(�����������Զ�����)
	void	Clean();								// ��������е���������
	uint8* InAlloc(int nSize);						// ������뻺���ڴ棬������д���ݣ���������뿽��һ��
	bool	In(const uint8* pData, int nSize);		// ���볤��ΪnSize������
	int		Out(uint8* pData, int* pnSize);			// ȡ�����ݣ�*pnSize������ȡ�õ����ݳ��ȣ�����0��ʾ�ɹ�������ݣ�-1��ʾû������
	void	Out(int nSize);							// �ͷ�����
	bool	Resize(int nSize);						//���·����ڴ����
};

class DETNET_EXPORT DETNetTcp
{
	enum
	{
		Closed,
		Connecting,
		Connected,
		ConnectFailed,
	};
	struct DETFrameHeader
	{
		uint32 Size;				//����С
		uint32 ID;					//Э���
	};
#define HEADER_SIZE sizeof(DETFrameHeader)
public:
	DETNetTcp();
	virtual ~DETNetTcp();
private:
	ISocketSubsystem* SocketSubsystem;
	FSocket* Socket;

	TArray<uint8> ReceiveBuffer;
	TArray<uint8> FrameBuffer;
	DETTcpStreamBuffer* StreamBuffer;

	int ConnectState;

	FTimespan PingInterval, PongInterval;
	FDateTime LastSent;
	FDateTime LastReceivedPacket;
	FDateTime LastReceivedFrame;
	FTimerHandle HeartbeatTimer;

	/* Handlers for websocket events */
	virtual void OnConnected();
	virtual void OnConnectionError(const FString& Error);
	virtual void OnClosed(bool Initiative);
	virtual void OnTick(float DeltaTime);

	int CheckFrame();
	void Clear();

protected:
	FString MatchServerAddr;
public:
	void Init();
	int Connect(const FString& _Host = TEXT(""));
	void Close(bool Initiative = true);
	void Tick(float DeltaTime);

	template <typename InStructType>
	int Send(const InStructType& Data)
	{
		if (Socket == nullptr)
		{
			return -1;
		}
		auto cmd = dynamic_cast<const FICmd*>(&Data);
		if (cmd == nullptr)
		{
			return -2;
		}
		FString JsonString;
		DHJsonUtils::ToJson(&Data, JsonString);
		std::string str(TCHAR_TO_UTF8(*JsonString));
		DETFrameHeader header;
		header.Size = (uint32)str.size();
		header.ID = (uint32)cmd->GetID();
		TArray<uint8> Buf((const unsigned char*)str.c_str(), (int32)str.size());
		DETNetEncode encode(uint32(HEADER_SIZE + header.Size));
		encode.Encode(header.Size);
		encode.Encode(header.ID);
		encode.Encode(Buf);
		int32 sendBytes;
		Socket->Send(encode.GetBuffer().GetData(), encode.GetBufferSize(), sendBytes);
		LastSent = FDateTime::UtcNow();
		return 0;
	}

};