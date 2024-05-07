// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PortalCaptureComponent.h"
#include "PortalTeleportationComponent.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class UNREALLEARNING_API APortal : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly)
	APortal *LinkedPortal;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	USceneCaptureComponent2D *Capture;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent *Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	UPortalCaptureComponent *CaptureComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	UPortalTeleportationComponent *TeleportationComponent;

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
