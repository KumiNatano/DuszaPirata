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

	static ConstructorHelpers::FClassFinder <APlayerController> controllerFinder(TEXT("Blueprint'/Game/Blueprints/BP_HeroController.BP_HeroController_C'"));
	if (controllerFinder.Succeeded())
	{
		PlayerControllerClass = controllerFinder.Class;
	}
	else
	{
		GLog->Log("GameMode: Could not find hero controller class!");
	}
}
