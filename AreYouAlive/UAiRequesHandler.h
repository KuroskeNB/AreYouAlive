// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "HttpManager.h"
#include "Http.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "UAiRequesHandler.generated.h"
/**
 * 
 */
UCLASS()
class UAiRequesHandler : public UObject
{
	GENERATED_BODY()
public:
   static void SendPostRequest(const FString& Prompt, const FString &key,UObject* requester);
   static UObject* lastRequester;
private:
    static void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

};
