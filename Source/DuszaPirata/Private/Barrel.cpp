#include "Barrel.h"

#include "ExplosionComponent.h"
#include "HealthSystem.h"


// Sets default values
ABarrel::ABarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABarrel::BeginPlay()
{
	Super::BeginPlay();
	
	UHealthSystem* HealthComponent = this->FindComponentByClass<UHealthSystem>();
	if (HealthComponent)
	{
		HealthComponent->OnDeath.AddDynamic(this, &ABarrel::HandleDeath);
	}
}

// Called every frame
void ABarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABarrel::HandleDeath(AActor* DamagedActor, float Damage,
		const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	UExplosionComponent* ExplosionComponent = this->FindComponentByClass<UExplosionComponent>();
	if (ExplosionComponent)
	{
		ExplosionComponent->TriggerExplosion();
		Destroy();
	}
}

