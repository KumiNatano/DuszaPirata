// Copyright Epic Games, Inc. All Rights Reserved.

#include "PrototypeGameMode.h"
#include "Hero.h"
#include "UObject/ConstructorHelpers.h"

APrototypeGameMode::APrototypeGameMode() : Super()
{
	static ConstructorHelpers::FClassFinder <APawn> heroFinder(TEXT("Blueprint'/Game/Blueprints/BP_Hero.BP_Hero_C'"));
	if(heroFinder.Succeeded( ))
	{
		DefaultPawnClass = heroFinder.Class;
	}
	else
	{
		GLog->Log("GameMode: Could not find hero class!");
	}
}
