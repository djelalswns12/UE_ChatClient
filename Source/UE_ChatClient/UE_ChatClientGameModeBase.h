// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ChatClient.h"

#include "GameFramework/GameModeBase.h"
#include <Blueprint/UserWidget.h>
#include "ClientPlayerController.h"

#include "UE_ChatClientGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE_CHATCLIENT_API AUE_ChatClientGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AUE_ChatClientGameModeBase();
	UFUNCTION(BlueprintCallable, Category = "UMG_Game")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
		UUserWidget* CurrentWidget;

};
