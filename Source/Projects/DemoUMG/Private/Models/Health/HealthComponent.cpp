// Copyright Atennop. All Rights Reserved.

#include "Models/Health/HealthComponent.h"

#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentHealth = MaxHealth;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	OnHealthChanged.Execute(CurrentHealth, MaxHealth);
}

void UHealthComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	OnHealthChanged.Unbind();
	GetWorld()->GetTimerManager().ClearTimer(DyingTimerHandle);
}

void UHealthComponent::Damage(const int DamageAmount)
{
	if (bIsDead)
		return;
	
	CurrentHealth -= DamageAmount;
	OnHealthChanged.Execute(CurrentHealth, MaxHealth);

	if (DamageSound != nullptr)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DamageSound, GetOwner()->GetActorLocation());
	
	if (CurrentHealth <= 0)
		Die();
}

void UHealthComponent::Die()
{
	bIsDead = true;
	CurrentHealth = 0;

	const ACharacter *Character = Cast<ACharacter>(GetOwner());
	Character->GetMesh()->SetAllBodiesSimulatePhysics(true);
	Character->GetCapsuleComponent()->DestroyComponent();

	GetWorld()->GetTimerManager().SetTimer(DyingTimerHandle, [&]
	{
		if (DeathWidgetClass == nullptr)
			return;
			
		const auto Widget = CreateWidget(GetWorld(), DeathWidgetClass);
		Widget->AddToViewport();
	}, DeathDelay, false);
}

void UHealthComponent::Heal(const int HealAmount)
{
	if (bIsDead)
		return;
	
	CurrentHealth += HealAmount;
	if (CurrentHealth >= MaxHealth)
		CurrentHealth = MaxHealth;

	OnHealthChanged.Execute(CurrentHealth, MaxHealth);
}
