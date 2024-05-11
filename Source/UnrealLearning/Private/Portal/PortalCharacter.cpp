// Copyright Atennop. All Rights Reserved.

#include "Portal/PortalCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

APortalCharacter::APortalCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APortalCharacter::OnTimelineTick(float Alpha) const
{
	const auto CharacterController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CharacterController->SetControlRotation(UKismetMathLibrary::RInterpTo(InitialControlRotation, FRotator(InitialControlRotation.Pitch, InitialControlRotation.Yaw, 0), Alpha, 1));
	GetCapsuleComponent()->SetWorldRotation(UKismetMathLibrary::RInterpTo(InitialWorldRotation, FRotator(0, InitialWorldRotation.Yaw, 0), Alpha, 1));
}

void APortalCharacter::BeginPlay()
{
	Super::BeginPlay();
	FOnTimelineFloat Tick;
	FOnTimelineEvent End;
	
	Tick.BindUFunction(this, FName("OnTimelineTick"));
	End.BindUFunction(this, "OnTimelineEnd");
	ReorientingTimeline.AddInterpFloat(ReorientingCurve, Tick);
	ReorientingTimeline.SetTimelineFinishedFunc(End);
}

void APortalCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	ReorientingTimeline.TickTimeline(DeltaSeconds);
}

void APortalCharacter::Reorient()
{
	if (const auto CharacterController = UGameplayStatics::GetPlayerController(GetWorld(), 0); CharacterController->GetControlRotation().Roll != 0.0f || GetCapsuleComponent()->GetComponentRotation().Roll != 0.0f)
	{
		InitialControlRotation = CharacterController->GetControlRotation();
		InitialWorldRotation = GetCapsuleComponent()->GetComponentRotation();
		ReorientingTimeline.PlayFromStart();
	}
}
