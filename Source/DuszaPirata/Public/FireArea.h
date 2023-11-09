

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FireArea.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUSZAPIRATA_API UFireArea : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFireArea();
	UPROPERTY(EditAnywhere)
	bool bShouldBeDestroyedAfterTime;
	
	UPROPERTY(EditAnywhere)
	float LivingTime;
	
protected:
	virtual void BeginPlay() override;
	void DeleteFireArea();
	FTimerHandle MemberTimerHandle;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
		
};
