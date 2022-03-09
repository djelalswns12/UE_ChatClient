// Copyright Epic Games, Inc. All Rights Reserved.


#include "UE_ChatClientGameModeBase.h"

AUE_ChatClientGameModeBase::AUE_ChatClientGameModeBase() {
	static ConstructorHelpers::FClassFinder<UUserWidget> Awidget(TEXT("/Game/AuthWidget"));
	if (Awidget.Succeeded() && Awidget.Class != NULL)
	{
		AuthWidget = Awidget.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> Lwidget(TEXT("/Game/LobbyWidget"));
	if (Lwidget.Succeeded() && Lwidget.Class != NULL)
	{
		LobbyWidget = Lwidget.Class;
	}

	DefaultPawnClass = APawn::StaticClass();
	PlayerControllerClass = AClientPlayerController::StaticClass();


}

void AUE_ChatClientGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerClass = AClientPlayerController::StaticClass();
	ChangeMenuWidget(AuthWidget);
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

