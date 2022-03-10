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
	UE_LOG(LogTemp, Log, TEXT("Client is On"));
}
void UClientGameInstance::ReceiveEvent()
{
	//Called NetWorkManager
	if (GetSocketConnectionState()) 
	{
		GameMode = Cast<AUE_ChatClientGameModeBase>(GetWorld()->GetAuthGameMode());
		client->ReceiveData();
		if (!client->CurOrder.IsEmpty()) {
			TArray<FString> outData;
			client->CurOrder.ParseIntoArray(outData, TEXT("<H>"));
			FString SetOrder;
			SetOrder.Empty();
			
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
					if (SetOrder.Find(TEXT("LS")) >= 0)
					{
						UE_LOG(LogTemp, Log, TEXT("LOGINSUCCESS DATA"));
						client->IsLogin = true;
						GameMode->SetLobby();
					}
					if (SetOrder.Find(TEXT("LF")) >= 0)
					{
						UE_LOG(LogTemp, Log, TEXT("LOGINFAIL DATA"));
						client->IsLogin = false;
						Cast<UAuthWidgetManager>(GameMode->CurrentWidget)->PopUp2Visible();
						//GameMode->SetLobby();
					}
					if (SetOrder.Find(TEXT("ST")) >= 0)
					{
						TArray<FString> roomUserListData;
						data.ParseIntoArray(roomUserListData, TEXT("\r\n"));
						roomUserListData.RemoveAt(0);
						roomUserListData.RemoveAt(0);
						roomUserListData.RemoveAt(0);
						roomUserListData.RemoveAt(roomUserListData.Num() - 1);
						Cast<ULobbyWidgetManager>(GameMode->CurrentWidget)->ChangeRoomUserList(roomUserListData);
					}
					else if (SetOrder.Find(TEXT("US")) >= 0)
					{
						UE_LOG(LogTemp, Log, TEXT("US"));
						TArray<FString> userListData;
						data.ParseIntoArray(userListData, TEXT("\r\n"));
						userListData.RemoveAt(0);
						userListData.RemoveAt(userListData.Num() - 1);
						Cast<ULobbyWidgetManager>(GameMode->CurrentWidget)->ChangeUserList(userListData);
					}
					else if (SetOrder.Find(TEXT("LT")) >= 0)
					{
						UE_LOG(LogTemp, Log, TEXT("LT"));
						TArray<FString> roomListData;
						data.ParseIntoArray(roomListData, TEXT("\r\n"));
						roomListData.RemoveAt(0);
						roomListData.RemoveAt(roomListData.Num() - 1);
						Cast<ULobbyWidgetManager>(GameMode->CurrentWidget)->ChangeRoomList(roomListData);
					}
					else if (SetOrder.Find(TEXT("MS")) >= 0)
					{
						UE_LOG(LogTemp, Log, TEXT("Message By Service"));
						if (client->IsLogin) 
						{
							//Cast<ULobbyWidgetManager>(GameMode->CurrentWidget)->AddText(data);
						}
					}
					else if (SetOrder.Find(TEXT("UM")) >= 0)
					{
						UE_LOG(LogTemp, Log, TEXT("User Msg"));
						if (client->IsLogin) 
						{
							Cast<ULobbyWidgetManager>(GameMode->CurrentWidget)->AddText(data);
						}
					}
					else if (SetOrder.Find(TEXT("RS")) >= 0)
					{
						UE_LOG(LogTemp, Log, TEXT("ROOM MAKE SUCCESS"));
						if (client->IsLogin)
						{
							Cast<ULobbyWidgetManager>(GameMode->CurrentWidget)->SetRoomChatPanelVisible(ESlateVisibility::SelfHitTestInvisible);
						}
					}
					else if (SetOrder.Find(TEXT("PM")) >= 0)
					{
						UE_LOG(LogTemp, Log, TEXT("POP UP MSG"));
						if (client->IsLogin)
						{
							Cast<ULobbyWidgetManager>(GameMode->CurrentWidget)->SetMsgPanel(data);
						}
					}
					UE_LOG(LogTemp, Log, TEXT("\n %d번째>>> HEADER NAME IS : %s\n"),i,*SetOrder);
					SetOrder.Empty();
					continue;
				}
				//UE_LOG(LogTemp, Log, TEXT("\n %d번째>>> 데이터 소실  ( set : %s , outd[%d] : %s ) \n"), i,*SetOrder,i,*outData[i]);
			}

			client->CurOrder.Empty();

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
void UClientGameInstance::OnUserPopUp(TArray<FString>& data) {
	GameMode = Cast<AUE_ChatClientGameModeBase>(GetWorld()->GetAuthGameMode());
	Cast<ULobbyWidgetManager>(GameMode->CurrentWidget)->PopUpUserPannel();
	Cast<ULobbyWidgetManager>(GameMode->CurrentWidget)->SetUserPannel(data);
}
void UClientGameInstance::OnRoomEnterPopUp(TArray<FString>& data) {
	GameMode = Cast<AUE_ChatClientGameModeBase>(GetWorld()->GetAuthGameMode());
	Cast<ULobbyWidgetManager>(GameMode->CurrentWidget)->PopUpRoomEnterPannel();
	Cast<ULobbyWidgetManager>(GameMode->CurrentWidget)->SetRoomChatPannel(data);

}
bool UClientGameInstance::GetSocketConnectionState() {
	return client->GetConnectionState();
}

void UClientGameInstance::SetSettingUserName(FString data)
{
	TArray<FString> arr;
	data.ParseIntoArray(arr, TEXT(":"));
	SettingUserName= arr[1];
	UE_LOG(LogTemp, Log, TEXT("세팅된 이름은 :%s"), *SettingUserName);
}
void UClientGameInstance::SetSettingRoomName(FString data)
{
	FString num = "";
	int pos=data.Find(TEXT("번"));
	for (int i = 1; i < pos; i++) {
		num += data[i];
	}
	SettingRoomNumber = num;
	SettingRoomNumber.TrimStartInline();
	UE_LOG(LogTemp, Log, TEXT("세팅된 방번호는 :%s"), *SettingRoomNumber);
}