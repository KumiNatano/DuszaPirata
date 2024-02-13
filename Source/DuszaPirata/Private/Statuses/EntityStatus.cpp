#include "Statuses/EntityStatus.h"


void UEntityStatus::Activate()
{
	if (!IsBusy)
	{
		CurrentLifespan = Lifespan;
		CurrentTick = 0;
		CurrentTime = 0;
		IsBusy = true;
		
		Started();
		OnStart.Broadcast(this);
	}
}

void UEntityStatus::ExtendLifespan(float ExtendTime)
{
	if (IsBusy && ExtendTime > 0)
	{
		float oldLifespan = CurrentLifespan;
		CurrentLifespan += ExtendTime;
		
		LifespanExtended(oldLifespan, CurrentLifespan);
		OnLifespanExtend.Broadcast(this, oldLifespan, CurrentLifespan);
	}
}

void UEntityStatus::Interrupt()
{
	if (IsBusy)
	{
		Interrupted();
		OnInterrupt.Broadcast(this);
		
		CurrentLifespan = Lifespan;
		CurrentTime = 0;
		CurrentTick = 0;
		IsBusy = false;
	}
}


void UEntityStatus::AssignActor(AActor* Actor)
{
	if (Actor != nullptr)
	{
		if (TargetActor != Actor)
		{
			TargetActor = Actor;
			
			ActorAssigned(TargetActor);
			OnActorAssign.Broadcast(this, TargetActor);
		}
	}
}

void UEntityStatus::Tick(float DeltaTime)
{
	if (IsBusy)
	{
		CurrentTime += DeltaTime;
		if (CurrentTime > CurrentLifespan)
		{
			CurrentTime = CurrentLifespan;
			
			Ended();
			OnEnd.Broadcast(this);
			
			CurrentLifespan = Lifespan;
			CurrentTime = 0;
			CurrentTick = 0;
			IsBusy = false;
		}
		else
		{
			CurrentTick++;
			
			Ticked(DeltaTime);
			OnTick.Broadcast(this, DeltaTime);
		}
	}
}

void UEntityStatus::Tick()
{
	Tick(TickDuration);
}