// Copyright Atennop. All Rights Reserved.

#include "Character/PhysicsCharacterGrabbingComponent.h"
#include "Camera/CameraComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

UPhysicsCharacterGrabbingComponent::UPhysicsCharacterGrabbingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPhysicsCharacterGrabbingComponent::Grab(const FInputActionValue& Value)
{
	if (bIsGrabbing)
	{
		PhysicsHandle->ReleaseComponent();
		bIsGrabbing = false;
		return;
	}
	
	FHitResult Hit;
	const FVector StartLocation = Character->GetFirstPersonCameraComponent()->GetComponentLocation();
	const FVector EndLocation = StartLocation + Character->GetFirstPersonCameraComponent()->GetForwardVector() * 250;

	if (const bool WasHit = GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility, FCollisionQueryParams()); !WasHit || !Hit.Component->IsSimulatingPhysics())
		return;

	bIsGrabbing = true;
	PhysicsHandle->GrabComponentAtLocationWithRotation(&*Hit.Component, NAME_None, Hit.Component->GetComponentLocation(), Hit.Component->GetComponentRotation());
}

void UPhysicsCharacterGrabbingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<APhysicsCharacter>(GetOwner());
	check(IsValid(Character))
	check(IsValid(PhysicsHandle))
}

void UPhysicsCharacterGrabbingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	PhysicsHandle->SetTargetLocation(Character->GetFirstPersonCameraComponent()->GetComponentLocation() + Character->GetFirstPersonCameraComponent()->GetForwardVector() * 200);
}
