


#include "Bullet.h"

#include "HealthSystem.h"

// Sets default values for this component's properties
UBullet::UBullet()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UBullet::BeginPlay()
{
	Super::BeginPlay();

	if (UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()))
	{
		PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &UBullet::OnOverlapBegin);
	}

	if(!GetOwner()->GetWorldTimerManager().IsTimerActive(MemberTimerHandle)) //jesli timer nie jest uzywany to
	{
		GetOwner()->GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &UBullet::DestroyBulletObject, TimeToDestroy, false); //aktywuj timer
	}
}


// Called every frame
void UBullet::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBullet::DestroyBulletObject()
{
	GetOwner()->Destroy();
}

void UBullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UHealthSystem* HealthComponent = OtherActor->FindComponentByClass<UHealthSystem>();
	if (HealthComponent)
	{
		AActor* DamagedActor = OtherActor;
		float DamageAmount = DamageToDeal;
		const UDamageType* DamageType = nullptr;
		AController* InstigatedBy = nullptr;
		AActor* DamageCauser = GetOwner();
		HealthComponent->TakeDamage(DamagedActor, DamageAmount, DamageType, InstigatedBy, DamageCauser);
	}

	DestroyBulletObject();
}



