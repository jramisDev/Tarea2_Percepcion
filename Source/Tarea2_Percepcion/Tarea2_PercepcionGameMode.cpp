// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tarea2_PercepcionGameMode.h"
#include "Tarea2_PercepcionCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATarea2_PercepcionGameMode::ATarea2_PercepcionGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
