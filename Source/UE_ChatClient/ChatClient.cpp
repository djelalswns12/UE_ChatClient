// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatClient.h"

bool UChatClient::Connect()
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
	FString address = TEXT("127.0.0.1");
	int32 port = 4444;
	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Trying to connect.")));

	if (Socket->Connect(*addr)) {
		ConnectionState = true;
		return true;
	}
	return false;
}
void UChatClient::SendData(FString& text)
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
void UChatClient::ReceiveData()
{
	uint32 Size = 0;
	if (Socket==nullptr) 
	{
		UE_LOG(LogTemp, Log, TEXT("SOCKET ERROR 1"));
		return;
	}
	if (Socket->GetConnectionState() != ESocketConnectionState::SCS_Connected)
	{
		UE_LOG(LogTemp, Log, TEXT("SOCKET ERROR 2"));
		return;
	}
	if (Socket->HasPendingData(Size))
	{
		int read = 0;
		if (Socket->Recv(DataBuffer + DataBufferPoint, 1024 - DataBufferPoint, read))
		{
			DataBufferPoint += read;
			UE_LOG(LogTemp, Log, TEXT("DataBufferPoint %d"), DataBufferPoint);
		}
	}
	if (DataBufferPoint > 0) {
		wchar_t* wc = new wchar_t[DataBufferPoint + 1];
		mbstowcs(wc, (char*)DataBuffer, DataBufferPoint + 1);
		FString data(wc);
		UE_LOG(LogTemp, Log, TEXT("\n Recv Data ->> %s"), *data);
		CurOrder = data;
		//OrderBuffer.Enqueue(data);
		//Excute(data);
		for (int i = 0; i < DataBufferPoint; i++) {
			DataBuffer[i] = 0;
		}
		DataBufferPoint = 0;
	}
	//Excute();
}
bool UChatClient::GetConnectionState()
{
	return ConnectionState;
}