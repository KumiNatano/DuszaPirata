

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MusketPickup.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUSZAPIRATA_API UMusketPickup : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMusketPickup();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FTimerHandle MemberTimerHandle;
public:

	UPROPERTY(EditAnywhere)
	TArray<AActor*> OverlappingActors;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SomethingIsOnPickup();
	
};
