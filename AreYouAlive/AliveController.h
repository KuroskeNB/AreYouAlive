// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AliveController.generated.h"

/**
 * 
 */
UCLASS()
class AREYOUALIVE_API AAliveController : public APlayerController
{
	GENERATED_BODY()
	protected:
	//virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category="Dialogue")
	TSubclassOf<class UUserWidget> DialogueWidget;
	
	class  UUserWidget* DialogueWindow;
    bool bIsInDialogue=false;
	public:
	bool OpenDialogueWindow();
	void FindSomeoneForDialogue(FHitResult& result);
};