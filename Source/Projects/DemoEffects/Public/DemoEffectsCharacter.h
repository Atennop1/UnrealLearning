// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/ThirdPerson/Public/ThirdPersonCharacter.h"
#include "DemoEffectsCharacter.generated.h"

UCLASS()
class DEMOEFFECTS_API ADemoEffectsCharacter : public AThirdPersonCharacter
{
	GENERATED_BODY()

public:
	ADemoEffectsCharacter();
	void SetCanMove(const bool bNewCanMove) { bCanMove = bNewCanMove; }

	class UCharacterAuraCastingComponent *GetAuraCastingComponent() const { return AuraCastingComponent; }
	class UCharacterBlastingComponent *GetBlastingComponent() const { return BlastingComponent; }

protected:
	virtual void Jump() override;
	virtual void Move(const FInputActionValue& Value) override;
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UCharacterAuraCastingComponent *AuraCastingComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UCharacterBlastingComponent *BlastingComponent = nullptr;
	
	bool bCanMove = true;
};
