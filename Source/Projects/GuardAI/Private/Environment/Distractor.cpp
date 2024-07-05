// Copyright Atennop. All Rights Reserved.

#include "Environment/Distractor.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Hearing.h"

ADistractor::ADistractor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADistractor::Distract()
{
	if (!CanDistract)
		return;
	
	CanDistract = false;
	UAISense_Hearing::ReportNoiseEvent(GetWorld(), DistractPositions[FMath::RandRange(0, DistractPositions.Num() - 1)]->GetActorLocation(),
		Loudness, UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (IsValid(DistractSound))
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DistractSound, GetActorLocation());
}