

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExplosionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUSZAPIRATA_API UExplosionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExplosionComponent();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Explosion")
	void StartCountdown();

	UFUNCTION(BlueprintCallable, Category = "Explosion")
	void TriggerExplosion();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	float CountdownDuration = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	float ExplosionRadius = 500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	float DamageAmount = 50.0f;

	UFUNCTION()
	void DealDamageInRadius();

	UFUNCTION()
	void SpawnExplosionEffects();

		
};
