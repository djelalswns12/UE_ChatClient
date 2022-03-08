// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientGameInstance.h"

void UClientGameInstance::Init() 
{
	Super::Init();
	client = NewObject<UChatClient>(UChatClient::StaticClass());
	UE_LOG(LogTemp, Log, TEXT("hello~~~~~~~~~~~~~~~~"));
}
void UClientGameInstance::Test() 
{
	if (client->ConnectState==false) 
	{
		client->Connect();
		if (client->Socket->GetConnectionState() == ESocketConnectionState::SCS_Connected) 
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connect Success ! ")));
			return;
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connect Fail, Check your Network ! ")));
		return;
	}
	client->SendData(TEXT("LOGIN H"));
}
void UClientGameInstance::Login(FString msg) 
{
	if (client->ConnectState == false)
	{
		client->Connect();
		if (client->Socket->GetConnectionState() == ESocketConnectionState::SCS_Connected)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connect Success ! ")));
			return;
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connect Fail, Check your Network ! ")));
		return;
	}
	client->SendData("LOGIN "+msg);
}