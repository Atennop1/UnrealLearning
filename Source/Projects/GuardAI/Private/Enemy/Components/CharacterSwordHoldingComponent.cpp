// Copyright Atennop. All Rights Reserved.

#include "Enemy/Components/CharacterSwordHoldingComponent.h"
#include "Enemy/GuardCharacter.h"

UCharacterSwordHoldingComponent::UCharacterSwordHoldingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterSwordHoldingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AGuardCharacter>(GetOwner());
	check(IsValid(Character))

	UAnimInstance *AnimationInstance = Character->GetMesh()->GetAnimInstance();
	AnimationInstance->OnMontageEnded.AddDynamic(this, &UCharacterSwordHoldingComponent::OnMontageEnded);
	AnimationInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UCharacterSwordHoldingComponent::OnMontageNotifyBegin);
}

void UCharacterSwordHoldingComponent::Sheath()
{
	if (IsSheathing || SpawnedSword == nullptr)
		return;
	
	UAnimInstance *AnimationInstance = Character->GetMesh()->GetAnimInstance();
	AnimationInstance->Montage_Play(SheathingMontage);
	IsSheathing = true;
}

void UCharacterSwordHoldingComponent::Withdraw()
{
	if (IsWithdrawing || SpawnedSword != nullptr)
		return;
	
	UAnimInstance *AnimationInstance = Character->GetMesh()->GetAnimInstance();
	AnimationInstance->Montage_Play(WithdrawingMontage);
	IsWithdrawing = true;
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void UCharacterSwordHoldingComponent::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == SheathingMontage)
		IsSheathing = false;

	if (Montage == WithdrawingMontage)
		IsWithdrawing = false;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterSwordHoldingComponent::OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	if (NotifyName == SpawnSwordNotifyName)
	{
		SpawnedSword = GetWorld()->SpawnActor(SwordClass);
		SpawnedSword->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), SwordSocketName);
	}

	if (NotifyName == DestroySwordNotifyName)
	{
		GetWorld()->DestroyActor(SpawnedSword);
		SpawnedSword = nullptr;
	}
}

