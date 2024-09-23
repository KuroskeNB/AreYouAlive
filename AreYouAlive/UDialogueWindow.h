// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AiRequester.h"
#include "UDialogueWindow.generated.h"

/**
 * 
 */
UCLASS()
class AREYOUALIVE_API UDialogueWindow : public UUserWidget, public IAiRequester
{
	GENERATED_BODY()
	
	protected:
	UPROPERTY(meta = (BindWidgetOptional))
	class UButton* SendRequestButton;
    UPROPERTY(meta = (BindWidgetOptional))
	class UEditableTextBox* textBox;
	UPROPERTY(meta = (BindWidgetOptional))
	class UTextBlock* AnswerText;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = APIData)
	FString ApiKey;
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnSendRequestButtonClicked();
	UFUNCTION()
    virtual void RecieveAnswer_Implementation(FString& answer);
};
