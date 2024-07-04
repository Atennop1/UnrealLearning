// Copyright Atennop. All Rights Reserved.

#include "Environment/Distractor.h"
#include "Perception/AISense_Hearing.h"

ADistractor::ADistractor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADistractor::Distract() const
{
	UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), Loudness);
}

