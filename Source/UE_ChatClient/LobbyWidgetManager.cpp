#include "LobbyWidgetManager.h"
#include "ClientGameInstance.h"
void ULobbyWidgetManager::NativeConstruct()
{
	Super::NativeConstruct();
	GameIns = Cast<UClientGameInstance>(GetWorld()->GetGameInstance());

	SendButton = Cast<UButton>(GetWidgetFromName(TEXT("SendButton")));
	RecvDataScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("RecvDataScrollBox")));
	SendDataTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("SendDataTextBox")));

	RoomScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("RoomListScroll")));
	UserScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("UserListScroll")));

	RoomChatPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("RoomChatPanel")));
	RoomChatOutBtn = Cast<UButton>(GetWidgetFromName(TEXT("RoomChatOutBtn")));

	//대화방 입장 팝업
	RoomEnterPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("RoomEnterPanel")));
	RoomEnterBtn= Cast<UButton>(GetWidgetFromName(TEXT("RoomEnterBtn")));
	RoomCancleBtn= Cast<UButton>(GetWidgetFromName(TEXT("RoomCancleBtn")));
	//유저정보 팝업
	UserPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("UserPanel")));
	SendTMsgBox= Cast<UButton>(GetWidgetFromName(TEXT("endTMsgBox")));

	UserPanelOutBtn= Cast<UButton>(GetWidgetFromName(TEXT("UserPanelOutBtn")));
	UserInfoText= Cast<UTextBlock>(GetWidgetFromName(TEXT("UserInfoText")));
	TMsgBox= Cast<UEditableTextBox>(GetWidgetFromName(TEXT("TMsgBox")));

	// 버튼 클릭시 호출될 델리게이트에 함수를 등록한다
	SendButton->OnClicked.AddDynamic(this, &ULobbyWidgetManager::SendButtonEvent);
	RoomChatOutBtn->OnClicked.AddDynamic(this, &ULobbyWidgetManager::PopUpRoomChatPannel);
	MakeBtnListPool();
}

void ULobbyWidgetManager::SendButtonEvent()
{
	FString data = SendDataTextBox->Text.ToString();
	GameIns->SendMsg(data);
	//AddRoomSlot(TEXT("hello"));
	//GameIns->LoginEvent(*LoginInputTextBox->Text.ToString());
}

