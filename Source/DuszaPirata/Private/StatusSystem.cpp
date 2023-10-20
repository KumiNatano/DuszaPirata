#include "StatusSystem.h"

UStatusSystem::UStatusSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStatusSystem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UStatusSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (GetWorld() && GetWorld()->GetFirstPlayerController() && GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::K))
	{
		TurnOnStatus(10,0.5,1);
	}
}

void UStatusSystem::TurnOnStatus(float duration, float tickrate, float damage)
{
	IsStatusActive = true;
	damageToDealPerTick = damage;
	DurationOfStatus = duration/tickrate;
	GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &UStatusSystem::ReapeatingDamage, tickrate, true, 0.0f);
}

void UStatusSystem::TurnOffStatus()
{
	IsStatusActive = false;
}

void UStatusSystem::ReapeatingDamage()
{
	if (--DurationOfStatus <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(MemberTimerHandle);
		TurnOffStatus();
	}

	AActor* Owner = GetOwner();
	if (Owner)
	{
		UHealthSystem* HealthComp = Owner->FindComponentByClass<UHealthSystem>();
		if (HealthComp)
		{
			AActor* DamagedActor = Owner;
			float DamageAmount = damageToDealPerTick;
			const UDamageType* DamageType = nullptr;
			AController* InstigatedBy = nullptr;
			AActor* DamageCauser = Owner;
			HealthComp->TakeDamage(DamagedActor, DamageAmount, DamageType, InstigatedBy, DamageCauser);
		}
	}
}
