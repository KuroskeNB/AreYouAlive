// Fill out your copyright notice in the Description page of Project Settings.


#include "UDialogueWindow.h"
#include "UAiRequesHandler.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"

void UDialogueWindow::NativeConstruct()
{
    Super::NativeConstruct();
    if(SendRequestButton)
    {
        SendRequestButton->OnPressed.AddDynamic(this,&UDialogueWindow::OnSendRequestButtonClicked);
    }
}

void UDialogueWindow::OnSendRequestButtonClicked()
{
    // Send AI request
    if(textBox)
    {
        UAiRequesHandler::SendPostRequest(textBox->GetText().ToString(),ApiKey,this);
    }
}

void UDialogueWindow::RecieveAnswer_Implementation(FString &answer)
{
    // Put AI answer on screen
    if(AnswerText)
    AnswerText->SetText(FText::FromString(answer));
}
