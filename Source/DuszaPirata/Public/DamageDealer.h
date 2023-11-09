#pragma once

#include "CoreMinimal.h"
#include "DuszaPirata/Public/HealthSystem.h"
#include "GameFramework/Actor.h"
#include "DamageDealer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUSZAPIRATA_API UDamageDealer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageDealer();
	
	UPROPERTY(EditAnywhere)
	TArray<AActor*> OverlappingActors;

	UPROPERTY(EditAnywhere)
	float DamageToDeal;

	UPROPERTY(EditAnywhere)
	float TimeRateToDamage;
	
protected:
	FTimerHandle MemberTimerHandle;
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void DealDamageInArea();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
