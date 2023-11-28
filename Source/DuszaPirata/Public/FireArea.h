

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
	void DeleteFireAreaParticles();
	void DeleteFireArea();
	FTimerHandle MemberTimerHandle;
};
