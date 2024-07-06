// Copyright Atennop. All Rights Reserved.

#include "Breaker/Other/CharacterDistractingComponent.h"
#include "Camera/CameraComponent.h"
#include "Enemy/GuardCharacter.h"
#include "Environment/Distractor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UCharacterDistractingComponent::UCharacterDistractingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterDistractingComponent::Distract()
{
	if (!IsValid(CurrentDistractor))
		return;
	
	if (CurrentDistractor->GetCanDistract())
		CurrentDistractor->Distract();

	if (!CurrentDistractor->GetCanDistract())
		ClearDistractor();
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

	const bool WasHit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Camera->GetComponentLocation(), Camera->GetComponentLocation() + Camera->GetForwardVector() * 100000, CheckingSphereRadius,
		TArray<TEnumAsByte<EObjectTypeQuery>> { ObjectTypeQuery8 }, false, { }, EDrawDebugTrace::None, HitResult, true);

	const bool IsThereDistractor = WasHit && Cast<ADistractor>(HitResult.GetActor()) != nullptr;
	ADistractor *Distractor = IsThereDistractor ? Cast<ADistractor>(HitResult.GetActor()) : nullptr;
	
	const bool IsDistractorVisible = IsThereDistractor && GetWorld()->LineTraceSingleByChannel(HitResult, Camera->GetComponentLocation(), Distractor->GetActorLocation(),
		ECC_Visibility, { }) && HitResult.GetActor() == Distractor;
		
	if (!IsDistractorVisible && CurrentDistractor != nullptr)
		ClearDistractor();
	
	if (IsDistractorVisible && CurrentDistractor != Distractor && Distractor->GetCanDistract() && UKismetMathLibrary::Vector_Distance(Character->GetActorLocation(), Distractor->GetActorLocation()) <= MaximumDistance)
		SetDistractor(Distractor);
}

void UCharacterDistractingComponent::ClearDistractor()
{
	if (const auto Mesh = CurrentDistractor->GetComponentByClass<UStaticMeshComponent>(); IsValid(Mesh))
	{
		Mesh->SetRenderCustomDepth(false);
		Mesh->SetCustomDepthStencilValue(0);
	}
	
	CurrentDistractor = nullptr;
}

void UCharacterDistractingComponent::SetDistractor(ADistractor* NewDistractor)
{
	CurrentDistractor = NewDistractor;
		
	if (const auto Mesh = CurrentDistractor->GetComponentByClass<UStaticMeshComponent>(); IsValid(Mesh))
	{
		Mesh->SetRenderCustomDepth(true);
		Mesh->SetCustomDepthStencilValue(1);
	}
}

