// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PostProcessingPortal.h"
#include "Templates/FirstPerson/Public/FirstPersonCharacter.h"
#include "PostProcessingCharacter.generated.h"

UCLASS()
class POSTPROCESSING_API APostProcessingCharacter : public AFirstPersonCharacter
{
	GENERATED_BODY()

public:
	APostProcessingCharacter();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UMaterialInterface *CurrentPostProcessMaterial = nullptr;
	
	UPROPERTY(EditAnywhere)
	UMaterialInterface *CurrentEntryMaterial = nullptr;

	friend APostProcessingPortal;
};
