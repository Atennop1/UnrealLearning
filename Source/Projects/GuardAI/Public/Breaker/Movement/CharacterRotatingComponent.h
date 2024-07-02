// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterRotatingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUARDAI_API UCharacterRotatingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void Rotate(const FVector2D Input) const;	
	UCharacterRotatingComponent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class ABreakerCharacter *Character = nullptr;
};
