// Copyright Atennop. All Rights Reserved.

#include "Portal/Portal.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APortal::BeginPlay()
{
	Super::BeginPlay();
	check(Capture && ForwardDirection && Mesh);
	Link(LinkedPortal);
}

void APortal::Setup()
{
	if (PortalMaterial != nullptr && RenderTexture != nullptr)
		return;
	
	PortalMaterial = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), this);
	Mesh->SetMaterial(0, PortalMaterial);
	
	const FVector2D TextureSize = GEngine->GameViewport->Viewport->GetSizeXY();
	RenderTexture = UKismetRenderingLibrary::CreateRenderTarget2D(this, TextureSize.X, TextureSize.Y, RTF_RGBA16f);
}

void APortal::Link(APortal* Portal)
{
	if (Portal == nullptr)
		return;

	Setup();
	Portal->Setup();
	
	LinkedPortal = Portal;
	LinkedPortal->LinkedPortal = this;

	LinkedPortal->PortalMaterial->SetTextureParameterValue("RenderTexture", RenderTexture);
	PortalMaterial->SetTextureParameterValue("RenderTexture", LinkedPortal->RenderTexture);

	LinkedPortal->Capture->TextureTarget = RenderTexture;
	Capture->TextureTarget = LinkedPortal->RenderTexture;
}
