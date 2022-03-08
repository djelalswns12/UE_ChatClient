// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"

#include "ClientGameInstance.h"
#include "AuthWidgetManager.generated.h"

/**
 * 
 */
UCLASS()
class UE_CHATCLIENT_API UAuthWidgetManager : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* LoginBtn;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UEditableTextBox* LoginInputTextBox;

protected:
	virtual void NativeConstruct() override;


private:
	// 버튼을 눌렀을 때, 호출될 델리게이트에 등록할 함수
	UFUNCTION(BlueprintCallable)
		void LoginCallback();
};