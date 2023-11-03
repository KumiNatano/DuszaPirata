


#include "ExplosionComponent.h"

#include "HealthSystem.h"

// Sets default values for this component's properties
UExplosionComponent::UExplosionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UExplosionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UExplosionComponent::StartCountdown()
{
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UExplosionComponent::TriggerExplosion);
}

void UExplosionComponent::TriggerExplosion()
{
	DealDamageInRadius();
	SpawnExplosionEffects();
}

void UExplosionComponent::DealDamageInRadius()
{
	TArray<AActor*> OverlappedActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_PhysicsBody));

	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(), 
		GetOwner()->GetActorLocation(), 
		ExplosionRadius, 
		ObjectTypes, 
		nullptr,
		OverlappedActors,
		OverlappedActors
	);

	//DrawDebugSphere(GetWorld(), GetOwner()->GetActorLocation(), ExplosionRadius, 24, FColor::Red, false, 2);
	
	//GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FString::Printf(TEXT("Znaleziono %d aktorów"), OverlappedActors.Num()));
	
	for (AActor* Actor : OverlappedActors)
	{
		if (Actor->ActorHasTag(FName("isDamagedByExplosion")))
		{
		
			UHealthSystem* HealthComponent = Actor->FindComponentByClass<UHealthSystem>();
			if (HealthComponent)
			{
				AActor* DamagedActor = Actor;
				const UDamageType* DamageType = nullptr;
				AController* InstigatedBy = nullptr;
				AActor* DamageCauser = GetOwner();
				HealthComponent->TakeDamage(DamagedActor, DamageAmount, DamageType, InstigatedBy, DamageCauser);
			}
		}
	}
}

void UExplosionComponent::SpawnExplosionEffects()
{
	if (MyNiagaraEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MyNiagaraEffect, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), FVector(1.0f), true, true, ENCPoolMethod::AutoRelease);
	}
}

