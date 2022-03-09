#include "LobbyWidgetManager.h"

void ULobbyWidgetManager::NativeConstruct()
{
	Super::NativeConstruct();
	GameIns = Cast<UClientGameInstance>(GetWorld()->GetGameInstance());

	SendButton = Cast<UButton>(GetWidgetFromName(TEXT("SendButton")));
	RecvDataScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("RecvDataScrollBox")));
	SendDataTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("SendDataTextBox")));

	// ��ư Ŭ���� ȣ��� ��������Ʈ�� �Լ��� ����Ѵ�
	SendButton->OnClicked.AddDynamic(this, &ULobbyWidgetManager::SendButtonEvent);
}

void ULobbyWidgetManager::SendButtonEvent()
{
	GameIns->SendMsg(SendDataTextBox->Text.ToString());
	//GameIns->LoginEvent(*LoginInputTextBox->Text.ToString());
}
void ULobbyWidgetManager::AddText(FString txt) {
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *txt);

	UTextBlock* tstText = NewObject<UTextBlock>(UTextBlock::StaticClass());
	tstText->SetText(FText::FromString(txt));
	UScrollBox* scrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("RecvDataScrollBox")));

	RecvDataScrollBox->AddChild(tstText);
	RecvDataScrollBox->ScrollToEnd();

}
void ULobbyWidgetManager::Login() {
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *txt);
	GameIns->client->Connect();

}