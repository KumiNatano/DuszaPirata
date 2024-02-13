#include "Statuses/EntityDamageStatus.h"


void UEntityDamageStatus::ActorAssigned_Implementation(AActor* Actor)
{
	Health = Actor->FindComponentByClass<UHealthSystem>();
}

void UEntityDamageStatus::Started_Implementation()
{
	DamageGiven = 0;
	if (DamageOnStart)
	{
		Health->TakeDamage(nullptr, StartDamage, nullptr, nullptr, nullptr);
		DamageGiven += StartDamage;
	}
}

void UEntityDamageStatus::Ticked_Implementation(float DeltaTime)
{
	if (DamageOnTick)
	{
		float dmg;

		if (TickDamageType == EEntityStatusTickDamageType::Constant)
		{
			dmg = TickDamage;
		}
		else
		{
			// TODO: Maybe add some restrictions? This could be problem in the future, but for now it's good.
			dmg = DeltaTime / Lifespan;
		}

		Health->TakeDamage(nullptr, dmg, nullptr, nullptr, nullptr);
		DamageGiven += dmg;
	}
}

void UEntityDamageStatus::Ended_Implementation()
{
	if (DamageOnEnd)
	{
		Health->TakeDamage(nullptr, EndDamage, nullptr, nullptr, nullptr);
		DamageGiven += EndDamage;
	}
}