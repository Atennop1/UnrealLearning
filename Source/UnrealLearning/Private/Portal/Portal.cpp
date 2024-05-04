// Copyright Atennop. All Rights Reserved.

#include "Portal/Portal.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetRenderingLibrary.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetupAttachment(RootComponent);

	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	PortalMesh->SetupAttachment(Root);
	
	Capture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Capture"));
	Capture->SetupAttachment(Root);
}

void APortal::Link(APortal* Portal)
{
	if (Portal == nullptr)
		return;

	Portal->Setup();
	OtherPortal = Portal;
	Portal->OtherPortal = this;

	OtherPortal->PortalMaterial->SetTextureParameterValue("Texture", RenderTexture);
	PortalMaterial->SetTextureParameterValue("Texture", OtherPortal->RenderTexture);

	OtherPortal->Capture->TextureTarget = RenderTexture;
	Capture->TextureTarget = OtherPortal->RenderTexture;
}

void APortal::Setup()
{
	if (PortalMaterial != nullptr && RenderTexture != nullptr)
		return;
	
	PortalMaterial = UMaterialInstanceDynamic::Create(PortalMesh->GetMaterial(0), this);
	PortalMesh->SetMaterial(0, PortalMaterial);
	
	const FVector2D TextureSize = GEngine->GameViewport->Viewport->GetSizeXY();
	RenderTexture = UKismetRenderingLibrary::CreateRenderTarget2D(this, TextureSize.X, TextureSize.Y, RTF_RGBA16f);
}

void APortal::BeginPlay()
{
	Super::BeginPlay();
	SetTickGroup(TG_PostUpdateWork);
	
	Setup();
	Link(OtherPortal);
}

void APortal::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (OtherPortal == nullptr)
		return;
	
	const FTransform Transform = GetActorTransform();
	const FVector PortalScale = Transform.GetScale3D();
	const FTransform OtherTransform = OtherPortal->GetActorTransform();
	const FTransform CameraTransform = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorTransform();
	
	const FVector NewPosition = UKismetMathLibrary::TransformLocation(OtherTransform, UKismetMathLibrary::InverseTransformLocation(FTransform(Transform.GetRotation(), Transform.GetLocation(), FVector(-PortalScale.X, -PortalScale.Y, PortalScale.Z)), CameraTransform.GetLocation()));
	const FVector NewRotationVectorX = UKismetMathLibrary::TransformDirection(OtherTransform, UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::InverseTransformDirection(Transform, FVector(CameraTransform.GetRotation().X)), FVector(1, 0, 0)), FVector(0, 1,0)));
	const FVector NewRotationVectorY = UKismetMathLibrary::TransformDirection(OtherTransform, UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::InverseTransformDirection(Transform, FVector(CameraTransform.GetRotation().Y)), FVector(1, 0, 0)), FVector(0, 1,0)));
	const FVector NewRotationVectorZ = UKismetMathLibrary::TransformDirection(OtherTransform, UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::InverseTransformDirection(Transform, FVector(CameraTransform.GetRotation().Z)), FVector(1, 0, 0)), FVector(0, 1,0)));
	const FRotator NewRotation = UKismetMathLibrary::MakeRotationFromAxes(NewRotationVectorX, NewRotationVectorY, NewRotationVectorZ);
	
	OtherPortal->GetCamera()->SetWorldLocationAndRotation(NewPosition, NewRotation);
}
