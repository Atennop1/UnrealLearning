// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PostProcessingPortal.generated.h"

UCLASS()
class POSTPROCESSING_API APostProcessingPortal : public AActor
{
	GENERATED_BODY()

public:
	APostProcessingPortal();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UBoxComponent *TriggerCollider = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UStaticMeshComponent *EntryMesh = nullptr;

	UPROPERTY(EditInstanceOnly)
	UMaterial *EntryMaterial = nullptr;

	UPROPERTY(EditInstanceOnly)
	UMaterial *PostProcessMaterial = nullptr;
	
	FVector LastPosition = FVector();
	bool LastInFront = false;
	bool IsOverlapping = false;
	
	bool HasCrossedDoor();
};
