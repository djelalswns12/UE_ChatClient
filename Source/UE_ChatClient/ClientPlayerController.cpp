// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientPlayerController.h"

void  AClientPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetShowMouseCursor(true);
	FInputModeGameAndUI inputMode;
	inputMode.SetHideCursorDuringCapture(false);
	SetInputMode(inputMode);

}

AClientPlayerController::AClientPlayerController()
{

}
