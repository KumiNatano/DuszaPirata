// Copyright Epic Games, Inc. All Rights Reserved.

#include "DuszaPirataGameMode.h"
#include "DuszaPirataCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADuszaPirataGameMode::ADuszaPirataGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
