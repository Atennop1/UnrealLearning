// Copyright Atennop. All Rights Reserved.

#include "Enemy/Patrolling/PatrollingPath.h"

APatrollingPath::APatrollingPath()
{
	PrimaryActorTick.bCanEverTick = false;
}

APatrolPoint* APatrollingPath::GetNextPatrolPoint()
{
	CurrentPointIndex++;

	if (CurrentPointIndex == Points.Num())
		CurrentPointIndex = 0;

	return Points[CurrentPointIndex];
}
