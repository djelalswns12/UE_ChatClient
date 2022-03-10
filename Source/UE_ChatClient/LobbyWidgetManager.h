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
#include "CustomButton.h"
#include "DataButton.h"

#include "LobbyWidgetManager.generated.h"

/**
 * 
 */
class UScrollBoxSlot;
class UClientGameInstance;
class UDataButton;
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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UScrollBox* RoomUserListScroll;


	//대화방 입장 팝업
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UCanvasPanel* RoomEnterPanel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* RoomEnterBtn;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* RoomCancleBtn;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* RoomInfoText;

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

	//대화방 만들기
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UCanvasPanel* MakeRoomPanel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* MakeRoomBtn;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* RoomMakeBtn;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* RoomMakeOutBtn;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UEditableTextBox* SetRoomNameText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UEditableTextBox* SetRoomCntText;

	//알림
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UCanvasPanel* MsgPanel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* MsgOutBtn;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* InviteBtn;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* MyMsgText;

protected:
	virtual void NativeConstruct() override;
	UClientGameInstance* GameIns;
	int preRoomCnt;
	int preUserCnt;
	int preRoomUserCnt;
	TArray<UDataButton*> RoomList;
	TArray<UDataButton*> UserList;
	TArray<UDataButton*> RoomUserList;

public:
	void MakeBtnListPool();
	void EditText(UDataButton* btn,FString& data);
	void EditTextForName(UDataButton* btn,FString& data);

	void ChangeRoomList(TArray<FString>& data);
	void ChangeUserList(TArray<FString>& data);
	void ChangeRoomUserList(TArray<FString>& data);
	void AttachBtn(UWidget* btn, UScrollBox* scroll, FMargin& margin);
	void AddText(FString txt);

	void AddRoomSlot(FString& txt);
	void AddUserSlot(FString& txt);
	void AddRoomUserSlot(FString& txt);

	void SetRoomChatPannel(TArray<FString>& data);
	void SetUserPannel(TArray<FString>& data);


public:
	// 버튼을 눌렀을 때, 호출될 델리게이트에 등록할 함수
	UFUNCTION(BlueprintCallable)
		void SendButtonEvent();

	UFUNCTION(BlueprintCallable)
		void PopUpRoomChatPannel();

	UFUNCTION(BlueprintCallable)
		void PopUpUserPannel();

	UFUNCTION(BlueprintCallable)
		void PopUpRoomEnterPannel();

	UFUNCTION(BlueprintCallable)
		void PopUpMakeRoomPanel();

	UFUNCTION(BlueprintCallable)
		void MakeRoomEvent();

	UFUNCTION(BlueprintCallable)
		void EnterRoom();

	UFUNCTION(BlueprintCallable)
		void ToUser();

	UFUNCTION(BlueprintCallable)
		void Login();
	UFUNCTION(BlueprintCallable)
		void InMsg();
	UFUNCTION(BlueprintCallable)
		void OutRoom();
	UFUNCTION(BlueprintCallable)
		void SetRoomChatPanelVisible(ESlateVisibility type);

	UFUNCTION(BlueprintCallable)
		void CloseMsgPanel();

	UFUNCTION(BlueprintCallable)
		void SetMsgPanel(FString& data);
};
