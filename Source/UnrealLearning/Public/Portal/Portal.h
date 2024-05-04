// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class UNREALLEARNING_API APortal : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly)
	APortal *OtherPortal;
	
	UPROPERTY(EditDefaultsOnly)
	USceneComponent *Root;
	
	UPROPERTY(EditDefaultsOnly)
	USceneCaptureComponent2D *Capture;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent *PortalMesh;

	UPROPERTY()
	UMaterialInstanceDynamic *PortalMaterial;

	UPROPERTY()
	UTextureRenderTarget2D *RenderTexture;

	void Setup();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
public:
	APortal();
	void Link(APortal *Portal);
	USceneCaptureComponent2D *GetCamera() const { return Capture; }
};
