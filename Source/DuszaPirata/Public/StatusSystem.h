#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "HealthSystem.h"
#include "StatusSystem.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUSZAPIRATA_API UStatusSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusSystem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsStatusActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DurationOfStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StatusDamageTickrate;

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void TurnOnStatus(float duration, float tickrate, float damage);
	void TurnOffStatus();
	

private:
	float damageToDealPerTick;
	void ReapeatingDamage();

	FTimerHandle MemberTimerHandle;
};
