// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "ClientGameInstance.h"
#include "NetworkManager.generated.h"

class ChatClient;
UCLASS()
class UE_CHATCLIENT_API ANetworkManager : public AActor
{
	GENERATED_BODY()
	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	ANetworkManager();
	UClientGameInstance* gameIns;
};
