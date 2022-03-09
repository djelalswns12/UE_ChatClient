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
		GameMode = Cast<AUE_ChatClientGameModeBase>(GetWorld()->GetAuthGameMode());
		client->ReceiveData();
		if (!client->CurOrder.IsEmpty()) {
			TArray<FString> outData;
			client->CurOrder.ParseIntoArray(outData, TEXT("<H>"));
			FString SetOrder="";
			for (int i = 0; i < outData.Num(); i++) 
			{
				if (SetOrder.IsEmpty()) {
					SetOrder = outData[i];
					continue;
				}
				else if(SetOrder==outData[i])
				{
					FString data=outData[i - 1];
					//set오더에 따라서
					if (SetOrder.Find(TEXT("LOGINSUCCESS")) >= 0)
					{
						UE_LOG(LogTemp, Log, TEXT("LOGINSUCCESS DATA"));
						client->IsLogin = true;
						GameMode->SetLobby();
					}
					if (SetOrder.Find(TEXT("LOGINFAIL")) >= 0)
					{
						UE_LOG(LogTemp, Log, TEXT("LOGINFAIL DATA"));
						client->IsLogin = false;
						//GameMode->SetLobby();
					}
					else if (SetOrder.Find(TEXT("US")) >= 0)
					{
						TArray<FString> a;
						int ra = FMath::RandRange(2, 15);
						UE_LOG(LogTemp, Log, TEXT("BTN SPAWN CNT : %d "),ra);
						for (int t = 0; t < ra; t++) {
							a.Add("hi"+t);
						}
						Cast<ULobbyWidgetManager>(GameMode->CurrentWidget)->ChangeRoomList(a);
					}
					else if (SetOrder.Find(TEXT("MSG")) >= 0)
					{
						UE_LOG(LogTemp, Log, TEXT("MSG DATA"));
						if (client->IsLogin) {
							Cast<ULobbyWidgetManager>(GameMode->CurrentWidget)->AddText(data);
						}
					}
					UE_LOG(LogTemp, Log, TEXT("\n %d번째>>> HEADER NAME IS : %s\n"),i,*SetOrder);
					SetOrder = "";
					continue;
				}
				//UE_LOG(LogTemp, Log, TEXT("\n %d번째>>> 데이터 소실  ( set : %s , outd[%d] : %s ) \n"), i,*SetOrder,i,*outData[i]);
			}
			client->CurOrder = "";

		}
	}
}
void UClientGameInstance::LoginEvent(FString name) 
{
	SendMsg("LOGIN/U " + name);
}
void UClientGameInstance::ConnectEvent()
{
	GameMode = Cast<AUE_ChatClientGameModeBase>(GetWorld()->GetAuthGameMode());
	if (client->Connect()) {
		Cast<UAuthWidgetManager>(GameMode->CurrentWidget)->PopUp(TEXT("닉네임을 입력하세요"), TEXT("Login"), true);
	}
	else {
		Cast<UAuthWidgetManager>(GameMode->CurrentWidget)->PopUp(TEXT("서버에 접속할 수 없습니다."), TEXT("Ok"), false);
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

