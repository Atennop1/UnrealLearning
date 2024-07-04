// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterAttackingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUARDAI_API UCharacterAttackingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCharacterAttackingComponent();

	bool GetIsAttacking() const { return IsAttacking; }
	void Attack();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class AGuardCharacter *Character = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FName SlashNotifyName = "Slash";

	UPROPERTY(EditDefaultsOnly)
	float AttackRadius = 25;

	UPROPERTY(EditDefaultsOnly)
	float AttackLength = 150;

	UPROPERTY(EditDefaultsOnly)
	int Damage = 30;
	
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage *AttackingMontage = nullptr;
	bool IsAttacking = false;

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);
};
