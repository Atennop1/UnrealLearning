// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Portal.h"
#include "Components/ActorComponent.h"
#include "PortalCaptureComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTALS_API UPortalCaptureComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	APortal *Owner = nullptr;

	UPROPERTY()
	USceneCaptureComponent2D *Capture = nullptr;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPortalCaptureComponent();
};
