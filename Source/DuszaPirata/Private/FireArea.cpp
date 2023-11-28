


#include "FireArea.h"

#include "NiagaraComponent.h"

UFireArea::UFireArea()
{

}

void UFireArea::BeginPlay()
{
	Super::BeginPlay();

	if(bShouldBeDestroyedAfterTime)
	{
		GetOwner()->GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &UFireArea::DeleteFireAreaParticles, LivingTime, false);
	}
	
}

void UFireArea::DeleteFireAreaParticles()
{
	UNiagaraComponent* NiagaraComponent = GetOwner()->FindComponentByClass<UNiagaraComponent>();
	
	if(NiagaraComponent)
	{
		NiagaraComponent->Deactivate();

	}
	GetOwner()->GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &UFireArea::DeleteFireArea, 0.75, false);
	

}

void UFireArea::DeleteFireArea()
{
	GetOwner()->Destroy();
}

