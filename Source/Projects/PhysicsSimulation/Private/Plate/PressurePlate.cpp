// Copyright Atennop. All Rights Reserved.

#include "Plate/PressurePlate.h"
#include "Kismet/KismetMathLibrary.h"
#include "Plate/Presser.h"

APressurePlate::APressurePlate()
{
	PrimaryActorTick.bCanEverTick = true;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	Frame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame"));
}

void APressurePlate::BeginPlay()
{
	Super::BeginPlay();
	Activatable.SetObject(ActivatableActor);
	Activatable.SetInterface(Cast<IActivatable>(ActivatableActor));
	
	Frame->AttachToComponent(Trigger, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false));
    Button->AttachToComponent(Trigger, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false));
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnTriggerBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::OnTriggerEndOverlap);

	FOnTimelineFloat OnTimelineFloat;
	OnTimelineFloat.BindUFunction(this, "OnActivatingTimelineUpdate");
	ActivatingTimeline.AddInterpFloat(ActivatingCurve, OnTimelineFloat);
}

void APressurePlate::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	ActivatingTimeline.TickTimeline(DeltaSeconds);
}

void APressurePlate::OnActivatingTimelineUpdate(float Alpha) const
{
	Button->SetRelativeLocation(UKismetMathLibrary::VLerp(DeactivatedButtonRelativePosition, ActivatedButtonRelativePosition, Alpha));
}

// ReSharper disable once CppMemberFunctionMayBeConst
// ReSharper disable once CppParameterMayBeConstPtrOrRef
void APressurePlate::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UPresser>())
		return;

	PressersCount++;
	ActivatingTimeline.Play();
	Frame->SetMaterial(0, ActivatedMaterial);
	
	if (Activatable != nullptr && PressersCount == 1)
		Activatable->Activate();
}

// ReSharper disable once CppMemberFunctionMayBeConst
// ReSharper disable once CppParameterMayBeConstPtrOrRef
void APressurePlate::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor->Implements<UPresser>())
		return;
	
	PressersCount--;
	ActivatingTimeline.Reverse();
	Frame->SetMaterial(0, DeactivatedMaterial);
	
	if (Activatable != nullptr && PressersCount == 0)
		Activatable->Deactivate();
}
