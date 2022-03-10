// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/Button.h"
#include "ClientGameInstance.h" 
#include "DataButton.generated.h"

/**
 * 
 */

UCLASS()
class UE_CHATCLIENT_API UDataButton : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UButton* btn;

	UClientGameInstance* GameIns;
	FString data;

public:
	
	UFUNCTION(BlueprintCallable)
	void SetEvent(int type);
	
	UFUNCTION(BlueprintCallable)
	void UserPopUpEvent();
	
	UFUNCTION(BlueprintCallable)
	void RoomEnterPopUpEvent();
	
	void Init();
	FString GetDataName();
};
