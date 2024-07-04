// Copyright Atennop. All Rights Reserved.

#include "Enemy/Components/CharacterAttackingComponent.h"
#include "Enemy/GuardCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Models/Health/HealthComponent.h"

UCharacterAttackingComponent::UCharacterAttackingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterAttackingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AGuardCharacter>(GetOwner());
	check(IsValid(Character))

	UAnimInstance *AnimationInstance = Character->GetMesh()->GetAnimInstance();
	AnimationInstance->OnMontageEnded.AddDynamic(this, &UCharacterAttackingComponent::OnMontageEnded);
		AnimationInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UCharacterAttackingComponent::OnMontageNotifyBegin);
}

void UCharacterAttackingComponent::Attack()
{
	if (IsAttacking)
		return;
	
	UAnimInstance *AnimationInstance = Character->GetMesh()->GetAnimInstance();
	AnimationInstance->Montage_Play(AttackingMontage);
	IsAttacking = true;
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void UCharacterAttackingComponent::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == AttackingMontage)
		IsAttacking = false;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterAttackingComponent::OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	if (NotifyName != SlashNotifyName)
		return;
	
	FHitResult Hit;
	const bool WasHit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Character->GetActorLocation(), Character->GetActorLocation() + Character->GetActorForwardVector() * AttackLength,
		AttackRadius, TArray<TEnumAsByte<EObjectTypeQuery>> { ObjectTypeQuery3 }, false, { Character }, EDrawDebugTrace::None, Hit, true);

	if (WasHit) if (const auto Health = Hit.GetActor()->GetComponentByClass<UHealthComponent>(); Health != nullptr)
		Health->Damage(Damage);
}
