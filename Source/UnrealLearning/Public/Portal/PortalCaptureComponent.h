// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/ArrowComponent.h"
#include "PortalCaptureComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALLEARNING_API UPortalCaptureComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class APortal *Owner;
	
	UPROPERTY(EditDefaultsOnly)
	USceneCaptureComponent2D *Capture;
	
	UPROPERTY(EditDefaultsOnly)
	UArrowComponent *ForwardDirection;
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent *PortalMesh;
	

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPortalCaptureComponent();
};
