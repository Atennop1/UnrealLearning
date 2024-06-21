// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "FirstPersonCharacter.h"
#include "PortalCharacter.generated.h"

UCLASS()
class PORTALS_API APortalCharacter : public AFirstPersonCharacter
{
	GENERATED_BODY()

private:
	FRotator InitialControlRotation;
	FRotator InitialWorldRotation;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat *ReorientingCurve;
	FTimeline ReorientingTimeline;

	UFUNCTION()
	void OnTimelineTick(float Alpha) const;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
public:
	APortalCharacter();
	void Reorient();
};
