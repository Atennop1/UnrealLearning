// Copyright Atennop. All Rights Reserved.

#include "NetworkGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

void ANetworkGameMode::Respawn(AController *Controller) const
{
	if (IsValid(Controller->GetPawn()))
		Controller->GetWorld()->DestroyActor(Controller->GetPawn());
	
	TArray<AActor*> SpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(Controller->GetWorld(), APlayerStart::StaticClass(), SpawnPoints);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	const FTransform SpawnTransform = SpawnPoints[FMath::RandRange(0, SpawnPoints.Num() - 1)]->GetTransform();

	ANetworkCharacter *NewCharacter = Cast<ANetworkCharacter>(Controller->GetWorld()->SpawnActor(CharacterClass, &SpawnTransform, SpawnParameters));
	Controller->Possess(NewCharacter);
}
