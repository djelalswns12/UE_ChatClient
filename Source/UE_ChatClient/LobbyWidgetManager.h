// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"

#include "ClientGameInstance.h"


#include "LobbyWidgetManager.generated.h"

/**
 * 
 */

class UClientGameInstance;
UCLASS()
class UE_CHATCLIENT_API ULobbyWidgetManager : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* SendButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UEditableTextBox* SendDataTextBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UScrollBox* RecvDataScrollBox;

protected:
	virtual void NativeConstruct() override;
	UClientGameInstance* GameIns;

public:
	void AddText(FString txt);
private:
	// 버튼을 눌렀을 때, 호출될 델리게이트에 등록할 함수
	UFUNCTION(BlueprintCallable)
		void SendButtonEvent();
	UFUNCTION(BlueprintCallable)
		void Login();
};
