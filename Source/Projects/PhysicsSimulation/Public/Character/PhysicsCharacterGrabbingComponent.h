// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "PhysicsCharacter.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "PhysicsCharacterGrabbingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PHYSICSSIMULATION_API UPhysicsCharacterGrabbingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPhysicsCharacterGrabbingComponent();
	void Grab(const FInputActionValue& Value);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UPhysicsHandleComponent *PhysicsHandle = nullptr;
	bool bIsGrabbing = false;

	UPROPERTY()
	APhysicsCharacter *Character = nullptr;
};
