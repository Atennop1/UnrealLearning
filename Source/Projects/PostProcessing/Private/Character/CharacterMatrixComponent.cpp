// Copyright Atennop. All Rights Reserved.

#include "Character/CharacterMatrixComponent.h"
#include "Materials/MaterialParameterCollectionInstance.h"

UCharacterMatrixComponent::UCharacterMatrixComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterMatrixComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	MatrixTimeline.TickTimeline(DeltaTime);	
}

void UCharacterMatrixComponent::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat TimelineFloat;
	TimelineFloat.BindUFunction(this, "OnParameterChanged");

	MatrixTimeline = FTimeline();
	MatrixTimeline.AddInterpFloat(MatrixChangingInfo.ChangingCurve, TimelineFloat);
}

void UCharacterMatrixComponent::ChangeMatrix()
{
	bIsLoaded = !bIsLoaded;

	if (!bIsLoaded)
	{
		MatrixTimeline.Play();
		return;
	}

	MatrixTimeline.Reverse();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterMatrixComponent::OnParameterChanged(float Amount) { GetWorld()->GetParameterCollectionInstance(ParameterCollection)->SetScalarParameterValue(MatrixChangingInfo.ParameterName, Amount); }

