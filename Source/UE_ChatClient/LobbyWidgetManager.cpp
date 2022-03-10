#include "LobbyWidgetManager.h"
#include "ClientGameInstance.h"
void ULobbyWidgetManager::NativeConstruct()
{
	Super::NativeConstruct();
	GameIns = Cast<UClientGameInstance>(GetWorld()->GetGameInstance());

	RoomScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("RoomListScroll")));
	UserScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("UserListScroll")));

	//대화방
	RoomChatPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("RoomChatPanel")));
	RoomChatOutBtn = Cast<UButton>(GetWidgetFromName(TEXT("RoomChatOutBtn")));
	SendButton = Cast<UButton>(GetWidgetFromName(TEXT("SendButton")));
	RecvDataScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("RecvDataScrollBox")));
	SendDataTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("SendDataTextBox")));
	RoomUserListScroll= Cast<UScrollBox>(GetWidgetFromName(TEXT("RoomUserListScroll")));

	//대화방 입장 팝업
	RoomEnterPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("RoomEnterPanel")));
	RoomEnterBtn= Cast<UButton>(GetWidgetFromName(TEXT("RoomEnterBtn")));
	RoomCancleBtn= Cast<UButton>(GetWidgetFromName(TEXT("RoomCancleBtn")));
	RoomInfoText= Cast<UTextBlock>(GetWidgetFromName(TEXT("RoomInfoText")));

	//유저정보 팝업
	UserPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("UserPanel")));
	SendTMsgBox= Cast<UButton>(GetWidgetFromName(TEXT("SendTMsgBox")));
	UserPanelOutBtn= Cast<UButton>(GetWidgetFromName(TEXT("UserPanelOutBtn")));
	UserInfoText= Cast<UTextBlock>(GetWidgetFromName(TEXT("UserInfoText")));
	TMsgBox= Cast<UEditableTextBox>(GetWidgetFromName(TEXT("TMsgBox")));
	InviteBtn= Cast<UButton>(GetWidgetFromName(TEXT("InviteBtn")));

	//대화방 생성 팝업
	MakeRoomPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("MakeRoomPanel")));
	MakeRoomBtn = Cast<UButton>(GetWidgetFromName(TEXT("MakeRoomBtn")));
	RoomMakeBtn = Cast<UButton>(GetWidgetFromName(TEXT("RoomMakeBtn")));
	RoomMakeOutBtn = Cast<UButton>(GetWidgetFromName(TEXT("RoomMakeOutBtn")));
	SetRoomNameText = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("SetRoomNameText")));
	SetRoomCntText = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("SetRoomCntText")));

	//알림 관련
	MsgPanel= Cast<UCanvasPanel>(GetWidgetFromName(TEXT("MsgPanel")));
	MsgOutBtn = Cast<UButton>(GetWidgetFromName(TEXT("MsgOutBtn")));
	MyMsgText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MyMsgText")));

	// 버튼 클릭시 호출될 델리게이트에 함수를 등록한다
	SendButton->OnClicked.AddDynamic(this, &ULobbyWidgetManager::SendButtonEvent);

	//대화방 입장 팝업 관련
	RoomCancleBtn->OnClicked.AddDynamic(this, &ULobbyWidgetManager::PopUpRoomEnterPannel);
	RoomEnterBtn->OnClicked.AddDynamic(this, &ULobbyWidgetManager::EnterRoom);

	//유저정보 팝업 관련
	UserPanelOutBtn->OnClicked.AddDynamic(this, &ULobbyWidgetManager::PopUpUserPannel);
	SendTMsgBox->OnClicked.AddDynamic(this, &ULobbyWidgetManager::ToUser);
	InviteBtn->OnClicked.AddDynamic(this, &ULobbyWidgetManager::InMsg);
	//대화방 내부 관련
	RoomChatOutBtn->OnClicked.AddDynamic(this, &ULobbyWidgetManager::OutRoom);

	//대화방 생성 관련
	MakeRoomBtn->OnClicked.AddDynamic(this, &ULobbyWidgetManager::PopUpMakeRoomPanel);
	RoomMakeBtn->OnClicked.AddDynamic(this, &ULobbyWidgetManager::MakeRoomEvent);
	RoomMakeOutBtn->OnClicked.AddDynamic(this, &ULobbyWidgetManager::PopUpMakeRoomPanel);

	//팝업메세지 관련
	MsgOutBtn->OnClicked.AddDynamic(this, &ULobbyWidgetManager::CloseMsgPanel);

	MakeBtnListPool();
}
void ULobbyWidgetManager::PopUpMakeRoomPanel() 
{
	if (MakeRoomPanel->GetVisibility() == ESlateVisibility::Hidden) 
	{
		MakeRoomPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else 
	{
		MakeRoomPanel->SetVisibility(ESlateVisibility::Hidden);
	}
}
void ULobbyWidgetManager::CloseMsgPanel()
{
	MsgPanel->SetVisibility(ESlateVisibility::Hidden);
}
void ULobbyWidgetManager::SetMsgPanel(FString& data)
{
	MyMsgText->SetText(FText::FromString(data));
	MsgPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void ULobbyWidgetManager::SetRoomChatPanelVisible(ESlateVisibility type)
{
	RecvDataScrollBox->ClearChildren();
	RoomChatPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}
void ULobbyWidgetManager::MakeRoomEvent()
{
	PopUpMakeRoomPanel();
	FString data = "O "+SetRoomCntText->Text.ToString() + " " + SetRoomNameText->Text.ToString();
	SetRoomCntText->SetText(FText::FromString(""));
	SetRoomNameText->SetText(FText::FromString(""));
	GameIns->SendMsg(data);
}

void ULobbyWidgetManager::SendButtonEvent()
{
	FString data = SendDataTextBox->Text.ToString();
	SendDataTextBox->SetText(FText::FromString(""));
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
		AddRoomUserSlot(data);
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
void ULobbyWidgetManager::OutRoom()
{
	PopUpRoomChatPannel();
	FString data = "/Q";
	GameIns->SendMsg(data);
}
void  ULobbyWidgetManager::EnterRoom()
{
	//PopUpRoomChatPannel();
	PopUpRoomEnterPannel();
	FString data ="J " + GameIns->SettingRoomNumber;
	GameIns->SendMsg(data);
}
void  ULobbyWidgetManager::InMsg()
{
	FString data;
	if (RoomChatPanel->GetVisibility() == ESlateVisibility::Hidden)
	{
		data = "대화방 참여시 초대할 수 있습니다.";
		SetMsgPanel(data);
	}
	else 
	{
		data = "/IN " + GameIns->SettingUserName;
	}
	GameIns->SendMsg(data);
}
void  ULobbyWidgetManager::ToUser()
{
	FString data;
	if (RoomChatPanel->GetVisibility() == ESlateVisibility::Hidden){
	data = "TO " + GameIns->SettingUserName + " " + TMsgBox->Text.ToString();
	}
	else {
	data = "/TO " + GameIns->SettingUserName + " " + TMsgBox->Text.ToString();
	}
	TMsgBox->SetText(FText::FromString(""));
	GameIns->SendMsg(data);
}
void  ULobbyWidgetManager::PopUpUserPannel() 
{
	if (UserPanel->GetVisibility() == ESlateVisibility::Hidden) 
	{
		UserPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else 
	{
		UserPanel->SetVisibility(ESlateVisibility::Hidden);
	}
}
void  ULobbyWidgetManager::PopUpRoomEnterPannel()
{
	if (RoomEnterPanel->GetVisibility() == ESlateVisibility::Hidden) 
	{
		RoomEnterPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else 
	{
		RoomEnterPanel->SetVisibility(ESlateVisibility::Hidden);
	}
}
void  ULobbyWidgetManager::SetRoomChatPannel(TArray<FString>& data)
{
	FString s = "";
	for (int i = 0; i < data.Num(); i++) {
		if (i == 0) 
		{
			GameIns->SetSettingRoomName(data[i]);
		}
		s += data[i] + "\n";
	}
	RoomInfoText->SetText(FText::FromString(s));
}
void  ULobbyWidgetManager::SetUserPannel(TArray<FString>& data)
{
	FString s = "";

	for (int i = 0; i < data.Num(); i++) {
		if (i == 0)
		{
			GameIns->SetSettingUserName(data[i]);
		}
		s += data[i]+"\n";
	}
	UserInfoText->SetText(FText::FromString(s));
}
void  ULobbyWidgetManager::ChangeRoomUserList(TArray<FString>& data)
{
	FMargin margin(0, 10, 0, 17);

	int curUserCnt = data.Num() - preRoomUserCnt;
	if (curUserCnt > 0)
	{
		for (int i = preRoomUserCnt; i < (preRoomUserCnt + curUserCnt); i++)
		{
			AttachBtn(RoomUserList[i]->btn, RoomUserListScroll, margin);
		}
	}
	else if (curUserCnt < 0)
	{
		for (int i = preRoomUserCnt - 1; i >= preRoomUserCnt + curUserCnt; i--)
		{
			RoomUserListScroll->RemoveChild(RoomUserList[i]->btn);
		}
	}
	preRoomUserCnt += curUserCnt;
	for (int i = 0; i < preRoomUserCnt; i++)
	{
		EditText(RoomUserList[i], data[i]);
		RoomUserList[i]->btn->SetVisibility(ESlateVisibility::Visible);
	}
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
			AttachBtn(UserList[i]->btn, UserScrollBox, margin);
		}
	}
	else if (curUserCnt < 0)
	{
		for (int i = preUserCnt - 1; i >= preUserCnt + curUserCnt; i--)
		{
			UserScrollBox->RemoveChild(UserList[i]->btn);
		}
	}
	preUserCnt += curUserCnt;
	for (int i = 0; i < preUserCnt; i++)
	{
		EditTextForName(UserList[i], data[i]);
		UserList[i]->btn->SetVisibility(ESlateVisibility::Visible);
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
			AttachBtn(RoomList[i]->btn,RoomScrollBox,margin);
		}
	}
	else if (curRoomCnt < 0) 
	{
		for (int i = preRoomCnt-1; i >= preRoomCnt+curRoomCnt; i--) 
		{
			RoomScrollBox->RemoveChild(RoomList[i]->btn);
		}
	}
	preRoomCnt += curRoomCnt;
	for (int i = 0; i < preRoomCnt; i++) 
	{
		EditText(RoomList[i],data[i]);
		RoomList[i]->btn->SetVisibility(ESlateVisibility::Visible);
	}
}
void ULobbyWidgetManager::AddRoomSlot(FString& txt)
{
	UTextBlock* showText = NewObject<UTextBlock>(UTextBlock::StaticClass());
	showText->SetText(FText::FromString(txt));
	showText->SetRenderScale(FVector2D(1,1 / float(3)));

	
	UDataButton* btn = NewObject<UDataButton>(UDataButton::StaticClass());

	btn->btn = NewObject<UButton>(UButton::StaticClass());
	btn->btn->AddChild(showText);
	btn->btn->SetRenderScale(FVector2D(1, 3));
	btn->GameIns = GameIns;
	btn->SetEvent(1);
	btn->btn->SetVisibility(ESlateVisibility::Hidden);

	RoomList.Add(btn);
}
void ULobbyWidgetManager::AddUserSlot(FString& txt)
{
	UTextBlock* showText = NewObject<UTextBlock>(UTextBlock::StaticClass());
	showText->SetText(FText::FromString(txt));
	UDataButton* btn = NewObject<UDataButton>(UDataButton::StaticClass());
	btn->btn = NewObject<UButton>(UButton::StaticClass());
	btn->btn->AddChild(showText);
	btn->GameIns = GameIns;
	btn->SetEvent(0);
	btn->btn->SetVisibility(ESlateVisibility::Hidden);
	UserList.Add(btn);
}
void ULobbyWidgetManager::AddRoomUserSlot(FString& txt)
{
	UTextBlock* showText = NewObject<UTextBlock>(UTextBlock::StaticClass());
	showText->SetText(FText::FromString(txt));
	UDataButton* btn = NewObject<UDataButton>(UDataButton::StaticClass());
	btn->btn = NewObject<UButton>(UButton::StaticClass());
	btn->btn->AddChild(showText);
	btn->GameIns = GameIns;
	btn->SetEvent(0);
	btn->btn->SetVisibility(ESlateVisibility::Hidden);
	RoomUserList.Add(btn);
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
void ULobbyWidgetManager::EditText(UDataButton* btn,FString& data)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *data);
	btn->data = data;
	Cast<UTextBlock>(btn->btn->GetChildAt(0))->SetText(FText::FromString(data));
}
void ULobbyWidgetManager::EditTextForName(UDataButton* btn, FString& data)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *data);
	btn->data = data;
	FString name = btn->GetDataName();
	Cast<UTextBlock>(btn->btn->GetChildAt(0))->SetText(FText::FromString(name));
}
void ULobbyWidgetManager::Login() {
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *txt);
	GameIns->client->Connect();

}