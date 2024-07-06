// Copyright Atennop. All Rights Reserved.

#include "Enemy/GuardPerception.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/GuardCharacter.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Prediction.h"

UGuardPerception::UGuardPerception()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGuardPerception::BeginPlay()
{
	Super::BeginPlay();
	Controller = Cast<AGuardController>(GetOwner());
	
	check(IsValid(Controller));
	OnTargetPerceptionUpdated.AddDynamic(this, &UGuardPerception::OnPerceptionUpdated);
}

void UGuardPerception::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(ChasingTimerHandle);
}

// ReSharper disable once CppMemberFunctionMayBeConst
// ReSharper disable once CppPassValueParameterByConstReference
void UGuardPerception::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	SensedActor = Actor;
	if (!SensedActor->IsA(ABreakerCharacter::StaticClass()))
		return;

	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Prediction>())
	{
		Controller->GetBlackboardComponent()->SetValueAsBool(IsPredictingPlayerVariableName, Stimulus.WasSuccessfullySensed());
		
		if (Stimulus.WasSuccessfullySensed())
			Controller->GetBlackboardComponent()->SetValueAsVector(PredictionLocationVariableName, Stimulus.StimulusLocation);
	}
	
	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
	{
		Controller->GetBlackboardComponent()->SetValueAsBool(IsHearingPlayerVariableName, Stimulus.WasSuccessfullySensed());
		
		if (Stimulus.WasSuccessfullySensed())
			Controller->GetBlackboardComponent()->SetValueAsVector(NoiseLocationVariableName, Stimulus.StimulusLocation);
	}
	
	if (Cast<ABreakerCharacter>(SensedActor)->IsPlayerControlled() && Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
	{
		Controller->GetBlackboardComponent()->SetValueAsBool(CanSeePlayerVariableName, Stimulus.WasSuccessfullySensed());
		
		if (Stimulus.WasSuccessfullySensed())
		{
			GetWorld()->GetTimerManager().ClearTimer(ChasingTimerHandle);
			Controller->GetBlackboardComponent()->SetValueAsObject(TargetVariableName, SensedActor);
			return;
		}
		
		ChasingTimerHandle = FTimerHandle();
		GetWorld()->GetTimerManager().SetTimer(ChasingTimerHandle, [&] { Controller->GetBlackboardComponent()->SetValueAsObject(TargetVariableName, nullptr); }, LoosingTargetTime, false);
		UAISense_Prediction::RequestControllerPredictionEvent(Controller, SensedActor, 1);
	}
}

