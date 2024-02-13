#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EntityStatus.generated.h"


UENUM(BlueprintType)
enum EEntityStatusTickType
{
	TickComponent,  // Invoke tick event each frame
	Fixed			// Invoke tick event every x seconds
};

UCLASS(Abstract, Blueprintable)
class DUSZAPIRATA_API UEntityStatus : public UObject
{
	GENERATED_BODY()

	
	UDELEGATE(BlueprintAuthorityOnly)
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
		FOnActorAssignSignature,
		UEntityStatus*, Status,
		AActor*, Actor);
	
	UDELEGATE(BlueprintAuthorityOnly)
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
		FOnStartSignature,
		UEntityStatus*, Status);
	
	UDELEGATE(BlueprintAuthorityOnly)
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
		FOnTickSignature,
		UEntityStatus*, Status,
		float, DeltaTime);
	
	UDELEGATE(BlueprintAuthorityOnly)
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
		FOnLifespanExtendSignature,
		UEntityStatus*, Status,
		float, OldLifespan,
		float, NewLifespan);
	
	UDELEGATE(BlueprintAuthorityOnly)
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
		FOnInterruptSignature,
		UEntityStatus*, Status);
	
	UDELEGATE(BlueprintAuthorityOnly)
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
		FOnEndSignature,
		UEntityStatus*, Status);
protected:
	/**
	 * Called when actor was assigned to status.
	 * @param Actor an actor that was assigned.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Events")
	void ActorAssigned(AActor* Actor);
	
	/**
	 * Called before status starts its work.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Events")
	void Started();

	/**
	 * Called each tick of status.
	 * @param DeltaTime time that has passed since last tick.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Events")
	void Ticked(float DeltaTime);

	/**
	 * Called when lifespan of status was extended.
	 * @param OldLifespan lifespan of a status before lifespan extension
	 * @param NewLifespan lifespan of a status after lifespan extension
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Events")
	void LifespanExtended(float OldLifespan, float NewLifespan);

	/**
	 * Called before interruption of work.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Events")
	void Interrupted();

	/**
	 * Called before status stops its work.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Events")
	void Ended();

	
	/**
	 * Called when actor was assigned to status.
	 * @param Actor an actor that was assigned.
	 */
	virtual void ActorAssigned_Implementation(AActor* Actor);
	
	/**
	 * Called before status starts its work.
	 */
	virtual void Started_Implementation();
	
	/**
	 * Called each tick of status.
	 * @param DeltaTime time that has passed since last tick.
	 */
	virtual void Ticked_Implementation(float DeltaTime);
	
	/**
	 * Called when lifespan of status was extended.
	 * @param OldLifespan lifespan of a status before lifespan extension
	 * @param NewLifespan lifespan of a status after lifespan extension
	 */
	virtual void LifespanExtended_Implementation(float OldLifespan, float NewLifespan);
	
	/**
	 * Called before interruption of work.
	 */
	virtual void Interrupted_Implementation();
	
	/**
	 * Called before status stops its work.
	 */
	virtual void Ended_Implementation();
public:
	/**
	 * Broadcasts when actor was assigned to status.
	 * @param Actor an actor that was assigned.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnActorAssignSignature OnActorAssign;
	
	/**
	 * Broadcasts before status starts its work.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnStartSignature OnStart;
	
	/**
	 * Broadcasts each tick of status.
	 * @param DeltaTime time that has passed since last tick.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnTickSignature OnTick;
	
	/**
	 * Broadcasts when lifespan of status was extended.
	 * @param OldLifespan lifespan of a status before lifespan extension
	 * @param NewLifespan lifespan of a status after lifespan extension
	 */
	UPROPERTY(BlueprintAssignable)
	FOnLifespanExtendSignature OnLifespanExtend;
	
	/**
	 * Broadcasts before interruption of work.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnInterruptSignature OnInterrupt;
	
	/**
	 * Broadcasts before status stops its work.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnEndSignature OnEnd;


	
	/**
	 * Default status duration time.
	 * If current time hits it, status will end, but it may be extended. 
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings")
	float Lifespan;
	
	/**
	 * Fixed interval between each tick. Use only if tick type is set to "Fixed".
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings")
	float TickDuration;

	/**
	 * Determines how tick event should be invoked: each frame, or every x seconds.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings")
	TEnumAsByte<EEntityStatusTickType> TickType;

	
	/**
	 * Tells if status is actively working.
	 */
	UPROPERTY(BlueprintReadOnly, Category="State")
	bool IsBusy;
	
	/**
	 * Work timer of status (in seconds).
	 * If status is not active, then equals 0.
	 */
	UPROPERTY(BlueprintReadOnly, Category="State")
	float CurrentTime = 0;
	
	/**
	 * Tick counter of status.
	 * If status is not active, then equals 0.
	 */
	UPROPERTY(BlueprintReadOnly, Category="State")
	int CurrentTick = 0;
	
	/**
	 * Duration of status's work. Lifespan of status may be extended.
	 * If status is not active, then equals default duration value of this status.
	 */
	UPROPERTY(BlueprintReadOnly, Category="State")
	float CurrentLifespan;

	/**
	 * No need for description.
	 */
	UPROPERTY(BlueprintReadOnly, Category="State")
	AActor* TargetActor;
	

	
	/**
	 * Call to begin work.
	 */
	UFUNCTION(BlueprintCallable)
	void Activate();

	/**
	 * If you want to extend lifespan of status during work, then call this
	 * @param ExtendTime time in seconds that will be added to lifespan of a status.
	 */
	UFUNCTION(BlueprintCallable)
	void ExtendLifespan(float ExtendTime);

	/**
	 * Used to stop work of a status when it's active.
	 */
	UFUNCTION(BlueprintCallable)
	void Interrupt();

	
	/**
	 * Attaches status to an actor.
	 * Only call this in status manager!
	 * @param Actor an actor to assign for status.
	 */
	void AssignActor(AActor* Actor);
	
	/**
	 * Do not call this directly!
	 * Only status manager should call this function.
	 */
	void Tick();
	
	/**
	 * Do not call this directly!
	 * Only status manager should call this function.
	 * @param DeltaTime time that has passed since last tick.
	 */
	void Tick(float DeltaTime);
};