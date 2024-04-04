#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Engine/StaticMeshActor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Firearm.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUSZAPIRATA_API UWeapon : public UItem
{
	GENERATED_BODY()

public:
	UWeapon();
	~UWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Config")
	TSubclassOf<AActor> bulletBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Config")
	int ammoAtStart = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Config")
	int maxAmmo = 3;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Config")
	int actualAmmo;

	void BeginPlay() override;

	
	UPROPERTY(EditAnywhere, Category = "Smoke")
	TArray<UNiagaraSystem*> smokeEffects;
	
	virtual void UseItem() override;
	void SpawnSmokeEffects(FVector SpawnLocation);
	virtual void ThrowItem() override;
};
