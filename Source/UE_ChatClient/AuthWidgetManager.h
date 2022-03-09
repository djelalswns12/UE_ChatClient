// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Widgets/SWidget.h"
#include "Widgets/Layout/SConstraintCanvas.h"
#include "Components/PanelWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "ClientGameInstance.h"



#include "AuthWidgetManager.generated.h"

/**
 * 
 */
class UClientGameInstance;
class UCanvasPanelSlot;
UCLASS()
class UE_CHATCLIENT_API UAuthWidgetManager : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* LoginBtn;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* ConnectBtn;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UEditableTextBox* LoginInputTextBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCanvasPanel* PopUpPanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* PopUpMsg;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* PopUpBtnMsg;
protected:
	virtual void NativeConstruct() override;
	UClientGameInstance* gameIns;

public:
	void AddText(FString txt);
	// 버튼을 눌렀을 때, 호출될 델리게이트에 등록할 함수
	UFUNCTION(BlueprintCallable)
		void LoginCallback();
	UFUNCTION(BlueprintCallable)
		void ConnectCallback();
	UFUNCTION(BlueprintCallable)
		void ConnectFail();
	UFUNCTION(BlueprintCallable)
		void LoginIdMiss();
	UFUNCTION(BlueprintCallable)
		void PopUp(FString mainMsg, FString btnMsg, bool editBox);
};