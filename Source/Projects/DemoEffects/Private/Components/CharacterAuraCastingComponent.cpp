// Copyright Atennop. All Rights Reserved.

#include "Components/CharacterAuraCastingComponent.h"

UCharacterAuraCastingComponent::UCharacterAuraCastingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterAuraCastingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ADemoEffectsCharacter>(GetOwner());
	check(IsValid(Character))

	UAnimInstance *AnimationInstance = Character->GetMesh()->GetAnimInstance();
	AnimationInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UCharacterAuraCastingComponent::OnMontageNotifyBegin);

	FOnTimelineFloat OnTimelineFloat;
	OnTimelineFloat.BindUFunction(this, "OnTimelineUpdated");
	AuraAppearingTimeline.AddInterpFloat(AuraAppearingCurve, OnTimelineFloat);
}

void UCharacterAuraCastingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AuraAppearingTimeline.TickTimeline(DeltaTime);
}

void UCharacterAuraCastingComponent::CastAura()
{
	if (bIsCasting)
		return;

	bIsCasting = true;           
	Character->SetCanMove(false);
	
	UAnimInstance *AnimationInstance = Character->GetMesh()->GetAnimInstance();
	AnimationInstance->Montage_Play(AuraCastingMontage); 
}

void UCharacterAuraCastingComponent::OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	if (NotifyName == "AllowMove")
	{
		Character->SetCanMove(true);
		return;
	}
	
	if (NotifyName != "CastAura")
		return;

	bIsActive = !bIsActive;
	bIsCasting = false;
	
	if (!bIsActive)
	{
		AuraAppearingTimeline.Reverse();
		return;
	}
	
	const FVector SpawnLocation = Character->GetActorLocation() + AuraSpawnLocation;
	SpawnedAuraActor = GetWorld()->SpawnActor(AuraClass, &SpawnLocation);
		
	SpawnedAuraActor->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::KeepWorldTransform);
	AuraAppearingTimeline.Play();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterAuraCastingComponent::OnTimelineUpdated(float Alpha)
{
	if (IsValid(SpawnedAuraActor))
		SpawnedAuraActor->SetActorScale3D(AuraSpawnSize * Alpha);

	if (Alpha == 0)
		GetWorld()->DestroyActor(SpawnedAuraActor);
}
