// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ScrollBoxSlot.h"

#include "LobbyWidgetManager.generated.h"

/**
 * 
 */
class UScrollBoxSlot;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UScrollBox* RoomScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UScrollBox* UserScrollBox;


	//대화방
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UCanvasPanel* RoomChatPanel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* RoomChatOutBtn;

	//대화방 입장 팝업
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UCanvasPanel* RoomEnterPanel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* RoomEnterBtn;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* RoomCancleBtn;

	//유저정보 팝업
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UCanvasPanel* UserPanel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* SendTMsgBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* UserPanelOutBtn;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* UserInfoText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UEditableTextBox* TMsgBox;

protected:
	virtual void NativeConstruct() override;
	UClientGameInstance* GameIns;
	int preRoomCnt;
	int preUserCnt;
	TArray<UButton*> RoomList;
	TArray<UButton*> UserList;

public:
	void MakeBtnListPool();
	void EditText(UButton* btn,FString& data);

	void ChangeRoomList(TArray<FString>& data);
	void ChangeUserList(TArray<FString>& data);

	void AttachBtn(UWidget* btn, UScrollBox* scroll, FMargin& margin);
	void AddText(FString txt);
	void AddRoomSlot(FString& txt);
	void AddUserSlot(FString& txt);

	void SetRoomChatPannel(TArray<FString>& data);
	void SetUserPannel(TArray<FString>& data);

private:
	// 버튼을 눌렀을 때, 호출될 델리게이트에 등록할 함수
	UFUNCTION(BlueprintCallable)
		void SendButtonEvent();
	UFUNCTION(BlueprintCallable)
		void PopUpRoomChatPannel();
	UFUNCTION(BlueprintCallable)
		void Login();
};
