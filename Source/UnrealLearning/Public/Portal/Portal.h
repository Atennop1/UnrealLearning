// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PortalCaptureComponent.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class UNREALLEARNING_API APortal : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly)
	APortal *LinkedPortal;
	
	UPROPERTY(EditDefaultsOnly)
	USceneComponent *Root;
	
	UPROPERTY(EditDefaultsOnly)
	USceneCaptureComponent2D *Capture;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent *PortalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	UPortalCaptureComponent *CaptureComponent;

	UPROPERTY()
	UMaterialInstanceDynamic *PortalMaterial;

	UPROPERTY()
	UTextureRenderTarget2D *RenderTexture;

	void Setup();

protected:
	virtual void BeginPlay() override;
	
public:
	APortal();
	void Link(APortal *Portal);
	
	APortal *GetLinkedPortal() const { return LinkedPortal; }
	USceneCaptureComponent2D *GetCapture() const { return Capture; }
};
