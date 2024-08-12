// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "Movement/NetworkCharacterCrouchingComponent.h"
#include "Movement/NetworkCharacterJumpingComponent.h"
#include "Movement/NetworkCharacterMovingComponent.h"
#include "Movement/NetworkCharacterRotatingComponent.h"
#include "GameFramework/Character.h"
#include "Shooting/NetworkCharacterPeekingComponent.h"
#include "Shooting/NetworkCharacterShootingComponent.h"
#include "NetworkCharacter.generated.h"

UCLASS()
class NETWORK_API ANetworkCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANetworkCharacter();
	
	UNetworkCharacterMovingComponent *GetMovingComponent() const { return MovingComponent; }
	UNetworkCharacterRotatingComponent *GetRotatingComponent() const { return RotatingComponent; }
	UNetworkCharacterCrouchingComponent *GetCrouchingComponent() const { return CrouchingComponent; }
	UNetworkCharacterJumpingComponent *GetJumpingComponent() const { return JumpingComponent; }
	UNetworkCharacterPeekingComponent *GetPeekingComponent() const { return PeekingComponent; }
	UNetworkCharacterShootingComponent *GetShootingComponent() const { return ShootingComponent; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UNetworkCharacterMovingComponent *MovingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UNetworkCharacterRotatingComponent *RotatingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UNetworkCharacterCrouchingComponent *CrouchingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UNetworkCharacterJumpingComponent *JumpingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UNetworkCharacterPeekingComponent *PeekingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UNetworkCharacterShootingComponent *ShootingComponent = nullptr;
};
