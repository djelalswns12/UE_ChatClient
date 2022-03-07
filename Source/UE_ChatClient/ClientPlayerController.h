// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ClientPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE_CHATCLIENT_API AClientPlayerController : public APlayerController
{
	GENERATED_BODY()
		virtual void BeginPlay() override;

protected:
	AClientPlayerController();
};
