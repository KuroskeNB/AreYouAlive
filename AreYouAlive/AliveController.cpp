// Fill out your copyright notice in the Description page of Project Settings.


#include "AliveController.h"
#include "Blueprint/UserWidget.h"

bool AAliveController::OpenDialogueWindow()
{
    //check if widget exist
    if(!DialogueWidget) return false; 
    
    //check dialogue state
    if(!bIsInDialogue)
    {
        // Place dialogue window on screen
        FHitResult hit;
        FindSomeoneForDialogue(hit);
        if(hit.GetActor())
        {
    DialogueWindow=CreateWidget(this,DialogueWidget);
        if (DialogueWindow)
        {
            DialogueWindow->AddToViewport();
            bIsInDialogue=true;
            
            FInputModeGameAndUI GameAndUI;
            SetInputMode(GameAndUI);
            SetShowMouseCursor(true);
        }
        }
    }
    else
    {
        // remove dialogue window from screen
        if(DialogueWindow)
        {
      DialogueWindow->RemoveFromParent();

     bIsInDialogue=false;
     FInputModeGameOnly GameOnly;
     SetInputMode(GameOnly);
     SetShowMouseCursor(false);
        }
    }
    return bIsInDialogue;
}


void AAliveController::FindSomeoneForDialogue(FHitResult& result)
{
    // Calculate screen center
        FVector2D ScreenCenter = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY()) * 0.5f;

        FVector WorldLocation;
        FVector WorldDirection;

        // Calculate screen center in world
        DeprojectScreenPositionToWorld(ScreenCenter.X, ScreenCenter.Y, WorldLocation, WorldDirection);

        // trace distance
        float TraceDistance = 2000.0f;
        FVector EndLocation = WorldLocation + (WorldDirection * TraceDistance);

        // trace properties
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(GetPawn());
        // line trace
        if (GetWorld()->LineTraceSingleByChannel(result, WorldLocation, EndLocation, ECC_GameTraceChannel1, CollisionParams))
        {
            // hit notify
            UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *result.GetActor()->GetName());

            // Debug Line draw
            DrawDebugLine(GetWorld(), WorldLocation, result.Location, FColor::Red, false, 1.0f, 0, 1.0f);
        }
        else
        {
            // Debug No hit
            DrawDebugLine(GetWorld(), WorldLocation, EndLocation, FColor::Green, false, 1.0f, 0, 1.0f);
        }
}
