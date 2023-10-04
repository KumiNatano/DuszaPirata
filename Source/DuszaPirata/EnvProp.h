#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnvProp.generated.h"

UCLASS()
class DUSZAPIRATA_API AEnvProp : public AActor
{
	GENERATED_BODY()
	
	
public:	
	AEnvProp();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool CanPickup;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool CanKick;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool CanThrow;

protected:
	virtual void BeginPlay() override;

public:	
	//virtual void Tick(float DeltaTime) override;
};
