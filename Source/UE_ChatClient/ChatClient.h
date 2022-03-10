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
#include "ChatClient.generated.h"


UCLASS()
class UE_CHATCLIENT_API UChatClient : public UObject
{
	GENERATED_BODY()
protected:
	bool ConnectionState;
	
public:
	uint8 DataBuffer[1024];
	bool IsLogin;
	int DataBufferPoint;
	FString CurOrder;
	FSocket* Socket;

public:
	bool Connect();
	void SendData(FString& text);
	void ReceiveData(); 
	bool GetConnectionState();
};
