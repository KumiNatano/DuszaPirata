


#include "DamageDealer.h"

#include "HealthSystem.h"

UDamageDealer::UDamageDealer()
{
	//PrimaryComponentTick.bCanEverTick = true;
}

void UDamageDealer::BeginPlay()
{
	Super::BeginPlay();

	if (UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()))
	{
		PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &UDamageDealer::OnOverlapBegin);
	}
	
}

void UDamageDealer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		UHealthSystem* HealthComponent = OtherActor->FindComponentByClass<UHealthSystem>();
		if (HealthComponent)
		{
			AActor* DamagedActor = OtherActor;
			float DamageAmount = 10;
			const UDamageType* DamageType = nullptr;
			AController* InstigatedBy = nullptr;
			AActor* DamageCauser = GetOwner();
			HealthComponent->TakeDamage(DamagedActor, DamageAmount, DamageType, InstigatedBy, DamageCauser);
		}
		else
		{
			
		}
	} 
}

void UDamageDealer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

