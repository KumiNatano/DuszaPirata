

#pragma once

#include "CoreMinimal.h"
#include "ItemPickup.h"
#include "Components/ActorComponent.h"
#include "ItemSlotComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUSZAPIRATA_API UItemSlotComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemSlotComponent();

	int SearchItemsArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	AActor* actuallItem;
	
	void CheckItemsInArea(int area);
	void PickupItem(AActor* actor);
	void ClearItemSlot();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
