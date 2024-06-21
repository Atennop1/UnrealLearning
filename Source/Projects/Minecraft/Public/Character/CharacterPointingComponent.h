// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blocks/IBlock.h"
#include "CharacterPointingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINECRAFT_API UCharacterPointingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	bool Debug;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceLength;
	
	FHitResult HitResult;
	bool IsPointing = false;
	bool WasCalculatedThisFrame = false;

	void Calculate();
	
protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UCharacterPointingComponent();
	
public:
	bool IsPointingAtSomething();
	IBlock* GetPointingBlock();
	FHitResult& GetHit();
};
