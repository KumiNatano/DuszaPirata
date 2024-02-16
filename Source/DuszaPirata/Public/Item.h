

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FVector upVector = FVector(0.0f, 0.0f, 0.3f);

	bool didItHit = false;
	
	virtual void UseItem();
	virtual void ThrowItem();
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
