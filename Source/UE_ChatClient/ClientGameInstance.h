// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChatClient.h"
#include "Engine/GameInstance.h"
#include "UE_ChatClientGameModeBase.h"
#include "AuthWidgetManager.h"
#include "ClientGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE_CHATCLIENT_API UClientGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	virtual void Init() override;

	
public:
	UChatClient* client;
	void Test();
	void LoginEvent(FString msg);
	void ReceiveEvent();
	bool GetSocketConnectionState();
};
