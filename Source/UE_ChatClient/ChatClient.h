// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <iostream>
#include <string>
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
protected:
	bool ConnectionState;

public:
	void Connect();
	void SendData(FString text);
	void ReceiveData(); 
	bool GetConnectionState();

	FSocket* Socket;
	TArray<uint8> UintConvert(FString msg);
	FString UintConvertToFString(TArray<uint8>& BinaryArray);
};
