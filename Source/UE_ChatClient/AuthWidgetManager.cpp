// Fill out your copyright notice in the Description page of Project Settings.


#include "AuthWidgetManager.h"


void UAuthWidgetManager::NativeConstruct()
{
	Super::NativeConstruct();

	// 위젯 블루프린트의 버튼을 이름을 통해 가져온다
	LoginBtn = Cast<UButton>(GetWidgetFromName(TEXT("LoginBtn")));

	// 위젯 블루프린트의 텍스트 블록을 이름을 통해 가져온다
	LoginInputTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("LoginInputTextBox")));

	// 버튼 클릭시 호출될 델리게이트에 함수를 등록한다
	LoginBtn->OnClicked.AddDynamic(this, &UAuthWidgetManager::LoginCallback);
}

void UAuthWidgetManager::LoginCallback()
{
	UClientGameInstance* gameIns = Cast<UClientGameInstance>(GetWorld()->GetGameInstance());
	gameIns->LoginEvent(*LoginInputTextBox->Text.ToString());
}
void UAuthWidgetManager::AddText(FString txt) {
	FString testString = TEXT("한글 테스트 완료");

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