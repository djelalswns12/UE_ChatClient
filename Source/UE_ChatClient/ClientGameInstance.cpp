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
	if (client->Connect()) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connect Success ! ")));
		client->SendData(TEXT("hello"));
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connect Faild - Please Retrying ")));
}