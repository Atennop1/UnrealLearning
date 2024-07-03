﻿// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterMovingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUARDAI_API UCharacterMovingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void Move(const FVector2D Input) const;
	UCharacterMovingComponent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class ABreakerCharacter *Character = nullptr;

	UPROPERTY(EditDefaultsOnly)
	bool IsMakingNoise = false;
};