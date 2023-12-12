


#include "MusketPickup.h"

#include "MusketSystem.h"
#include "DuszaPirata/Hero.h"

// Sets default values for this component's properties
UMusketPickup::UMusketPickup()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMusketPickup::BeginPlay()
{
	Super::BeginPlay();

	if (UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()))
	{
		PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &UMusketPickup::OnOverlapBegin);
		PrimitiveComponent->OnComponentEndOverlap.AddDynamic(this, &UMusketPickup::OnOverlapEnd);
	}
	
}


// Called every frame
void UMusketPickup::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UMusketPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GetOwner()->GetOverlappingActors(OverlappingActors, nullptr); //zaktualizuj liste rzeczy w strefie

	if(!GetOwner()->GetWorldTimerManager().IsTimerActive(MemberTimerHandle)) //jesli timer nie jest uzywany to
		{
		GetOwner()->GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &UMusketPickup::SomethingIsOnPickup, 0.5, true, 0.0f); //aktywuj timer
		}
}

void UMusketPickup::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GetOwner()->GetOverlappingActors(OverlappingActors, nullptr); //zaktualizuj liste rzeczy w strefie
}

void UMusketPickup::SomethingIsOnPickup()
{
	if(OverlappingActors.IsEmpty() == false) //jesli lista obiektow w kolizji nie jest pusta
		{
			for (auto Element : OverlappingActors)
			{
				AHero* PlayerCharacter = Cast<AHero>(Element);
				if (PlayerCharacter)
				{
					UMusketSystem* MusketSystem = Cast<UMusketSystem>(PlayerCharacter->GetComponentByClass(UMusketSystem::StaticClass()));

					if (MusketSystem)
					{
						if(MusketSystem->TryPickUpAmmo())
						{
							GetOwner()->Destroy();
						}
					}
				}
			}
		}
	else //jesli jest to dezaktywuj timer
		{
		GetOwner()->GetWorldTimerManager().ClearTimer(MemberTimerHandle);	
		}
}

