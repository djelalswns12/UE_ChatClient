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
						TArray<FString> userListData;
						data.ParseIntoArray(userListData, TEXT("\r\n"));
						userListData.RemoveAt(0);
						userListData.RemoveAt(userListData.Num() - 1);
						Cast<ULobbyWidgetManager>(GameMode->CurrentWidget)->ChangeUserList(userListData);
					}
					else if (SetOrder.Find(TEXT("LT")) >= 0)
					{
						TArray<FString> roomListData;
						data.ParseIntoArray(roomListData, TEXT("\r\n"));
						roomListData.RemoveAt(0);
						roomListData.RemoveAt(roomListData.Num() - 1);
						Cast<ULobbyWidgetManager>(GameMode->CurrentWidget)->ChangeRoomList(roomListData);
					}
					else if (SetOrder.Find(TEXT("MSG")) >= 0)
					{
						UE_LOG(LogTemp, Log, TEXT("MSG DATA"));
						if (client->IsLogin) {
							Cast<ULobbyWidgetManager>(GameMode->CurrentWidget)->AddText(data);
						}
					}
					UE_LOG(LogTemp, Log, TEXT("\n %d번째>>> HEADER NAME IS : %s\n"),i,*SetOrder);
					SetOrder.Empty();
					continue;
				}
				//UE_LOG(LogTemp, Log, TEXT("\n %d번째>>> 데이터 소실  ( set : %s , outd[%d] : %s ) \n"), i,*SetOrder,i,*outData[i]);
			}
			client->CurOrder = "";

		}
	}
}
void UClientGameInstance::LoginEvent(FString& name)
{
	FString data = "LOGIN/U " + name;
	SendMsg(data);
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
void UClientGameInstance::SendMsg(FString& msg)
{
	client->SendData(msg);
}

bool UClientGameInstance::GetSocketConnectionState() {
	return client->GetConnectionState();
}

