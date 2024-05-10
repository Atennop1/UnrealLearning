﻿// Copyright Atennop. All Rights Reserved.

#include "Portal/PortalTeleportationComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Portal/Portal.h"
#include "Portal/PortalMathHelper.h"

UPortalTeleportationComponent::UPortalTeleportationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPortalTeleportationComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<APortal>(GetOwner());
	check(Owner);
}

void UPortalTeleportationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*> OverlappingActors;
	Owner->GetOverlappingActors(OverlappingActors, ACharacter::StaticClass());

	if (OverlappingActors.Num() == 0)
		return;

	if (ACharacter *Character = Cast<ACharacter>(OverlappingActors[0]); IsCrossing(Character))
		Teleport(Character);
}

bool UPortalTeleportationComponent::IsCrossing(const ACharacter* Character)
{
	const FVector Point = Character->GetTransform().GetLocation();
	const FVector Normal = Owner->GetForwardDirection();

	float IntersectionT = 0.0f;
	FVector Intersection = FVector::Zero();
	const bool IsInFront = (Point - Owner->GetTransform().GetLocation()).Dot(Normal) >= 0;
	const bool IsIntersect = UKismetMathLibrary::LinePlaneIntersection(LastPosition, Point, UKismetMathLibrary::MakePlaneFromPointAndNormal(Point, Normal), IntersectionT, Intersection);
	const bool IsCrossing = IsIntersect && !IsInFront && LastInFront;

	LastInFront = IsInFront;
	LastPosition = Point;
	return IsCrossing;
}

void UPortalTeleportationComponent::Teleport(ACharacter* Character) const
{
	const FTransform Transform = Owner->GetActorTransform();
	const FTransform OtherTransform = Owner->GetLinkedPortal()->GetActorTransform();
	
	const FVector NewPosition = UPortalMathHelper::CalculateNewPosition(Transform, OtherTransform, Character->GetTransform().GetLocation());
	const FRotator NewRotator = UPortalMathHelper::CalculateNewRotation(Transform, OtherTransform, Character->GetTransform().GetRotation());
	Character->SetActorLocationAndRotation(NewPosition, NewRotator);
	
	AController *Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	const FRotator NewControlRotator = UPortalMathHelper::CalculateNewRotation(Transform, OtherTransform, Controller->GetControlRotation().Quaternion());
	Controller->SetControlRotation(NewControlRotator);

	UPawnMovementComponent *CharacterMovement = Character->GetMovementComponent();
	CharacterMovement->Velocity = CharacterMovement->Velocity.Size() * UKismetMathLibrary::TransformDirection(OtherTransform, UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::InverseTransformDirection(Transform, CharacterMovement->Velocity.GetSafeNormal()), FVector(1, 0, 0)), FVector(0, 1, 0)));
}
