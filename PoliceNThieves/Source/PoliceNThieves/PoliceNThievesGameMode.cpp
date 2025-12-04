// Copyright Epic Games, Inc. All Rights Reserved.

#include "PoliceNThievesGameMode.h"
#include "PoliceNThievesCharacter.h"
#include "UObject/ConstructorHelpers.h"

APoliceNThievesGameMode::APoliceNThievesGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
