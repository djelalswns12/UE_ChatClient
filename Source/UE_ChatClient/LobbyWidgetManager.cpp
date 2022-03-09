#include "LobbyWidgetManager.h"

void ULobbyWidgetManager::NativeConstruct()
{
	Super::NativeConstruct();
	GameIns = Cast<UClientGameInstance>(GetWorld()->GetGameInstance());

	SendButton = Cast<UButton>(GetWidgetFromName(TEXT("SendButton")));
	RecvDataScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("RecvDataScrollBox")));
	SendDataTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("SendDataTextBox")));

	//ScrollBox* RoomScrollBox;
	RoomScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("RoomListScroll")));
	//UCanvasPanel* RoomSlot;
	RoomSlot = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("RoomSlot")));

	// 버튼 클릭시 호출될 델리게이트에 함수를 등록한다
	SendButton->OnClicked.AddDynamic(this, &ULobbyWidgetManager::SendButtonEvent);
	MakeRoomListPool();
}

void ULobbyWidgetManager::SendButtonEvent()
{
	GameIns->SendMsg(SendDataTextBox->Text.ToString());
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
void ULobbyWidgetManager::MakeRoomListPool() 
{
	for (int i = 0; i < 64; i++)
	{
		AddRoomSlot("no"+i);
	}
	UE_LOG(LogTemp, Log, TEXT("ROOM SET CLEAR"));
}
void  ULobbyWidgetManager::ChangeRoomList(TArray<FString> data) 
{
	int curRoomCnt = data.Num() - preRoomCnt;
	if (curRoomCnt > 0) {
		for (int i = preRoomCnt; i < preRoomCnt+curRoomCnt; i++)
		{
			AttachBtn(RoomList[i]);
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
	UE_LOG(LogTemp, Log, TEXT("(CHANGE EVENT )NOW SET ROOM CNT IS : %d"),preRoomCnt);
}
void ULobbyWidgetManager::AddRoomSlot(FString txt)
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
void ULobbyWidgetManager::AttachBtn(UButton* btn) 
{
	RoomScrollBox->AddChild(btn);
	Cast<UScrollBoxSlot>(btn->Slot)->SetPadding(FMargin(0, 35, 0, 50));
}
void ULobbyWidgetManager::EditText(UButton* btn,FString data)
{
	Cast<UTextBlock>(btn->GetChildAt(0))->SetText(FText::FromString(data));


}
void ULobbyWidgetManager::Login() {
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *txt);
	GameIns->client->Connect();

}