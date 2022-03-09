// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatClient.h"

void UChatClient::Connect()
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
	FString address = TEXT("127.0.0.1");
	int32 port =4444;
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
	setlocale(LC_ALL, "korean");
	text += "\r\n";
	int32 BytesSent = 0;

	char c[1024];
	
	TArray<uint8> arr;
	wchar_t* da = text.GetCharArray().GetData();
	int len = wcstombs(c, da, 1024);
	for (int i = 0; i < len; i++)
	{
		arr.Add(c[i]);
	}

	//auto data = UintConvert(text);
	Socket->Send(arr.GetData(), len, BytesSent);
}

FString UChatClient::ReceiveData() 
{
	uint32 Size;
	TArray<uint8> ReceivedData;
	if(Socket->HasPendingData(Size))
	{
		UE_LOG(LogTemp, Log, TEXT("Size %d"), Size);
		ReceivedData.SetNum(Size);
		int32 Read = 0;
		Socket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);	

		wchar_t wc[1024];
		int len=mbstowcs(wc, (char*)ReceivedData.GetData() ,1024);
		FString readData(wc);
		return readData;
	}
	return "";
}
bool UChatClient::GetConnectionState()
{
	return ConnectionState;
}