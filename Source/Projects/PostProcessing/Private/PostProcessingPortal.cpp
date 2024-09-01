// Copyright Atennop. All Rights Reserved.

#include "PostProcessingPortal.h"
#include "Character/PostProcessingCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

APostProcessingPortal::APostProcessingPortal()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APostProcessingPortal::BeginPlay()
{
	Super::BeginPlay();
	check(IsValid(TriggerCollider))
	
	check(IsValid(EntryMesh))
	EntryMesh->SetMaterial(0, EntryMaterial);
}

void APostProcessingPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!TriggerCollider->IsOverlappingActor(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		IsOverlapping = false;
		return;
	}
	
	if (!HasCrossedDoor())
		return;

	APostProcessingCharacter *Character = Cast<APostProcessingCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!IsValid(Character))
		return;
	
	EntryMesh->SetMaterial(0, Character->CurrentEntryMaterial);
	std::swap(Character->CurrentEntryMaterial, EntryMaterial);

	FPostProcessSettings PostProcessSettings = FPostProcessSettings();
	PostProcessSettings.WeightedBlendables = TArray { FWeightedBlendable(1, PostProcessMaterial) };
	Character->GetFirstPersonCameraComponent()->PostProcessSettings = PostProcessSettings;
	std::swap(Character->CurrentPostProcessMaterial, PostProcessMaterial);
}

bool APostProcessingPortal::HasCrossedDoor()
{
	const UCameraComponent *PlayerCamera = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetComponentByClass<UCameraComponent>();
	const bool IsInFront = GetActorForwardVector().Dot(PlayerCamera->GetComponentLocation() - GetActorLocation()) >= 0;
	const FPlane Plane = UKismetMathLibrary::MakePlaneFromPointAndNormal(GetActorLocation(), GetActorForwardVector());

	float T = 0.0f;
	FVector Intersection = FVector::Zero();
	const bool IsIntersecting = UKismetMathLibrary::LinePlaneIntersection(PlayerCamera->GetComponentLocation(), LastPosition, Plane, T, Intersection);

	const bool IsCrossing = IsIntersecting && IsOverlapping && (!IsInFront && LastInFront || IsInFront && !LastInFront);
	LastPosition = PlayerCamera->GetComponentLocation();
	LastInFront = IsInFront;
	IsOverlapping = true;

	return IsCrossing;
}

