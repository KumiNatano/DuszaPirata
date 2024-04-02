


#include "Items/ItemSlotComponent.h"

//#include "ItemPickup.h"

// Sets default values for this component's properties
UItemSlotComponent::UItemSlotComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}

// Called when the game starts
void UItemSlotComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UItemSlotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if(actuallItem == nullptr)
	{
		CheckItemsInArea(200);
	}
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UItemSlotComponent::CheckItemsInArea(int area)
{
	
	FVector Location = GetOwner()->GetActorLocation();

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
			AActor* pickupObject = Result.GetActor();
			if (pickupObject)
			{
				// Sprawdź, czy aktor posiada komponent UItemPickup
				UItemPickup* ItemPickupComponent = Cast<UItemPickup>(pickupObject->GetComponentByClass(UItemPickup::StaticClass()));

				if (ItemPickupComponent)
				{
					// Znaleziono aktora z komponentem UItemPickup - wykonaj odpowiednie działanie
					PickupItem(pickupObject);
					pickupObject->Destroy();
					break;
				}
			}
		}

	}
}

void UItemSlotComponent::PickupItem(AActor* PickupActor)
{
	USkeletalMeshComponent* MyMeshComponent = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	
	if (actuallItem == nullptr && PickupActor != nullptr)
	{
		UItemPickup* ItemPickup = Cast<UItemPickup>(PickupActor->GetComponentByClass(UItemPickup::StaticClass()));
        
		if (ItemPickup != nullptr && ItemPickup->PrefabBlueprint != nullptr)
		{
			// Ustalenie lokalizacji i rotacji gdzie broń powinna zostać zinstancjonowana
			// Załóżmy, że "ItemSocket" jest nazwą gniazda na postaci, gdzie ma zostać zainstancjonowana broń
			const FTransform SocketTransform = MyMeshComponent->GetSocketTransform(TEXT("ItemSocket"), RTS_World);
            
			UWorld* World = GetWorld();
			if (World != nullptr)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				//SpawnParams.AddIgnoredActor(ActorToIgnore);
				
				// Stwórz broń i przyłącz do gniazda na postaci
				AActor* SpawnedWeapon = World->SpawnActor<AActor>(
					ItemPickup->PrefabBlueprint, 
					SocketTransform.GetLocation(), 
					SocketTransform.GetRotation().Rotator(), 
					SpawnParams
				);

				if (SpawnedWeapon != nullptr)
				{
					FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
					SpawnedWeapon->AttachToComponent(MyMeshComponent, AttachmentRules, TEXT("ItemSocket"));
                    
					actuallItem = SpawnedWeapon; // Zapisujemy zinstancjonowaną broń jako aktualny przedmiot
				}
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Item slot is already in use or actor is null."));
	}
}

void UItemSlotComponent::ClearItemSlot()
{
	actuallItem = nullptr;
}


