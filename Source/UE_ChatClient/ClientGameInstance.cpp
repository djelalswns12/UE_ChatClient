// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientGameInstance.h"

void UClientGameInstance::Init() 
{
	Super::Init();
	client = NewObject<UChatClient>(UChatClient::StaticClass());
	UE_LOG(LogTemp, Log, TEXT("hello~~~~~~~~~~~~~~~~"));

}
void UClientGameInstance::Test() 
{
	
}
void UClientGameInstance::ReceiveEvent()
{
	if (GetSocketConnectionState()) 
	{
//--------------------------------------//
//	SOCKET
//-------------------------------------//
		//FString s=client->ReceiveData();

//--------------------------------------//
//	FSocket
//-------------------------------------//
		
		FString s=client->FReceiveData();
		if (s.Len() > 0) 
		{
			class AUE_ChatClientGameModeBase* gameMode = Cast<AUE_ChatClientGameModeBase>(GetWorld()->GetAuthGameMode());
			class UAuthWidgetManager* widget = Cast<UAuthWidgetManager>(gameMode->CurrentWidget);
			widget->AddText(s);
		}
	}
}
void UClientGameInstance::LoginEvent(FString msg) 
{
	if (!client->GetConnectionState()) {
		client->Connect();
		//client->ServerOn();
		return;
	}
	//FString data = "안녕화살벌\r\n";
	//client->SendData(&client->mySocket,data);

	if (GetSocketConnectionState() == false)
	{
		if (GetSocketConnectionState() == ESocketConnectionState::SCS_Connected)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connect Success ! ")));
			return;
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connect Fail, Check your Network ! ")));
		return;
	}
	client->SendData("LOGIN "+msg);
	UE_LOG(LogTemp, Log, TEXT("hello~~~~~~~~~~~~~~~~"));
}

bool UClientGameInstance::GetSocketConnectionState() {
	return client->GetConnectionState();
}