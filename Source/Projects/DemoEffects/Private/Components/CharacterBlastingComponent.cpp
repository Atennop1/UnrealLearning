// Copyright Atennop. All Rights Reserved.

#include "Components/CharacterBlastingComponent.h"
#include "Components/CharacterAuraCastingComponent.h"
#include "Kismet/KismetMathLibrary.h"

UCharacterBlastingComponent::UCharacterBlastingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterBlastingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ADemoEffectsCharacter>(GetOwner());
	check(IsValid(Character))

	UAnimInstance *AnimationInstance = Character->GetMesh()->GetAnimInstance();
	AnimationInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UCharacterBlastingComponent::OnMontageNotifyBegin);
}

void UCharacterBlastingComponent::Blast()
{
	if (bIsBlasting  || Character->GetAuraCastingComponent()->GetIsCasting())
		return;

	bIsBlasting = true;
	Character->SetCanMove(false);
	
	UAnimInstance *AnimationInstance = Character->GetMesh()->GetAnimInstance();
	AnimationInstance->Montage_Play(BlastingMontage); 
}

void UCharacterBlastingComponent::OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	if (NotifyName == "AllowMove")
	{
		Character->SetCanMove(true);
		return;
	}
	
	if (NotifyName != "Blast")
		return;

	const FVector SpawnLocation = UKismetMathLibrary::Quat_RotateVector(Character->GetActorRotation().Quaternion(), BlastSpawnLocation) + Character->GetActorLocation();
	const FRotator SpawnRotation = Character->GetActorRotation();
	AActor *BlastActor = GetWorld()->SpawnActor(BlastClass, &SpawnLocation, &SpawnRotation);

	BlastActor->SetLifeSpan(40);
	bIsBlasting = false;
}
