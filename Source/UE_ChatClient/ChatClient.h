// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

#include "ChatClient.generated.h"

/**
 * 
 */
UCLASS()
class UE_CHATCLIENT_API UChatClient : public UObject
{
	GENERATED_BODY()
	
public:
	void Connect();
	void SendData(FString text);
	void ReceiveData(); 
	bool ConnectState;

	FSocket* Socket;
	TArray<uint8> UintConvert(FString msg);
};
