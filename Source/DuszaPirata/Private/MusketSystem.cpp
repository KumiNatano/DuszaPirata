


#include "MusketSystem.h"

// Sets default values for this component's properties
UMusketSystem::UMusketSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

UStaticMeshComponent* MusketModel = nullptr;

// Called when the game starts
void UMusketSystem::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UStaticMeshComponent*> Components;
	GetOwner()->GetComponents<UStaticMeshComponent>(Components);
	
	for (UStaticMeshComponent* Component : Components)
	{
		if (Component->GetName() == "MusketModel")
		{
			MusketModel = Component;
			break;
		}
	}
	
}


// Called every frame
void UMusketSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UMusketSystem::TryPickUpAmmo()
{
	if(isLoaded)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, TEXT("Mamy juz pocisk, nie da sie podniesc!"));
		return false;
	}
	else
	{
		if (MusketModel)
		{
			MusketModel->SetVisibility(true);
		}
	
		isLoaded = true;
		//GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, TEXT("Podniesiono pocisk!"));
		return true;
	}

}

void UMusketSystem::Shoot()
{
	if(isLoaded)
	{
		isLoaded = false;
		MusketModel->SetVisibility(false);
		//GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, TEXT("Wystrzelono pocisk!"));
		
		FVector ForwardVector = GetOwner()->GetActorForwardVector();
		FVector SpawnLocation = GetOwner()->GetActorLocation() + (ForwardVector * distanceFromPlayerForBulletToSpawn); //przemnozone ile dalej od wlasciciela zrespic zeby nie zranic go
		
		AStaticMeshActor* Bullet = GetWorld()->SpawnActor<AStaticMeshActor>(BulletBlueprint, SpawnLocation, GetOwner()->GetActorRotation());
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, TEXT("Nie wystrzelono, bo nie ma czego!"));
	}
}

