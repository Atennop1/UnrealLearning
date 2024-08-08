// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NetworkCharacter.generated.h"

UCLASS()
class NETWORK_API ANetworkCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANetworkCharacter();
	
	class UCharacterMovingComponent *GetMovingComponent() const { return MovingComponent; }
	class UCharacterRotatingComponent *GetRotatingComponent() const { return RotatingComponent; }
	class UCharacterCrouchingComponent *GetCrouchingComponent() const { return CrouchingComponent; }
	class UCharacterJumpingComponent *GetJumpingComponent() const { return JumpingComponent; }

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
