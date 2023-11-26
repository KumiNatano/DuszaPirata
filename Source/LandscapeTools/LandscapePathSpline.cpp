#include "LandscapePathSpline.h"

#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

#if WITH_EDITOR
#include "EditorViewportClient.h"
#include "Editor/UnrealEdEngine.h"
#include "SplineComponentVisualizer.h"
#include "UnrealEdGlobals.h"
#endif


ALandscapePathSpline::ALandscapePathSpline()
{
	PrimaryActorTick.bCanEverTick = false;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	RootComponent = Spline;
}

#if WITH_EDITOR
void ALandscapePathSpline::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!GEditor) { return; }
	FViewport* Viewport = GEditor->GetActiveViewport();
	if (!Viewport) { return; }
	FViewportClient* Client = Viewport->GetClient();
	if (!Client) { return; }
	const FEditorViewportClient* ViewportClient = StaticCast<FEditorViewportClient*>(Client);
	if (!ViewportClient) { return; }

	const TSharedPtr<FSplineComponentVisualizer> SplineVisualiser
		= StaticCastSharedPtr<FSplineComponentVisualizer>(
			GUnrealEd->FindComponentVisualizer(USplineComponent::StaticClass()));
	if (!SplineVisualiser) { return; }

	const UWorld* World = GetWorld();
	if (!World) { return; }

	for (TSet<int32> Keys = SplineVisualiser->GetSelectedKeys(); const int32 Key : Keys)
	{
		const FVector Position = Spline->GetLocationAtSplinePoint(Key, ESplineCoordinateSpace::World);
		const FVector CameraPosition = ViewportClient->GetViewLocation();
		const FVector CastEnd = CameraPosition + (Position - CameraPosition).GetSafeNormal() * 100000.0;

		if (FHitResult OutHit;
			World->LineTraceSingleByChannel(OutHit, CameraPosition, CastEnd, ECC_WorldStatic))
		{
			Spline->SetLocationAtSplinePoint(Key, OutHit.Location, ESplineCoordinateSpace::World, false);
		}
	}

	for (USplineMeshComponent* MeshComponent : SplineMeshes)
	{
		MeshComponent->DestroyComponent();
	}
	SplineMeshes.Empty();

	for (int32 i = 0; i < Spline->GetNumberOfSplinePoints(); ++i)
	{
		Spline->SetUpVectorAtSplinePoint(i, FVector::UpVector, ESplineCoordinateSpace::World, false);
	}
	Spline->UpdateSpline();

	const int32 End = Spline->GetNumberOfSplinePoints() - 1;

	for (int32 i = 0; i < End; ++i)
	{
		USplineMeshComponent* SplineMesh
			= NewObject<USplineMeshComponent>(this, FName(FString::Printf(TEXT("Mesh%d"), i)));
		SplineMesh->RegisterComponent();

		SplineMesh->SetStartPosition(Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World), false);
		SplineMesh->SetEndPosition(Spline->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::World), false);
		SplineMesh->SetStartTangent(Spline->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::World), false);
		SplineMesh->SetEndTangent(Spline->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::World), false);
		SplineMesh->SetStartScale(FVector2d(Spline->GetScaleAtSplinePoint(i)), false);
		SplineMesh->SetEndScale(FVector2d(Spline->GetScaleAtSplinePoint(i + 1)), true);

		SplineMesh->SetMaterial(0, Material);
		SplineMesh->SetStaticMesh(Mesh);
		SplineMeshes.Add(SplineMesh);
		SplineMesh->RuntimeVirtualTextures.Add(RuntimeVirtualTexture);
	}
}
#endif
