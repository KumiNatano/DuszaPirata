// 


#include "AttackSystem.h"

#include "Enemy.h"
#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties
UAttackSystem::UAttackSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	DefaultDamage = 50;
	Damage = DefaultDamage;

	DefaultStrength = 100000;
	Strength = DefaultStrength;
}


// Called when the game starts
void UAttackSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UAttackSystem::DealDamage(AActor* DamagedActor, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{
	
}

void UAttackSystem::Kicking()
{
	FVector SphereCenter = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 200;
	float SphereRadius = 200.0;
	int SphereSegments = 12;
	FColor SphereColor = FColor::Red;

	TArray<FOverlapResult> Overlaps;
	FCollisionQueryParams CollisionParams;

	DrawDebugSphere(GetWorld(), SphereCenter, SphereRadius, SphereSegments, SphereColor, false, 2.0f);
	
	bool bHit = GetWorld()->OverlapMultiByObjectType(
		Overlaps,
		SphereCenter,
		FQuat::Identity,
		FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllObjects),
		FCollisionShape::MakeSphere(SphereRadius),
		CollisionParams
	);

	if (bHit)
	{
		for (const FOverlapResult& OverlapResult : Overlaps)
		{
			AActor* HitActor = OverlapResult.GetActor();
			// hit Enemy
			if (AEnemy* Enemy = Cast<AEnemy>(HitActor))
			{
				Enemy->SetRagdoll(true);
				UPrimitiveComponent* EnemyRoot;
				if(ACharacter* Character = Cast<ACharacter>(Enemy))
				{
					EnemyRoot = Character->GetMesh();
					if(EnemyRoot)
					{
						EnemyRoot->AddImpulseAtLocation(GetOwner() ->GetActorForwardVector() * Strength/4,
							EnemyRoot->GetComponentTransform().TransformPosition(GetOwner()->GetActorLocation()));
					}
				}
			}
			// if hit Object other than Enemy
			else if (USceneComponent* RootComponent = HitActor->GetRootComponent())
			{
				UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(RootComponent);
				if (PrimitiveComponent && PrimitiveComponent->IsSimulatingPhysics())
				{
					PrimitiveComponent->AddImpulse(GetOwner()->GetActorForwardVector() * Strength + GetOwner()->GetActorUpVector()*10.f);
				}
			}
		}
	}
}

