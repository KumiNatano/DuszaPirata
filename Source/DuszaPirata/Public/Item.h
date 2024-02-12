

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthSystem.h"
#include "Item.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUSZAPIRATA_API UItem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FString ItemName = "Default Name";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float ThrowDamage = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float ThrowForce = 500;
	
	virtual void UseItem();
	virtual void ThrowItem();
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
