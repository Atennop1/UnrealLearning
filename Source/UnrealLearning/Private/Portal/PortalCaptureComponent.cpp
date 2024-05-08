// Copyright Atennop. All Rights Reserved.

#include "../../Public/Portal/PortalCaptureComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/GameplayStatics.h"
#include "Portal/Portal.h"
#include "Portal/PortalMathHelper.h"

UPortalCaptureComponent::UPortalCaptureComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPortalCaptureComponent::BeginPlay()
{
	Super::BeginPlay();

	ForwardDirection = Cast<UArrowComponent>(GetOwner()->GetComponentByClass(UArrowComponent::StaticClass()));
	Capture = Cast<USceneCaptureComponent2D>(GetOwner()->GetComponentByClass(USceneCaptureComponent2D::StaticClass()));
	PortalMesh = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	Owner = Cast<APortal>(GetOwner());
	check(Owner && Capture && ForwardDirection && PortalMesh);
	
	Capture->bEnableClipPlane = true;
	Capture->ClipPlaneNormal = ForwardDirection->GetForwardVector();
	Capture->ClipPlaneBase = PortalMesh->GetComponentLocation() + ForwardDirection->GetForwardVector() * -3;
}

void UPortalCaptureComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Owner->GetLinkedPortal() == nullptr)
		return;

	if (const FVector2D ViewportSize = GEngine->GameViewport->Viewport->GetSizeXY(); Capture->TextureTarget != nullptr && (Capture->TextureTarget->SizeX != ViewportSize.X || Capture->TextureTarget->SizeY != ViewportSize.Y))
		Capture->TextureTarget->ResizeTarget(ViewportSize.X, ViewportSize.Y);
	
	const FTransform Transform = Owner->GetActorTransform();
	const FTransform OtherTransform = Owner->GetLinkedPortal()->GetActorTransform();
	const FTransform CameraTransform = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentTransform();
	
	const FVector NewPosition = UPortalMathHelper::CalculateNewPosition(Transform, OtherTransform, CameraTransform.GetLocation());
	const FRotator NewRotation = UPortalMathHelper::CalculateNewRotation(Transform, OtherTransform, CameraTransform.GetRotation());
	Owner->GetLinkedPortal()->GetCapture()->SetWorldLocationAndRotation(NewPosition, NewRotation);
}
