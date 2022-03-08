// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChatClient.h"
#include "Engine/GameInstance.h"
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
	UChatClient* client;
public:
	void Test();
	void Login(FString msg);
};
