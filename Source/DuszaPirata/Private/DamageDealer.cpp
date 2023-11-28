#include "DamageDealer.h"

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
		PrimitiveComponent->OnComponentEndOverlap.AddDynamic(this, &UDamageDealer::OnOverlapEnd);
	}
	
}

void UDamageDealer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GetOwner()->GetOverlappingActors(OverlappingActors, nullptr); //zaktualizuj liste rzeczy w strefie

	if(!GetOwner()->GetWorldTimerManager().IsTimerActive(MemberTimerHandle)) //jesli timer nie jest uzywany to
	{
		GetOwner()->GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &UDamageDealer::DealDamageInArea, TimeRateToDamage, true, 0.0f); //aktywuj timer
	}
}

void UDamageDealer::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GetOwner()->GetOverlappingActors(OverlappingActors, nullptr); //zaktualizuj liste rzeczy w strefie
}

void UDamageDealer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDamageDealer::DealDamageInArea()
{

	if(OverlappingActors.IsEmpty() == false) //jesli lista obiektow w kolizji nie jest pusta
	{
		for (auto Element : OverlappingActors)
		{
			UHealthSystem* HealthComponent = Element->FindComponentByClass<UHealthSystem>();
			if (HealthComponent)
			{
				AActor* DamagedActor = Element;
				float DamageAmount = DamageToDeal;
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
	else //jesli jest to dezaktywuj timer
	{
		GetOwner()->GetWorldTimerManager().ClearTimer(MemberTimerHandle);	
	}
}

