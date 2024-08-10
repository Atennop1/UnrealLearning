// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "Components/NetworkCharacterCrouchingComponent.h"
#include "Components/NetworkCharacterJumpingComponent.h"
#include "Components/NetworkCharacterMovingComponent.h"
#include "Components/NetworkCharacterRotatingComponent.h"
#include "GameFramework/Character.h"
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
};
