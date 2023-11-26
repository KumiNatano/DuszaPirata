// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LandscapePathSpline.generated.h"

class USplineComponent;
class USplineMeshComponent;

UCLASS()
class LANDSCAPETOOLS_API ALandscapePathSpline : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALandscapePathSpline();
protected:
	UPROPERTY(EditAnywhere)
	USplineComponent* Spline;
private:
	UPROPERTY(EditAnywhere, Category="Path")
	UMaterialInstance* Material;
	UPROPERTY(EditAnywhere, Category="Path")
	UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere, Category="Path")
	URuntimeVirtualTexture* RuntimeVirtualTexture;
	UPROPERTY()
	TArray<USplineMeshComponent*> SplineMeshes;
#if WITH_EDITOR
protected:
	virtual void OnConstruction(const FTransform& Transform) override;
#endif
	
};
