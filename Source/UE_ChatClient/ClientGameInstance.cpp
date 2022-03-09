// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientGameInstance.h"

void UClientGameInstance::Init() 
{
	Super::Init();
	client = NewObject<UChatClient>(UChatClient::StaticClass());
	UE_LOG(LogTemp, Log, TEXT("Client is On"));
}
void UClientGameInstance::Test() 
{
	
}
void UClientGameInstance::ReceiveEvent()
{
	if (GetSocketConnectionState()) 
	{
		client->ReceiveData();
		/*FString s=client->ReceiveData();
		if (s.Len() > 0) 
		{
			class AUE_ChatClientGameModeBase* gameMode = Cast<AUE_ChatClientGameModeBase>(GetWorld()->GetAuthGameMode());
			TArray<FString> outData;
			s.ParseIntoArray(outData, TEXT("%HEADER%"));

			 UE_LOG(LogTemp,Log,TEXT("orin:%s outData0: %s %d %d"),*s,*outData[0],1==1,(FString("hi")=="hi"));
			 int32 findIdx = outData[0].Find(TEXT("LOGINSUCCESS"));
			if (findIdx>0) {
				gameMode->ChangeMenuWidget(gameMode->LobbyWidget);
			}
			else {
				class ULobbyWidgetManager* widget =Cast<ULobbyWidgetManager>(gameMode->CurrentWidget);
				widget->AddText(s);
			}
		}
		else 
		{
			UE_LOG(LogTemp, Log, TEXT("No Data"));
		}*/
	}
}
void UClientGameInstance::LoginEvent(FString name) 
{
	client->SendData("LOGIN/U " + name);
}
void UClientGameInstance::ConnectEvent()
{
	if (client->Connect()) {

	}
	return;
}
void UClientGameInstance::SendMsg(FString msg) 
{
	client->SendData(msg);
}

bool UClientGameInstance::GetSocketConnectionState() {
	return client->GetConnectionState();
}

