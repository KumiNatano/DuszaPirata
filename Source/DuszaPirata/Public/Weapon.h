#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Engine/StaticMeshActor.h"
#include "Weapon.generated.h"


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
	
	virtual void UseItem() override;
	virtual void ThrowItem() override;
};
