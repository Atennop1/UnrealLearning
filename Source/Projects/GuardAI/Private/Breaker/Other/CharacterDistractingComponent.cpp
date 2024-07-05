// Copyright Atennop. All Rights Reserved.

#include "Breaker/Other/CharacterDistractingComponent.h"
#include "Camera/CameraComponent.h"
#include "Enemy/GuardCharacter.h"
#include "Environment/Distractor.h"
#include "Kismet/KismetSystemLibrary.h"

UCharacterDistractingComponent::UCharacterDistractingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterDistractingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ABreakerCharacter>(GetOwner());
	check(IsValid(Character))
}

void UCharacterDistractingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	const UCameraComponent *Camera = Character->GetComponentByClass<UCameraComponent>();
	FHitResult HitResult;

	const bool WasHit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Camera->GetComponentLocation(), Camera->GetComponentLocation() + Camera->GetForwardVector() * 100000, 100,
		TArray<TEnumAsByte<EObjectTypeQuery>> { ObjectTypeQuery1, ObjectTypeQuery2, ObjectTypeQuery8 }, false, { Character }, EDrawDebugTrace::None, HitResult, true);

	if (WasHit)
		GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Cyan, HitResult.GetActor()->GetName());
	
	if (WasHit && Cast<ADistractor>(HitResult.GetActor()) != nullptr)
		Cast<ADistractor>(HitResult.GetActor())->Distract();
}

