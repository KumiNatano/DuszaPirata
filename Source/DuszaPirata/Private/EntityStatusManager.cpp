#include "EntityStatusManager.h"


UEntityStatus* UEntityStatusManager::CreateStatus(TSubclassOf<UEntityStatus> Type)
{
	return NewObject<UEntityStatus>(this, Type);
}


void UEntityStatusManager::HandleNewAdd(UEntityStatus* Status)
{
	UClass* type = Status->GetClass();
	Statuses.Add(type, Status);
	Status->AssignActor(GetOwner());
	Status->Activate();
	// Start ticking process for fixed-interval ticked statuses
	if (Status->TickType == EEntityStatusTickType::Fixed)
	{
		FTimerHandle handle;
		float tickrate = Status->TickDuration;
		Status->OnEnd.AddDynamic(this, &UEntityStatusManager::HandleFixedTickableEnd);
		TimerManager->SetTimer(handle, Status, &UEntityStatus::Tick, tickrate, true, tickrate);
		Timers.Add(type, handle);
	}
}

void UEntityStatusManager::HandleDuplicateAdd(UEntityStatus* OriginalStatus, UEntityStatus* DuplicateStatus)
{
	if (!OriginalStatus->IsBusy)
	{
		UClass* type = OriginalStatus->GetClass();
		Statuses[type] = DuplicateStatus;
		// TODO: If status is fixed-intervaled, then stop timer for original status and set a new one for new status. At the moment I'm too lazy to implement that
	}
	else
	{
		float extendTime = DuplicateStatus != nullptr? DuplicateStatus->Lifespan : OriginalStatus->Lifespan;
		OriginalStatus->ExtendLifespan(extendTime);
	}
}

void UEntityStatusManager::HandleFixedTickableEnd(UEntityStatus* Status)
{
	UClass* type = Status->GetClass();

	if (Timers.Contains(type))
	{
		TimerManager->ClearTimer(Timers[type]);
		ToDispose.Add(type, Status);
	}
}

void UEntityStatusManager::HandleToDispose()
{
	for (auto iterator = ToDispose.CreateIterator(); iterator; ++iterator)
	{
		TSubclassOf<UEntityStatus> type = iterator.Key();

		if (Statuses.Contains(type))
		{
			UEntityStatus* disposeStatus = iterator.Value();
			UEntityStatus* currentStatus = Statuses[type];
			
			if (disposeStatus && currentStatus == disposeStatus)
			{
				Statuses.Remove(type);
			}
		}

		iterator.RemoveCurrent();
	}
}


void UEntityStatusManager::HandleTicks(float DeltaTime)
{
	HandleToDispose();
	
	for (auto iterator = Statuses.CreateIterator(); iterator; ++iterator)
	{
		UEntityStatus* status = iterator.Value();

		if (status != nullptr)
		{
			if (status->IsBusy && status->TickType == EEntityStatusTickType::TickComponent)
			{
				status->Tick(DeltaTime);

				if (!status->IsBusy)
				{
					iterator.RemoveCurrent();
				}
			}
		}
		else
		{
			iterator.RemoveCurrent();
		}
	}
}


UEntityStatus* UEntityStatusManager::AddStatus(UEntityStatus* Status)
{
	UEntityStatus* result;

	if (Status)
	{
		if (Status->IsBusy)
		{
			return nullptr;
		}
		
		UClass* type = Status->GetClass();

		if (Statuses.Contains(type))
		{
			result = Statuses[type];
			if (result != nullptr)
			{
				HandleDuplicateAdd(result, Status);
			}
			else
			{
				Statuses.Remove(type);
			}
		}
		else
		{
			result = Status;
			HandleNewAdd(Status);
		}
	}
	else
	{
		result = nullptr;
	}

	return result;
}

UEntityStatus* UEntityStatusManager::AddStatusOfType(TSubclassOf<UEntityStatus> Type)
{
	UEntityStatus* status;
	
	if (Statuses.Contains(Type))
	{
		status = Statuses[Type];
		if (status != nullptr)
		{
			HandleDuplicateAdd(status, nullptr);
		}
		else
		{
			Statuses.Remove(Type);
		}
	}
	else
	{
		status = CreateStatus(Type);
		if (status != nullptr)
		{
			HandleNewAdd(status);
		}
	}
	
	return status;
}

UEntityStatus* UEntityStatusManager::GetStatusOfType(TSubclassOf<UEntityStatus> Type)
{
	UEntityStatus* status = nullptr;
	
	if (Statuses.Contains(Type))
	{
		status = Statuses[Type];	
	}

	return status;
}

bool UEntityStatusManager::HasStatusOfType(TSubclassOf<UEntityStatus> Type)
{
	return GetStatusOfType(Type) != nullptr;
}

bool UEntityStatusManager::HasStatus(UEntityStatus* Status)
{
	UClass* type = Status->GetClass();

	if(Statuses.Contains(type))
	{
		return Statuses[type] == Status;
	}

	return false;
}


UEntityStatusManager::UEntityStatusManager()
{
	PrimaryComponentTick.bCanEverTick = true;

	TimerManager = nullptr;
}

void UEntityStatusManager::BeginPlay()
{
	Super::BeginPlay();
	
	TimerManager = &GetWorld()->GetTimerManager();
}

void UEntityStatusManager::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HandleTicks(DeltaTime);
}