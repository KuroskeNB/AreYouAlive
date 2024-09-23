// Fill out your copyright notice in the Description page of Project Settings.


#include "UAiRequesHandler.h"
#include "AiRequester.h"

UObject* UAiRequesHandler::lastRequester = nullptr;

void UAiRequesHandler::SendPostRequest(const FString &Prompt, const FString &key,UObject* requester)
{
    lastRequester=requester;
    // Create request
    TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();

    // Put AI url for a connection
    Request->SetURL(TEXT("https://api.openai.com/v1/chat/completions"));

    // Set type POST
    Request->SetVerb(TEXT("POST"));

    // Устанавливаем заголовки
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"),*key)); // Autorization data for AI

    // insert request body (JSON)
     FString RequestBody = FString::Printf(TEXT(R"({
        "model": "gpt-3.5-turbo",
        "messages": [{"role": "user", "content": "%s"}],
        "max_tokens": 50,
        "temperature": 0.7
    })"), *Prompt);
    Request->SetContentAsString(RequestBody);

    // request's answer handler
    Request->OnProcessRequestComplete().BindStatic(&UAiRequesHandler::OnResponseReceived);

    // send request
    Request->ProcessRequest();
}

void UAiRequesHandler::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    // check if request succeeded
    if (bWasSuccessful && Response.IsValid())
    {
        // debug response
        FString ResponseString = Response->GetContentAsString();
        UE_LOG(LogTemp, Log, TEXT("Response: %s"), *ResponseString);

        // Parse the JSON response
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseString);

        if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
        {
            // check the 'choices' array
            const TArray<TSharedPtr<FJsonValue>>* ChoicesArray;
            if (JsonObject->TryGetArrayField(TEXT("choices"), ChoicesArray))
            {
                if (ChoicesArray->Num() > 0)
                {
                    // Get the first object in the array
                    TSharedPtr<FJsonObject> FirstChoiceObject = (*ChoicesArray)[0]->AsObject();
                    if (FirstChoiceObject.IsValid())
                    {
                       //prepare properties for response
                        FString Answer;
                        TSharedPtr<FJsonObject> MessageObject;
                        // check for the 'message' field in the first object
                        if (FirstChoiceObject->HasField(TEXT("message")))
                        {
                           // handle the response into property
                            MessageObject = FirstChoiceObject->GetObjectField(TEXT("message"));
                            
                            if (MessageObject->TryGetStringField(TEXT("content"), Answer))
                            {
                                // procces the answer(content) field
                                UE_LOG(LogTemp, Log, TEXT("Generated Answer: %s"), *Answer);
                                if(lastRequester && lastRequester->GetClass()->ImplementsInterface(UAiRequester::StaticClass()))
                                {
                                    IAiRequester::Execute_RecieveAnswer(lastRequester,Answer);
                                }
                                else{
                                     UE_LOG(LogTemp, Display, TEXT("not recieve answer"));
                                }
                            } 
                            else
                            {
                                UE_LOG(LogTemp, Warning, TEXT("Failed to get 'content' field"));
                            }
                        }
                        else
                        {
                            UE_LOG(LogTemp, Warning, TEXT("Failed to get 'message' field"));
                        }
                    }
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to get 'choices' field"));
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to receive valid response"));
    }
}

