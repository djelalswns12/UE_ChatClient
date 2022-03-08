// Copyright Epic Games, Inc. All Rights Reserved.


#include "UE_ChatClientGameModeBase.h"

AUE_ChatClientGameModeBase::AUE_ChatClientGameModeBase() {
	static ConstructorHelpers::FClassFinder<UUserWidget> widget(TEXT("/Game/AuthWidget"));
	if (widget.Succeeded() && widget.Class != NULL)
	{
		StartingWidgetClass = widget.Class;
	}
	DefaultPawnClass = APawn::StaticClass();
	PlayerControllerClass = AClientPlayerController::StaticClass();


}

void AUE_ChatClientGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//PlayerControllerClass = AClientPlayerController::StaticClass();
	ChangeMenuWidget(StartingWidgetClass);
	
}

void AUE_ChatClientGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{


	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

