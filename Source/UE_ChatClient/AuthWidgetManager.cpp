// Fill out your copyright notice in the Description page of Project Settings.


#include "AuthWidgetManager.h"


void UAuthWidgetManager::NativeConstruct()
{
	Super::NativeConstruct();

	// ���� ��������Ʈ�� ��ư�� �̸��� ���� �����´�
	LoginBtn = Cast<UButton>(GetWidgetFromName(TEXT("LoginBtn")));

	// ���� ��������Ʈ�� �ؽ�Ʈ ������ �̸��� ���� �����´�
	LoginInputTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("LoginInputTextBox")));

	// ��ư Ŭ���� ȣ��� ��������Ʈ�� �Լ��� ����Ѵ�
	LoginBtn->OnClicked.AddDynamic(this, &UAuthWidgetManager::TestButtonCallback);
}

void UAuthWidgetManager::LoginCallback()
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *LoginInputTextBox->Text.ToString());
}