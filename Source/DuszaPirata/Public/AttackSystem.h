// 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackSystem.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUSZAPIRATA_API UAttackSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAttackSystem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float DefaultDamage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	
	UFUNCTION()
	void DealDamage(AActor* DamagedActor, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
