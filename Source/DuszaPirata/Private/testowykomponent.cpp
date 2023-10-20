


#include "testowykomponent.h"

// Sets default values for this component's properties
Utestowykomponent::Utestowykomponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void Utestowykomponent::BeginPlay()
{
	Super::BeginPlay();
	testoooooowa = 100;
	// ...
	
}


// Called every frame
void Utestowykomponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	testoooooowa--;

	// ...
}

