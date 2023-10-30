// 


#include "AttackSystem.h"

#include "HealthSystem.h"


// Sets default values for this component's properties
UAttackSystem::UAttackSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	DefaultDamage = 50;
	Damage = DefaultDamage;

	DefaultStrength = 2;
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
	
}

