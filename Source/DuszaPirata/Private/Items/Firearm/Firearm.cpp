#include "Items/Firearm/Firearm.h"

UWeapon::UWeapon()
{

}

UWeapon::~UWeapon()
{
	
}

void UWeapon::BeginPlay()
{
	Super::BeginPlay();
	actualAmmo = ammoAtStart;
}

void UWeapon::UseItem()
{
	Super::UseItem();
	if(actualAmmo > 0)
	{
		actualAmmo--;

		AActor* ParentActor = GetOwner()->GetAttachParentActor();
		if (ParentActor)
		{
			FVector ForwardVector = ParentActor->GetActorForwardVector();
			FVector SpawnLocation = GetOwner()->GetActorLocation() + (ForwardVector * 90);
			FRotator SpawnRotation = ParentActor->GetActorRotation();

			AStaticMeshActor* Bullet = GetWorld()->SpawnActor<AStaticMeshActor>(bulletBlueprint, SpawnLocation, SpawnRotation);

			SpawnSmokeEffects(SpawnLocation);
		}
	}
}

void UWeapon::SpawnSmokeEffects(FVector SpawnLocation)
{
	for(UNiagaraSystem* Effect : smokeEffects)
	{
		if (Effect)
		{
			FRotator SpawnRotation = GetOwner()->GetActorRotation();

			UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				GetWorld(),
				Effect,
				SpawnLocation,
				SpawnRotation
			);
		}
	}
}

void UWeapon::ThrowItem()
{
	Super::ThrowItem();
}
