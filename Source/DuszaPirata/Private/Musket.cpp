


#include "Musket.h"

Musket::Musket()
{
}

Musket::~Musket()
{
}

void Musket::UseItem()
{
	UWeapon::UseItem();
	Musket::Shoot();
}

void Musket::Shoot()
{
	if(HowMuchAmmo > 1)
	{
		HowMuchAmmo--;
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, TEXT("Strzelono!")); 
		//MusketModel->SetVisibility(false);
		//GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, TEXT("Wystrzelono pocisk!"));
		
		//FVector ForwardVector = GetOwner()->GetActorForwardVector();
		//FVector SpawnLocation = GetOwner()->GetActorLocation() + (ForwardVector * distanceFromPlayerForBulletToSpawn); //przemnozone ile dalej od wlasciciela zrespic zeby nie zranic go
		
		//AStaticMeshActor* Bullet = GetWorld()->SpawnActor<AStaticMeshActor>(BulletBlueprint, SpawnLocation, GetOwner()->GetActorRotation());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, TEXT("Nie wystrzelono, bo nie ma czego!"));
	}
}
