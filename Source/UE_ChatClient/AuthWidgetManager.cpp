// Fill out your copyright notice in the Description page of Project Settings.


#include "AuthWidgetManager.h"


void UAuthWidgetManager::NativeConstruct()
{
	Super::NativeConstruct();
	gameIns = Cast<UClientGameInstance>(GetWorld()->GetGameInstance());
	// 위젯 블루프린트의 버튼을 이름을 통해 가져온다
	LoginBtn = Cast<UButton>(GetWidgetFromName(TEXT("LoginBtn_")));

	// 위젯 블루프린트의 버튼을 이름을 통해 가져온다
	ConnectBtn = Cast<UButton>(GetWidgetFromName(TEXT("ConnectBtn_")));

	// 위젯 블루프린트의 텍스트 블록을 이름을 통해 가져온다
	LoginInputTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("LoginInputTextBox")));
	PopUpPanel= Cast<UCanvasPanel>(GetWidgetFromName(TEXT("PopUPPanel")));

	// 버튼 클릭시 호출될 델리게이트에 함수를 등록한다
	LoginBtn->OnClicked.AddDynamic(this, &UAuthWidgetManager::LoginCallback);
	ConnectBtn->OnClicked.AddDynamic(this, &UAuthWidgetManager::ConnectCallback);
}
void UAuthWidgetManager::ConnectCallback()
{
	//gameIns->LoginEvent(*LoginInputTextBox->Text.ToString());
	PopUpPanel->SetVisibility(ESlateVisibility::Visible);
	gameIns->ConnectEvent();
}
void UAuthWidgetManager::LoginCallback()
{
	gameIns->LoginEvent(*LoginInputTextBox->Text.ToString());
}
void UAuthWidgetManager::AddText(FString txt) {
	UE_LOG(LogTemp, Warning, TEXT("%s"), *txt);

	UTextBlock* tstText = NewObject<UTextBlock>(UTextBlock::StaticClass());
	tstText->SetText(FText::FromString(txt));

	UScrollBox* scrollBox=Cast<UScrollBox>(GetWidgetFromName(TEXT("ScrollBox")));
	scrollBox->AddChild(tstText);
	scrollBox->ScrollToEnd();

	
	//UTextBlock* tstText = WidgetTree->ConstructObject<UTextBlock>(UTextBlock::StaticClass(), this);
	//tstText->SetText(FText::FromString(TEXT("Test Button")));
	//UButton* tstBtn = WidgetTree->ConstructObject<UButton>(UButton::StaticClass(), this);
	//tstBtn->AddChild(tstText);
	
}