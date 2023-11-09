


#include "FireArea.h"

UFireArea::UFireArea()
{

}

void UFireArea::BeginPlay()
{
	Super::BeginPlay();

	if(bShouldBeDestroyedAfterTime)
	{
		GetOwner()->GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &UFireArea::DeleteFireArea, LivingTime, false);
	}
	
}

void UFireArea::DeleteFireArea()
{
	GetOwner()->Destroy();
}

