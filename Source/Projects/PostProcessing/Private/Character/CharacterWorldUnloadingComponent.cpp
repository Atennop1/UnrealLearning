// Copyright Atennop. All Rights Reserved.

#include "Character/CharacterWorldUnloadingComponent.h"
#include "Materials/MaterialParameterCollectionInstance.h"

UCharacterWorldUnloadingComponent::UCharacterWorldUnloadingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterWorldUnloadingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	WorldUnloadingTimeline.TickTimeline(DeltaTime);	
}

void UCharacterWorldUnloadingComponent::BeginPlay()
{
	Super::BeginPlay();
	WorldUnloadingTimeline = FTimeline();

	auto AddParameterToTimeline = [&](const FName FunctionName, UCurveFloat *Curve)
	{
		FOnTimelineFloat TimelineFloat;
		TimelineFloat.BindUFunction(this, FunctionName);
		WorldUnloadingTimeline.AddInterpFloat(Curve, TimelineFloat);
	};
	
	AddParameterToTimeline("OnUnlitParameterChanged", UnlitChangingInfo.ChangingCurve);
	AddParameterToTimeline("OnGreyParameterChanged", GreyChangingInfo.ChangingCurve);
	AddParameterToTimeline("OnOutlineParameterChanged", OutlineChangingInfo.ChangingCurve);
	AddParameterToTimeline("OnDarknessParameterChanged", DarknessChangingInfo.ChangingCurve);
}

void UCharacterWorldUnloadingComponent::ChangeWorldState()
{
	bIsLoaded = !bIsLoaded;

	if (!bIsLoaded)
	{
		WorldUnloadingTimeline.Play();
		return;
	}

	WorldUnloadingTimeline.Reverse();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterWorldUnloadingComponent::OnUnlitParameterChanged(float Amount) { GetWorld()->GetParameterCollectionInstance(ParameterCollection)->SetScalarParameterValue(UnlitChangingInfo.ParameterName, Amount); }

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterWorldUnloadingComponent::OnGreyParameterChanged(float Amount) { GetWorld()->GetParameterCollectionInstance(ParameterCollection)->SetScalarParameterValue(GreyChangingInfo.ParameterName, Amount); }

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterWorldUnloadingComponent::OnOutlineParameterChanged(float Amount) { GetWorld()->GetParameterCollectionInstance(ParameterCollection)->SetScalarParameterValue(OutlineChangingInfo.ParameterName, Amount); }

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterWorldUnloadingComponent::OnDarknessParameterChanged(float Amount) { GetWorld()->GetParameterCollectionInstance(ParameterCollection)->SetScalarParameterValue(DarknessChangingInfo.ParameterName, Amount); }
