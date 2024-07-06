// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnHealthChanged, int, NewHealth, int, MaxHealth);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEMOUMG_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FOnHealthChanged OnHealthChanged;

	bool IsDead() const { return bIsDead; }
	void Damage(int DamageAmount);
	void Heal(int HealAmount);
	
	UHealthComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
private:
	UPROPERTY(EditAnywhere)
	int MaxHealth = 0;
	int CurrentHealth = 0;

	UPROPERTY(EditDefaultsOnly)
	float DeathDelay;
	
	UPROPERTY(EditDefaultsOnly)
	USoundBase *DamageSound = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> DeathWidgetClass;
	
	FTimerHandle DyingTimerHandle;
	bool bIsDead = false;
	
	UFUNCTION()
	void Die();
};
