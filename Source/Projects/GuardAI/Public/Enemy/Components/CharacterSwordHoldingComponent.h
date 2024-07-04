// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterSwordHoldingComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUARDAI_API UCharacterSwordHoldingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCharacterSwordHoldingComponent();

	bool GetIsWithdrawing() const { return IsWithdrawing; }
	bool GetIsSheathing() const { return IsSheathing; }
	
	void Sheath();
	void Withdraw();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class AGuardCharacter *Character = nullptr;

	UPROPERTY()
	AActor *SpawnedSword = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> SwordClass;

	UPROPERTY(EditDefaultsOnly)
	FName SpawnSwordNotifyName;

	UPROPERTY(EditDefaultsOnly)
	FName DestroySwordNotifyName;

	UPROPERTY(EditDefaultsOnly)
	FName SwordSocketName;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage *SheathingMontage = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage *WithdrawingMontage = nullptr;

	bool IsSheathing = false;
	bool IsWithdrawing = false;

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	
	UFUNCTION()
	void OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);
};
