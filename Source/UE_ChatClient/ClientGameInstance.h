// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChatClient.h"
#include "Engine/GameInstance.h"
#include "UE_ChatClientGameModeBase.h"

#include "AuthWidgetManager.h"
#include "LobbyWidgetManager.h"

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
	class UAuthWidgetManager* AuthWidget;
	class ULobbyWidgetManager* LobbyWidget;
	AUE_ChatClientGameModeBase* GameMode;
	class UChatClient* client;
	void Test();
	void LoginEvent(FString name);
	void ConnectEvent();
	void ReceiveEvent();
	void SendMsg(FString msg);
	bool GetSocketConnectionState();
};
