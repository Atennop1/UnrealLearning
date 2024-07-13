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

	class UCharacterAuraCastingComponent *GetCharacterAuraCastingComponent() const { return CharacterAuraCastingComponent; }

protected:
	virtual void Jump() override;
	virtual void Move(const FInputActionValue& Value) override;
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UCharacterAuraCastingComponent *CharacterAuraCastingComponent = nullptr;
	
	bool bCanMove = true;
};
