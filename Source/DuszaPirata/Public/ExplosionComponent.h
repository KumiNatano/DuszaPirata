

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ExplosionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUSZAPIRATA_API UExplosionComponent : public UActorComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExplosionSignature);
public:	
	UExplosionComponent();

	UPROPERTY(BlueprintAssignable)
	FOnExplosionSignature OnExplosionBP;

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Explosion")
	void StartCountdown();

	UFUNCTION(BlueprintCallable, Category = "Explosion")
	void TriggerExplosion();

	UPROPERTY(EditAnywhere, Category = "Fire")
	TSubclassOf<AActor> FireAreaBlueprint;


private:
	UPROPERTY(EditAnywhere, Category = "Explosion")
	float CountdownDuration = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Explosion")
	float ExplosionRadius = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Explosion")
	float DamageAmount = 50.0f;

	UFUNCTION()
	void DealDamageInRadius();

	UFUNCTION()
	void SpawnFireArea();
};
