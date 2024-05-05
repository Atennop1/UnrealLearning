// Copyright Atennop. All Rights Reserved.

#include "Portal/Portal.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Kismet/KismetStringLibrary.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	PortalMesh->SetupAttachment(RootComponent);

	CaptureComponent = CreateDefaultSubobject<UPortalCaptureComponent>(TEXT("PortalCaptureComponent"));
	Capture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Capture"));
	Capture->SetupAttachment(RootComponent);
}

void APortal::Link(APortal* Portal)
{
	if (Portal == nullptr)
		return;

	Setup();
	Portal->Setup();
	
	LinkedPortal = Portal;
	Portal->LinkedPortal = this;

	LinkedPortal->PortalMaterial->SetTextureParameterValue("RenderTexture", RenderTexture);
	PortalMaterial->SetTextureParameterValue("RenderTexture", LinkedPortal->RenderTexture);

	LinkedPortal->Capture->TextureTarget = RenderTexture;
	Capture->TextureTarget = LinkedPortal->RenderTexture;
}

void APortal::Setup()
{
	if (PortalMaterial != nullptr && RenderTexture != nullptr)
		return;
	
	PortalMaterial = UMaterialInstanceDynamic::Create(PortalMesh->GetMaterial(0), this);
	PortalMesh->SetMaterial(0, PortalMaterial);
	
	const FVector2D TextureSize = GEngine->GameViewport->Viewport->GetSizeXY();
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, UKismetStringLibrary::Conv_Vector2dToString(TextureSize));
	RenderTexture = UKismetRenderingLibrary::CreateRenderTarget2D(this, TextureSize.X, TextureSize.Y, RTF_RGBA16f);
}

void APortal::BeginPlay()
{
	Super::BeginPlay();
	Link(LinkedPortal);
}
