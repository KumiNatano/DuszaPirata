#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Statuses/EntityStatus.h"
#include "EntityStatusManager.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class DUSZAPIRATA_API UEntityStatusManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UEntityStatusManager();

protected:
	/**
	 * Dictionary of active statuses.
	 */
	UPROPERTY()
	TMap<TSubclassOf<UEntityStatus>, UEntityStatus*> Statuses;
	
	/**
	 * Dictionary of statuses that have to be deleted from list of statuses by next tick.
	 */
	UPROPERTY()
	TMap<TSubclassOf<UEntityStatus>, UEntityStatus*> ToDispose;

	/**
	 * Dictionary of timers for fixed-interval statuses.
	 */
	TMap<TSubclassOf<UEntityStatus>, FTimerHandle> Timers;

	/**
	 * Timer manager used for fixed ticks
	 */
	FTimerManager* TimerManager;

	
	/**
	 * Snippet for status instantiation.
	 * @param Type type of desired status.
	 */
	UFUNCTION()
	UEntityStatus* CreateStatus(TSubclassOf<UEntityStatus> Type);

	
	/**
	 * Called when new status is being added and it needs setup.
	 * @param Status new status.
	 */
	UFUNCTION()
	void HandleNewAdd(UEntityStatus* Status);
	
	/**
	 * Called to solve duplicate status being added.
	 * @param OriginalStatus status that already was there.
	 * @param DuplicateStatus duplicate status of the same status type. Could be null pointer.
	 */
	UFUNCTION()
	void HandleDuplicateAdd(UEntityStatus* OriginalStatus, UEntityStatus* DuplicateStatus);

	/**
	 * Called when fixed-intervally ticked status ended its work. 
	 * @param Status status itself.
	 */
	UFUNCTION()
	void HandleFixedTickableEnd(UEntityStatus* Status);
	
	/**
	 * Called to handle the dispose of statuses.
	 */
	UFUNCTION()
	void HandleToDispose();
	
	/**
	 * Called to do tick for statuses.
	 * @param DeltaTime tick delta time.
	 */
	UFUNCTION()
	void HandleTicks(float DeltaTime);

	
	virtual void BeginPlay() override;
public:	
	/**
	 * Tries to add instance of a status.
	 * In case of success, will return same pointer.
	 * Otherwise, if status manager contains status of same type, it will return it.
	 * If error occurs, could return null pointer.
	 * @param Status an instance add.
	 */
	UFUNCTION(BlueprintCallable)
	UEntityStatus* AddStatus(UEntityStatus* Status);

	/**
	 * Tries to create instance of a status, then add it.
	 * In case of success, will return same pointer.
	 * Otherwise, if status manager contains status of same type, it will return it.
	 * If error occurs, could return null pointer.
	 * @param Type desired status type.
	 */
	UFUNCTION(BlueprintCallable)
	UEntityStatus* AddStatusOfType(TSubclassOf<UEntityStatus> Type);
	
	/**
	 * Tries to get status of desired type.
	 * In case of success, will return pointer to it.
	 * Otherwise, will return null pointer.
	 * @param Type type of desired status.
	 */
	UFUNCTION(BlueprintCallable)
	UEntityStatus* GetStatusOfType(TSubclassOf<UEntityStatus> Type);
	
	/**
	 * Tells if manager has status of desired type.
	 * @param Type type of desired status.
	 */
	UFUNCTION(BlueprintCallable)
	bool HasStatusOfType(TSubclassOf<UEntityStatus> Type);
	
	/**
	 * Tells if manager has status instance.
	 * @param Status instance of status.
	 */
	UFUNCTION(BlueprintCallable)
	bool HasStatus(UEntityStatus* Status);

	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
