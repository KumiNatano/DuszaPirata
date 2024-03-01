


#include "Items/Item.h"

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
	
}

void UItem::ThrowItem()
{
	// Uzyskaj komponent mesh przedmiotu (zakładamy, że jest to StaticMeshComponent)
	UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	if (MeshComp)
	{
		MeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
		FVector ThrowDirection = GetOwner()->GetAttachParentActor()->GetActorForwardVector() + upVector; // Dodaj trochę w górę, aby stworzyć łuk rzutu
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
		OwnerMeshComp->OnComponentHit.AddDynamic(this, &UItem::OnComponentHit);
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

void UItem::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UHealthSystem* otherHealthSystem = OtherActor->FindComponentByClass<UHealthSystem>();
	if(otherHealthSystem && !didItHit)
	{
		AActor* DamagedActor = OtherActor;
		const UDamageType* DamageType = nullptr;
		AController* InstigatedBy = nullptr;
		AActor* DamageCauser = GetOwner();
		otherHealthSystem->TakeDamage(DamagedActor, ThrowDamage, DamageType, InstigatedBy, DamageCauser);
		didItHit = true;
	}
}

