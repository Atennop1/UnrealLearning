// Copyright Atennop. All Rights Reserved.

#include "Components/CharacterAuraCastingComponent.h"

UCharacterAuraCastingComponent::UCharacterAuraCastingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterAuraCastingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ADemoEffectsCharacter>(GetOwner());
	check(IsValid(Character))

	UAnimInstance *AnimationInstance = Character->GetMesh()->GetAnimInstance();
	AnimationInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UCharacterAuraCastingComponent::OnMontageNotifyBegin);
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
	if (NotifyName != "Cast")
		return;

	bIsActive = !bIsActive;
	bIsCasting = false;
	Character->SetCanMove(true);      
	
	if (bIsActive)
	{
		const FTransform SpawnTransform = FTransform(FRotator(), Character->GetActorLocation() + AuraSpawnLocation, AuraSpawnSize);
		SpawnedAuraActor = GetWorld()->SpawnActor(AuraClass, &SpawnTransform);
		
		SpawnedAuraActor->AttachToActor(Character, FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false));
		return;
	}
	
	GetWorld()->DestroyActor(SpawnedAuraActor);
}
