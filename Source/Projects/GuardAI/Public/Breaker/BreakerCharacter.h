// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Models/Character/CharacterGamePausingComponent.h"
#include "Movement/CharacterCrouchingComponent.h"
#include "Movement/CharacterJumpingComponent.h"
#include "Movement/CharacterMovingComponent.h"
#include "Movement/CharacterRotatingComponent.h"
#include "Other/CharacterDistractingComponent.h"
#include "Perception/AISightTargetInterface.h"
#include "BreakerCharacter.generated.h"

UCLASS()
class GUARDAI_API ABreakerCharacter : public ACharacter, public IAISightTargetInterface
{
	GENERATED_BODY()
	
public:
	ABreakerCharacter();

	UCharacterMovingComponent *GetMovingComponent() const { return MovingComponent; }
	UCharacterRotatingComponent *GetRotatingComponent() const { return RotatingComponent; }
	UCharacterCrouchingComponent *GetCrouchingComponent() const { return CrouchingComponent; }
	UCharacterJumpingComponent *GetJumpingComponent() const { return JumpingComponent; }
	UCharacterDistractingComponent *GetDistractingComponent() const { return DistractingComponent; }
	UCharacterGamePausingComponent *GetPausingComponent() const { return GamePausingComponent; }
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCharacterMovingComponent *MovingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCharacterRotatingComponent *RotatingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCharacterCrouchingComponent *CrouchingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCharacterJumpingComponent *JumpingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCharacterDistractingComponent *DistractingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCharacterGamePausingComponent *GamePausingComponent = nullptr;

	virtual bool CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation, int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor, const bool* bWasVisible, int32* UserData) const override;
};
