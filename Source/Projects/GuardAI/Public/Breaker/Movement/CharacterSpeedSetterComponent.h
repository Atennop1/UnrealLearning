// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterSpeedSetterComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUARDAI_API UCharacterSpeedSetterComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UCharacterSpeedSetterComponent();
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,  FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	class ABreakerCharacter *Character = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float WalkSpeed = 600;

	UPROPERTY(EditDefaultsOnly)
	float CrouchSpeed = 300;
};
