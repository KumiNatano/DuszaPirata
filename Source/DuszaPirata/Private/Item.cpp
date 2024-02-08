


#include "Item.h"

// Sets default values for this component's properties
UItem::UItem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UItem::UseItem()
{
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, TEXT("Uzyto itemu")); 
}

void UItem::ThrowItem()
{
	if(IsThrowable)
	{
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, TEXT("Rzucono item i zadano " + FString::SanitizeFloat(ThrowDamage) + " obrazen")); 
	}
}

// Called when the game starts
void UItem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UItem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

