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
//#include <Windows.h>
//#include <WS2tcpip.h>

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
	FString ReceiveData(); 
	bool GetConnectionState();
	FSocket* Socket;
};
