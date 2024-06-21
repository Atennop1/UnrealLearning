// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class PORTALS_API APortal : public AActor
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
	UArrowComponent *ForwardDirection;

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
	FVector GetForwardDirection() const { return ForwardDirection->GetForwardVector(); }
};
