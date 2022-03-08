// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatClient.h"

void UChatClient::Connect()
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
	FString address = TEXT("127.0.0.1");
	int32 port = 4444;
	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Trying to connect.")));

	ConnectionState= Socket->Connect(*addr);
}

void UChatClient::SendData(FString text) 
{
	text += "\r\n";
	auto data = UintConvert(text);
	uint8* msg = data.GetData();
	int32 BytesSent = 0;
	Socket->Send(msg, data.Num(),BytesSent);
	
}

void UChatClient::ReceiveData() 
{
	uint8 Buffer[1024] = { 0 };
	int32 DataLen = 0;
	uint32 Size;
	TArray<uint8> ReceivedData;
	if(Socket->HasPendingData(Size))
	{
		UE_LOG(LogTemp, Log, TEXT("Size %d"), Size);
		ReceivedData.SetNum(Size);
		int32 Read = 0;
		Socket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);	
		FString s = UintConvertToFString(ReceivedData);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Data is Come : %s"), *s));
	}
	//if (Socket->Recv(Buffer, sizeof(Buffer) - 1, DataLen, ESocketReceiveFlags::None))
	//{
	//	//FString s = BytesToString(Buffer,10);
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Data is Come")));
	//	
	//}
}
TArray<uint8> UChatClient::UintConvert(FString msg)
{
	TArray<uint8> tr_int8;
	TCHAR* pSendData = msg.GetCharArray().GetData();
	int32 nDataLen = FCString::Strlen(pSendData);
	for (int i = 0; i < nDataLen; i++)
	{
		uint8* dst = (uint8*)TCHAR_TO_UTF8(pSendData);
		tr_int8.Add(*dst);
		pSendData++;
	}
	return tr_int8;
}
FString UChatClient::UintConvertToFString(TArray<uint8>& BinaryArray)
{
	//(Create a string from a byte array!)
	const std::string cstr(reinterpret_cast<const char*>(BinaryArray.GetData()), BinaryArray.Num());
	//(FString can take in the c_str() of a std::string)
	return FString(cstr.c_str());
}
bool UChatClient::GetConnectionState()
{
	return ConnectionState;
}