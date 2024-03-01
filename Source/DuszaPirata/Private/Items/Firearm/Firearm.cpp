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
			FVector SpawnLocation = GetOwner()->GetActorLocation() + (ForwardVector * 90); //pozniej zmienic to na ignora, bo wciaz nie jest idealnie
			FRotator SpawnRotation = ParentActor->GetActorRotation();

			AStaticMeshActor* Bullet = GetWorld()->SpawnActor<AStaticMeshActor>(bulletBlueprint, SpawnLocation, SpawnRotation);
		}
	}
}

void UWeapon::ThrowItem()
{
	Super::ThrowItem();
}
