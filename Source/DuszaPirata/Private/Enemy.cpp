


#include "Enemy.h"

#include "HealthSystem.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	UHealthSystem* HealthSystem = FindComponentByClass<UHealthSystem>();
	if(HealthSystem)
	{
		HealthSystem->OnDeath.AddDynamic(this, &AEnemy::HandleDeath);
		
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::HandleDeath(AActor* DamagedActor, float Damage,
		const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	this->SetRagdoll(true);
	//if(Con)
}

void AEnemy::SetRagdoll(bool value)
{
	IsRagdolled = value;
	if(USkeletalMeshComponent* SkeletalMesh = this->FindComponentByClass<USkeletalMeshComponent>()) {
		if(UCapsuleComponent* CapsuleComp = this->GetCapsuleComponent())
		{
			if(value)
			{
				SkeletalMesh->SetSimulatePhysics(true);
				CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}
			else
			{
				CapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

				SkeletalMesh->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
				SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				SkeletalMesh->SetSimulatePhysics(false);
				FVector WorldMeshLocation = SkeletalMesh->GetComponentLocation();
				CapsuleComp->SetWorldLocation(WorldMeshLocation);

				SkeletalMesh->AttachToComponent(CapsuleComp, FAttachmentTransformRules(
					EAttachmentRule::SnapToTarget,
					EAttachmentRule::KeepRelative,
					EAttachmentRule::KeepRelative,
					true));
				SkeletalMesh->SetRelativeLocation_Direct(FVector(0, 0, -85));
				SkeletalMesh->SetRelativeRotation_Direct(FRotator(0, -90, 0));
			}
		}
	}
	
}

