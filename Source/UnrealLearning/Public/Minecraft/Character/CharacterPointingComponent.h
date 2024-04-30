// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Minecraft/Blocks/IBlock.h"
#include "CharacterPointingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALLEARNING_API UCharacterPointingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	bool Debug;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceLength;
	
	UPROPERTY()
	UObject* PointedObject = nullptr;
	FVector PointLocation = FVector::ZeroVector;
	bool WasCalculatedThisFrame = false;

	void Calculate();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
public:
	UCharacterPointingComponent();

	UObject* GetPointingObject();
	IBlock* GetPointingBlock();
	FVector GetPointLocation();
};
