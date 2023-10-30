


#include "HealthSystem.h"

// Sets default values for this component's properties
UHealthSystem::UHealthSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	DefaultHealth = 100;
	Health = DefaultHealth;
	MaxHealth = 100;
	bIsDead = false;

}


// Called when the game starts
void UHealthSystem::BeginPlay()
{
	Super::BeginPlay();
	
	AActor* Owner = GetOwner();
	if(Owner)
	{
		//Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthSystem::TakeDamage);
	}
	
}

void UHealthSystem::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{

	if(bIsDead == false)
	{
		if(Damage <= 0)
		{
			return;
		}
		
		Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);
		
		
		if(Health <= 0)
		{
			bIsDead = true;
			OnDeath.Broadcast();
		}
		
		if(AActor* Owner = GetOwner())
		{
			UFunction* DamageTakenFunction = Owner->FindFunction(FName("RefreshHPBar"));
			if(DamageTakenFunction)
			{
				Owner->ProcessEvent(DamageTakenFunction, nullptr);
			}
		}
	}
	

}

