


#include "Item.h"

// Sets default values for this component's properties
UItem::UItem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UItem::UseItem()
{
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, TEXT("Uzyto itemu")); 
}

void UItem::ThrowItem()
{
	//GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, TEXT("Rzucono item i zadano " + FString::SanitizeFloat(ThrowDamage) + " obrazen"));

	// Uzyskaj komponent mesh przedmiotu (zakładamy, że jest to StaticMeshComponent)
	UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	if (MeshComp)
	{
		FVector ThrowDirection = GetOwner()->GetAttachParentActor()->GetActorForwardVector() + FVector(0.0f, 0.0f, 0.3f); // Dodaj trochę w górę, aby stworzyć łuk rzutu
		ThrowDirection.Normalize();
		MeshComp->SetSimulatePhysics(true);
		MeshComp->AddImpulse(ThrowDirection * ThrowForce, NAME_None, true);
	}
	
}

// Called when the game starts
void UItem::BeginPlay()
{
	Super::BeginPlay();

	// Najpierw sprawdź, czy właściwy komponent mesh został znaleziony
	UPrimitiveComponent* OwnerMeshComp = Cast<UPrimitiveComponent>(GetOwner()->GetComponentByClass(UPrimitiveComponent::StaticClass()));
	if (OwnerMeshComp)
	{
		// Jeśli komponent istnieje, dodaj delegata
		OwnerMeshComp->OnComponentBeginOverlap.AddDynamic(this, &UItem::OnOverlapBegin);
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, TEXT("JEST")); 
	}
	else
	{
		// Jeśli komponent nie istnieje, wyświetl błąd debugowania
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, TEXT("Komponent nie znaleziony"));
	}
}


// Called every frame
void UItem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*if(GetOwner()->GetAttachParentActor() != nullptr)
	{
		FVector ThrowDirection = GetOwner()->GetAttachParentActor()->GetActorForwardVector();
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, ThrowDirection.ToString()); 

		// ...
	}*/
}

void UItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, TEXT("zbudowali maszyny")); 
	
	/*UHealthSystem* HealthComponent = OtherActor->FindComponentByClass<UHealthSystem>();
	if (HealthComponent)
	{
		AActor* DamagedActor = OtherActor;
		float DamageAmount = ThrowDamage;
		const UDamageType* DamageType = nullptr;
		AController* InstigatedBy = nullptr;
		AActor* DamageCauser = GetOwner();
		HealthComponent->TakeDamage(DamagedActor, DamageAmount, DamageType, InstigatedBy, DamageCauser);
	}*/
}

