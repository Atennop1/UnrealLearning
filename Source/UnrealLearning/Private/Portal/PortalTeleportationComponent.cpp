// Copyright Atennop. All Rights Reserved.

#include "Portal/PortalTeleportationComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Portal/Portal.h"

UPortalTeleportationComponent::UPortalTeleportationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPortalTeleportationComponent::BeginPlay()
{
	Super::BeginPlay();
	
	ForwardDirection = Cast<UArrowComponent>(GetOwner()->GetComponentByClass(UArrowComponent::StaticClass()));
	Owner = Cast<APortal>(GetOwner());
	check(Owner && ForwardDirection);
}

void UPortalTeleportationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*> OverlappingActors;
	Owner->GetOverlappingActors(OverlappingActors, ACharacter::StaticClass());

	if (OverlappingActors.Num() == 0)
		return;

	if (ACharacter *Character = Cast<ACharacter>(OverlappingActors[0]); IsCrossing(Character))
		Teleport(Character);
}

bool UPortalTeleportationComponent::IsCrossing(const ACharacter* Character)
{
	const FVector Point = Character->GetTransform().GetLocation();
	const FVector Normal = ForwardDirection->GetForwardVector();

	float IntersectionT = 0.0f;
	FVector Intersection = FVector::Zero();
	const bool IsInFront = (Point - Owner->GetTransform().GetLocation()).Dot(Normal) >= 0;
	const bool IsIntersect = UKismetMathLibrary::LinePlaneIntersection(LastPosition, Point, UKismetMathLibrary::MakePlaneFromPointAndNormal(Point, Normal), IntersectionT, Intersection);
	const bool IsCrossing = IsIntersect && !IsInFront && LastInFront;

	LastInFront = IsInFront;
	LastPosition = Point;
	return IsCrossing;
}

void UPortalTeleportationComponent::Teleport(ACharacter* Character) const
{
	const FTransform Transform = GetOwner()->GetActorTransform();
	const FVector PortalScale = Transform.GetScale3D();
	const FTransform OtherTransform = Owner->GetLinkedPortal()->GetActorTransform();
	
	const FVector NewPosition = UKismetMathLibrary::TransformLocation(OtherTransform, UKismetMathLibrary::InverseTransformLocation(FTransform(Transform.GetRotation(), Transform.GetLocation(), FVector(-PortalScale.X, -PortalScale.Y, PortalScale.Z)), Character->GetTransform().GetLocation()));
	const FRotator NewRotator = UKismetMathLibrary::MakeRotationFromAxes(
		UKismetMathLibrary::TransformDirection(OtherTransform, UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::InverseTransformDirection(Transform, Character->GetTransform().GetRotation().GetAxisX()), FVector(1, 0, 0)), FVector(0, 1, 0))),
		UKismetMathLibrary::TransformDirection(OtherTransform, UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::InverseTransformDirection(Transform, Character->GetTransform().GetRotation().GetAxisY()), FVector(1, 0, 0)), FVector(0, 1, 0))),
		UKismetMathLibrary::TransformDirection(OtherTransform, UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::InverseTransformDirection(Transform, Character->GetTransform().GetRotation().GetAxisZ()), FVector(1, 0, 0)), FVector(0, 1, 0))));

	AController *Controller = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
	const FRotator NewControlRotator = UKismetMathLibrary::MakeRotationFromAxes(
		UKismetMathLibrary::TransformDirection(OtherTransform, UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::InverseTransformDirection(Transform, Controller->GetControlRotation().Quaternion().GetAxisX()), FVector(1, 0, 0)), FVector(0, 1, 0))),
		UKismetMathLibrary::TransformDirection(OtherTransform, UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::InverseTransformDirection(Transform, Controller->GetControlRotation().Quaternion().GetAxisY()), FVector(1, 0, 0)), FVector(0, 1, 0))),
		UKismetMathLibrary::TransformDirection(OtherTransform, UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::InverseTransformDirection(Transform, Controller->GetControlRotation().Quaternion().GetAxisZ()), FVector(1, 0, 0)), FVector(0, 1, 0))));

	Character->SetActorTransform(FTransform(NewRotator, NewPosition, FVector::One()));
	Controller->SetControlRotation(NewControlRotator);
}
