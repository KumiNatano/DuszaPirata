#pragma once

#include "CoreMinimal.h"
#include "EntityStatus.h"
#include "HealthSystem.h"
#include "EntityDamageStatus.generated.h"


UENUM(BlueprintType)
enum EEntityStatusTickDamageType
{
	Relative,  // Damage is given relative to delta time, lifespan of status and total damage.
	Constant   // Constant amount of damage given each tick.
};

UCLASS()
class DUSZAPIRATA_API UEntityDamageStatus : public UEntityStatus
{
	GENERATED_BODY()
protected:
	virtual void ActorAssigned_Implementation(AActor* Actor) override;
	virtual void Started_Implementation() override;
	virtual void Ticked_Implementation(float DeltaTime) override;
	virtual void Ended_Implementation() override;
public:
	/**
	 * Tells if status should damage actor's health on start.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings")
	bool DamageOnStart = false;
	
	/**
	 * Tells if status should damage actor's health each tick.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings")
	bool DamageOnTick = false;
	
	/**
	 * Tells if status should damage actor's health each tick.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings")
	bool DamageOnEnd = false;
	
	/**
	 * Damage given to actor's health on start.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings")
	float StartDamage = 0;
	
	/**
	 * Total damage given to actor's health during life of status.
	 * Used when tick damage type is set to Relative.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings")
	float TotalDamage = 0;
	
	/**
	 * Damage given to actor's health each tick.
	 * Used when tick damage type is set to Constant.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings")
	float TickDamage = 0;
	
	/**
	 * Damage given to actor's health on end.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings")
	float EndDamage = 0;

	/**
	 * Determines how much damage should be given to actor's health each tick.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings")
	TEnumAsByte<EEntityStatusTickDamageType> TickDamageType;

	
	/**
	 * Damage given to actor's health during work.
	 */
	UPROPERTY(BlueprintReadOnly, Category="State")
	float DamageGiven = 0;
	
	/**
	 * A health component of target actor.
	 */
	UPROPERTY(BlueprintReadOnly, Category="State")
	UHealthSystem* Health;
};
