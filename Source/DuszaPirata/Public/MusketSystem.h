

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/StaticMeshActor.h"
#include "MusketSystem.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUSZAPIRATA_API UMusketSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMusketSystem();
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AStaticMeshActor> BulletBlueprint;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	bool isLoaded = false;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool TryPickUpAmmo();
	void Shoot();

	UPROPERTY(EditAnywhere)
	float distanceFromPlayerForBulletToSpawn = 50;
		
};
