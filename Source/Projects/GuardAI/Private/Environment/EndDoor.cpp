// Copyright Atennop. All Rights Reserved.

#include "Environment/EndDoor.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/GuardCharacter.h"
#include "Kismet/GameplayStatics.h"

AEndDoor::AEndDoor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEndDoor::BeginPlay()
{
	Super::BeginPlay();
	check(IsValid(DoorMesh))

	FOnTimelineFloat OnTimelineUpdated;
	OnTimelineUpdated.BindUFunction(this, "OnTimelineUpdated");
	
	OpeningTimeline = FTimeline();
	OpeningTimeline.AddInterpFloat(Curve, OnTimelineUpdated);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AEndDoor::OnTimelineUpdated(float Alpha)
{
	DoorMesh->SetRelativeRotation(FRotator(0, FMath::Lerp(ClosedRotationZ, OpenedRotationZ, Alpha), 0));
}

void AEndDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OpeningTimeline.TickTimeline(DeltaTime);

	TArray<AActor*> EnemyActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGuardCharacter::StaticClass(), EnemyActors);

	for (const auto EnemyActor : EnemyActors)
	{
		AAIController *EnemyController = Cast<AAIController>(Cast<AGuardCharacter>(EnemyActor)->GetController());
		const UBlackboardComponent *Blackboard = EnemyController->GetBlackboardComponent();

		if (Blackboard->GetValueAsBool("IsPredicting") || Blackboard->GetValueAsObject("TargetActor") != nullptr)
		{
			OpeningTimeline.Reverse();
			return;
		}
	}
	
	OpeningTimeline.Play();
}

