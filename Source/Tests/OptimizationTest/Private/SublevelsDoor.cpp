// Copyright Atennop. All Rights Reserved.

#include "SublevelsDoor.h"
#include "Kismet/GameplayStatics.h"

ASublevelsDoor::ASublevelsDoor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASublevelsDoor::BeginPlay()
{
	Super::BeginPlay();
	FirstTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASublevelsDoor::OnFirstBeginOverlap);
	SecondTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASublevelsDoor::OnSecondBeginOverlap);
}

void ASublevelsDoor::OnFirstBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsFirstCurrent) UGameplayStatics::LoadStreamLevelBySoftObjectPtr(GetWorld(), FirstSublevel, true, false, FLatentActionInfo());
	else UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(GetWorld(), FirstSublevel, FLatentActionInfo(), false);
	IsFirstCurrent = true;
}

void ASublevelsDoor::OnSecondBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsFirstCurrent) UGameplayStatics::LoadStreamLevelBySoftObjectPtr(GetWorld(), SecondSublevel, true, false, FLatentActionInfo());
	else UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(GetWorld(), SecondSublevel, FLatentActionInfo(), false);
	IsFirstCurrent = false;
}
