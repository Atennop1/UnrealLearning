// Copyright Atennop. All Rights Reserved.

#include "AmbientZone.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Character.h"

AAmbientZone::AAmbientZone()
{
	PrimaryActorTick.bCanEverTick = false;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
}

void AAmbientZone::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AAmbientZone::OnTriggerBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AAmbientZone::OnTriggerEndOverlap);
}

void AAmbientZone::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (!IsValid(Cast<ACharacter>(OtherActor)))
		return;

	Ambient->GetAudioComponent()->SetTriggerParameter(TriggerName);
}

void AAmbientZone::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if (!IsValid(Cast<ACharacter>(OtherActor)))
		return;

	TArray<AActor*> OverlappingActors;
	OtherActor->GetOverlappingActors(OverlappingActors);

	for (const auto Actor : OverlappingActors)
		if (IsValid(Cast<AAmbientZone>(Actor)))
			return;

	Ambient->GetAudioComponent()->SetTriggerParameter(NoneName);
}
