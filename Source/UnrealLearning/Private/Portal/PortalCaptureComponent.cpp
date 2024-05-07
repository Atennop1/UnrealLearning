// Copyright Atennop. All Rights Reserved.

#include "../../Public/Portal/PortalCaptureComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Portal/Portal.h"

UPortalCaptureComponent::UPortalCaptureComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPortalCaptureComponent::BeginPlay()
{
	Super::BeginPlay();

	ForwardDirection = Cast<UArrowComponent>(GetOwner()->GetComponentByClass(UArrowComponent::StaticClass()));
	Capture = Cast<USceneCaptureComponent2D>(GetOwner()->GetComponentByClass(USceneCaptureComponent2D::StaticClass()));
	Owner = Cast<APortal>(GetOwner());
	check(Owner && Capture && ForwardDirection);
	
	Capture->bEnableClipPlane = true;
	Capture->ClipPlaneNormal = ForwardDirection->GetForwardVector();
	Capture->ClipPlaneBase = ForwardDirection->GetComponentLocation() + ForwardDirection->GetForwardVector() * -3;
}

void UPortalCaptureComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Owner->GetLinkedPortal() == nullptr)
		return;

	if (const FVector2D ViewportSize = GEngine->GameViewport->Viewport->GetSizeXY(); Capture->TextureTarget != nullptr && (Capture->TextureTarget->SizeX != ViewportSize.X || Capture->TextureTarget->SizeY != ViewportSize.Y))
		Capture->TextureTarget->ResizeTarget(ViewportSize.X, ViewportSize.Y);
	
	const FTransform Transform = GetOwner()->GetActorTransform();
	const FVector PortalScale = Transform.GetScale3D();
	const FTransform OtherTransform = Owner->GetLinkedPortal()->GetActorTransform();
	const FTransform CameraTransform = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransform();
	
	const FVector NewPosition = UKismetMathLibrary::TransformLocation(OtherTransform, UKismetMathLibrary::InverseTransformLocation(FTransform(Transform.GetRotation(), Transform.GetLocation(), FVector(-PortalScale.X, -PortalScale.Y, PortalScale.Z)), CameraTransform.GetLocation()));
	const FVector NewRotationVectorX = UKismetMathLibrary::TransformDirection(OtherTransform, UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::InverseTransformDirection(Transform, CameraTransform.GetRotation().GetAxisX()), FVector(1, 0, 0)), FVector(0, 1,0)));
	const FVector NewRotationVectorY = UKismetMathLibrary::TransformDirection(OtherTransform, UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::InverseTransformDirection(Transform, CameraTransform.GetRotation().GetAxisY()), FVector(1, 0, 0)), FVector(0, 1,0)));
	const FVector NewRotationVectorZ = UKismetMathLibrary::TransformDirection(OtherTransform, UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::InverseTransformDirection(Transform, CameraTransform.GetRotation().GetAxisZ()), FVector(1, 0, 0)), FVector(0, 1,0)));
	const FRotator NewRotation = UKismetMathLibrary::MakeRotationFromAxes(NewRotationVectorX, NewRotationVectorY, NewRotationVectorZ);
	
	Owner->GetLinkedPortal()->GetCapture()->SetWorldLocationAndRotation(NewPosition, NewRotation);
}
