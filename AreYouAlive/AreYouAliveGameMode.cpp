// Copyright Epic Games, Inc. All Rights Reserved.

#include "AreYouAliveGameMode.h"
#include "AreYouAliveCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAreYouAliveGameMode::AAreYouAliveGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
