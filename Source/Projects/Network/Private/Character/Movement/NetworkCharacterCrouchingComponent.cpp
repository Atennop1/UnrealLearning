// Copyright Atennop. All Rights Reserved.

#include "Character/Movement/NetworkCharacterCrouchingComponent.h"
#include "Character/NetworkCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"

UNetworkCharacterCrouchingComponent::UNetworkCharacterCrouchingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void UNetworkCharacterCrouchingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ANetworkCharacter>(GetOwner());
	check(Character != nullptr)
	
	FOnTimelineFloat OnTimelineUpdate;
	OnTimelineUpdate.BindUFunction(this, "CrouchUpdate");
	CrouchingTimeline.AddInterpFloat(CrouchingCurve, OnTimelineUpdate);
	NormalHalfHeight = Character->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
}

void UNetworkCharacterCrouchingComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UNetworkCharacterCrouchingComponent, IsCrouching);
}

void UNetworkCharacterCrouchingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CrouchingTimeline.TickTimeline(DeltaTime);
}

void UNetworkCharacterCrouchingComponent::CrouchUpdate(float Alpha) const
{
	const float HalfHeight = FMath::Lerp(NormalHalfHeight, CrouchedHalfHeight, Alpha);
	Character->GetCapsuleComponent()->SetCapsuleHalfHeight(HalfHeight);
	Character->GetMesh()->SetRelativeLocation(FVector(0, 0, -HalfHeight));
}

void UNetworkCharacterCrouchingComponent::MulticastCrouchUpdate_Implementation(bool NewIsCrouching)
{
	IsCrouching = NewIsCrouching;
	
	if (IsCrouching)
	{
		CrouchingTimeline.Play();
		return;
	}
	
	CrouchingTimeline.Reverse();
}
