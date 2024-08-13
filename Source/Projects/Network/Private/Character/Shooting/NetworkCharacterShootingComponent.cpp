﻿// Copyright Atennop. All Rights Reserved.

#include "Character/Shooting/NetworkCharacterShootingComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/NetworkCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

UNetworkCharacterShootingComponent::UNetworkCharacterShootingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNetworkCharacterShootingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ANetworkCharacter>(GetOwner());
	check(IsValid(Character))

	Camera = Character->GetComponentByClass<UCameraComponent>();
	check(IsValid(Camera))
}

void UNetworkCharacterShootingComponent::ServerShoot_Implementation()
{
	if (!Character->GetHealthComponent()->IsAlive())
		return;
	
	const FVector Start = Camera->GetComponentLocation();
	const FVector End = Start + Camera->GetForwardVector() * 30000;

	FHitResult HitResult;
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, TraceTypeQuery1, false, TArray<AActor*> { Character }, EDrawDebugTrace::ForDuration, HitResult, true);

	if (const auto Enemy = Cast<ANetworkCharacter>(HitResult.GetActor()); Enemy != nullptr)
		Enemy->GetHealthComponent()->TakeDamage(Damage);
}
