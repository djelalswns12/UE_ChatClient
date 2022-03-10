// Fill out your copyright notice in the Description page of Project Settings.


#include "DataButton.h"

void UDataButton::SetEvent(int type) 
{
	if (type == 0) 
	{
		btn->OnClicked.AddDynamic(this, &UDataButton::UserPopUpEvent);
	}
	if (type == 1) 
	{
		btn->OnClicked.AddDynamic(this, &UDataButton::RoomEnterPopUpEvent);
	}
}
void UDataButton::Init() 
{
	
}
void UDataButton::UserPopUpEvent() 
{
	UE_LOG(LogTemp, Log, TEXT("%s"),*data);
	TArray<FString> arr;
	data.ParseIntoArray(arr, TEXT("|"));
	GameIns->OnUserPopUp(arr);
	//이용자:df 상태:로비 대기중   IP:127.0.0.1 PORT:13107 
	//
	return;
}
void UDataButton::RoomEnterPopUpEvent() 
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *data);
	TArray<FString> arr;
	data.ParseIntoArray(arr, TEXT("|"));
	GameIns->OnRoomEnterPopUp(arr);
	//이용자:df 상태:로비 대기중   IP:127.0.0.1 PORT:13107 
	//
	return;
}
FString UDataButton::GetDataName()
{
	TArray<FString> arr;
	data.ParseIntoArray(arr, TEXT("|"));
	return arr[0];
}