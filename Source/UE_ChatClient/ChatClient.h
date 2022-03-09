// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include <iostream>
#include <locale.h>
#include "UE_ChatClientGameModeBase.h"
#include "ChatClient.generated.h"

/**
 * 
 */
class AUE_ChatClientGameModeBase;
UCLASS()
class UE_CHATCLIENT_API UChatClient : public UObject
{
	GENERATED_BODY()
protected:
	bool ConnectionState;
public:
	AUE_ChatClientGameModeBase* GameMode;
	uint8 DataBuffer[1024];
	TQueue<FString> OrderBuffer;
	int DataBufferPoint;
	bool Connect();
	void SendData(FString text);
	void ReceiveData(); 
	bool GetConnectionState();
	void Excute();

	FString CurHeader;
	FSocket* Socket;
};
