// Copyright Atennop. All Rights Reserved.

#include "Models/SoundPlayer.h"
#include "Kismet/GameplayStatics.h"

ASoundPlayer::ASoundPlayer()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASoundPlayer::BeginPlay()
{
	Super::BeginPlay();
	check(IsValid(Collision))
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASoundPlayer::OnCollisionBeginOverlap);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ASoundPlayer::OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::PlaySound2D(GetWorld(), SoundToPlay);
}
