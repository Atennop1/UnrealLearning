// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FirstPersonCharacter.h"
#include "PhysicsCharacter.generated.h"

UCLASS()
class PHYSICSSIMULATION_API APhysicsCharacter : public AFirstPersonCharacter
{
	GENERATED_BODY()

public:
	APhysicsCharacter();

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UInputAction *GrabInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	class UPhysicsCharacterGrabbingComponent *GrabbingComponent;
};
