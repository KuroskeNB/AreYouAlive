// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AiRequester.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAiRequester : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for AI requesters
 * 
 */
class AREYOUALIVE_API IAiRequester
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
UFUNCTION(BlueprintNativeEvent)
void RecieveAnswer(FString& answer);
};
