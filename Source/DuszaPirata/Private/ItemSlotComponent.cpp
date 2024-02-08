


#include "ItemSlotComponent.h"

//#include "ItemPickup.h"

// Sets default values for this component's properties
UItemSlotComponent::UItemSlotComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;
	
}

// Called when the game starts
void UItemSlotComponent::BeginPlay()
{
	//Super::BeginPlay();
	
}


// Called every frame
void UItemSlotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UItemSlotComponent::CheckItemsInArea(int area)
{
	
	/*FVector Location = GetOwner()->GetActorLocation();

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner()); // Ignoruj aktora posiadającego ten komponent
	QueryParams.bTraceComplex = true;

	// Definiowanie typu kolizji, który ma być brany pod uwagę przy skanowaniu
	FCollisionObjectQueryParams ObjectQueryParams(FCollisionObjectQueryParams::AllObjects);

	// Wykonanie skanowania
	bool bFound = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		Location,
		FQuat::Identity,
		ObjectQueryParams,
		FCollisionShape::MakeSphere(area),
		QueryParams
	);

	if (bFound)
	{
		for (const FOverlapResult& Result : OverlapResults)
		{
			AActor* Actor = Result.GetActor();
			if (Actor)
			{
				// Sprawdź, czy aktor posiada komponent UItemPickup
				UItemPickup* ItemPickupComponent = Cast<UItemPickup>(Actor->GetComponentByClass(UItemPickup::StaticClass()));

				if (ItemPickupComponent)
				{
					// Znaleziono aktora z komponentem UItemPickup - wykonaj odpowiednie działanie
					GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, *Actor->GetName());
					//PickupItem(Actor);
				}
			}
		}

	}*/
}

/*void UItemSlotComponent::PickupItem(AActor* actor)
{
	
}*/