void ULobbyWidgetManager::AddText(FString txt) {
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *txt);

	UTextBlock* tstText = NewObject<UTextBlock>(UTextBlock::StaticClass());
	tstText->SetText(FText::FromString(txt));

	RecvDataScrollBox->AddChild(tstText);
	RecvDataScrollBox->ScrollToEnd();

}
void ULobbyWidgetManager::MakeBtnListPool() 
{
	for (int i = 0; i < 64; i++)
	{
		FString data = TEXT("no" + i);
		AddRoomSlot(data);
		AddUserSlot(data);
	}
	//UE_LOG(LogTemp, Log, TEXT("ROOM SET CLEAR"));
}
void  ULobbyWidgetManager::PopUpRoomChatPannel() 
{
		if (RoomChatPanel->GetVisibility() ==ESlateVisibility::Hidden) {
			RoomChatPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		else {
			RoomChatPanel->SetVisibility(ESlateVisibility::Hidden);
		}
}
void  ULobbyWidgetManager::SetRoomChatPannel(TArray<FString>& data)
{

}
void  ULobbyWidgetManager::SetUserPannel(TArray<FString>& data)
{

}
void  ULobbyWidgetManager::ChangeUserList(TArray<FString>& data)
{
	FMargin margin(0, 10, 0, 17);
	int curUserCnt = data.Num() - preUserCnt;
	//UE_LOG(LogTemp, Log, TEXT("(CHANGE EVENT )NOW SET ROOM CNT IS :  ( cur(set)>> %d /  pre >> %d )"), curRoomCnt, preRoomCnt);
	if (curUserCnt > 0)
	{
		for (int i = preUserCnt; i < (preUserCnt + curUserCnt); i++)
		{
			AttachBtn(UserList[i], UserScrollBox, margin);
		}
	}
	else if (curUserCnt < 0)
	{
		for (int i = preUserCnt - 1; i >= preUserCnt + curUserCnt; i--)
		{
			UserScrollBox->RemoveChild(UserList[i]);
		}
	}
	preUserCnt += curUserCnt;
	for (int i = 0; i < preUserCnt; i++)
	{
		EditText(UserList[i], data[i]);
		UserList[i]->SetVisibility(ESlateVisibility::Visible);
	}
}
void  ULobbyWidgetManager::ChangeRoomList(TArray<FString>& data) 
{
	FMargin margin(0, 35, 0, 53);
	int curRoomCnt = data.Num() - preRoomCnt;
	
	//UE_LOG(LogTemp, Log, TEXT("(CHANGE EVENT )NOW SET ROOM CNT IS :  ( cur(set)>> %d /  pre >> %d )"), curRoomCnt, preRoomCnt);
	if (curRoomCnt > 0) 
	{
		for (int i = preRoomCnt; i < (preRoomCnt + curRoomCnt); i++)
		{
			AttachBtn(RoomList[i],RoomScrollBox,margin);
		}
	}
	else if (curRoomCnt < 0) 
	{
		for (int i = preRoomCnt-1; i >= preRoomCnt+curRoomCnt; i--) 
		{
			RoomScrollBox->RemoveChild(RoomList[i]);
		}
	}
	preRoomCnt += curRoomCnt;
	for (int i = 0; i < preRoomCnt; i++) 
	{
		EditText(RoomList[i],data[i]);
		RoomList[i]->SetVisibility(ESlateVisibility::Visible);
	}
}
void ULobbyWidgetManager::AddRoomSlot(FString& txt)
{
	UTextBlock* text = NewObject<UTextBlock>(UTextBlock::StaticClass());
	text->SetText(FText::FromString(txt));
	text->SetRenderScale(FVector2D(1,1 / float(3)));

	UButton* btn = NewObject<UButton>(UButton::StaticClass());
	btn->SetRenderScale(FVector2D(1, 3));
	btn->AddChild(text);
	btn->SetVisibility(ESlateVisibility::Hidden);
	RoomList.Add(btn);
	UE_LOG(LogTemp, Log, TEXT("A ROOM IS SETTING"));
	//RoomScrollBox->AddChild(btn);
}
void ULobbyWidgetManager::AddUserSlot(FString& txt)
{
	UTextBlock* text = NewObject<UTextBlock>(UTextBlock::StaticClass());
	text->SetText(FText::FromString(txt));
	//text->SetRenderScale(FVector2D(1, 1 / float(1.5)));

	UButton* btn = NewObject<UButton>(UButton::StaticClass());
	//btn->SetRenderScale(FVector2D(1, 1.5));
	btn->AddChild(text);
	btn->SetVisibility(ESlateVisibility::Hidden);
	UserList.Add(btn);
	UE_LOG(LogTemp, Log, TEXT("A USER IS SETTING"));
	//RoomScrollBox->AddChild(btn);
}
void ULobbyWidgetManager::AttachBtn(UWidget* btn, UScrollBox* scroll, FMargin& margin)
{
	auto setBtn = Cast<UButton>(btn);
	if (setBtn == nullptr) 
	{
		return;
	}
	scroll->AddChild(btn);
	// (0, 35, 0, 53)
	Cast<UScrollBoxSlot>(btn->Slot)->SetPadding(margin);
}
void ULobbyWidgetManager::EditText(UButton* btn,FString& data)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *data);
	Cast<UTextBlock>(btn->GetChildAt(0))->SetText(FText::FromString(data));
}
void ULobbyWidgetManager::Login() {
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *txt);
	GameIns->client->Connect();

}