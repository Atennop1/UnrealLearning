// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Movement/CharacterCrouchingComponent.h"
#include "Movement/CharacterJumpingComponent.h"
#include "Movement/CharacterMovingComponent.h"
#include "Movement/CharacterRotatingComponent.h"
#include "BreakerCharacter.generated.h"

UCLASS()
class GUARDAI_API ABreakerCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	ABreakerCharacter();

	UCharacterMovingComponent *GetMovingComponent() const { return MovingComponent; }
	UCharacterRotatingComponent *GetRotatingComponent() const { return RotatingComponent; }
	UCharacterCrouchingComponent *GetCrouchingComponent() const { return CrouchingComponent; }
	UCharacterJumpingComponent *GetJumpingComponent() const { return JumpingComponent; }
	
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
};
