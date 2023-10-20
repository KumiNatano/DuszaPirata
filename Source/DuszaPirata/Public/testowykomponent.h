

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "testowykomponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUSZAPIRATA_API Utestowykomponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	Utestowykomponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float testoooooowa;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
