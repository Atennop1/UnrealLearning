// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterWorldUnloadingComponent.h"
#include "PostProcessingPortal.h"
#include "Templates/FirstPerson/Public/FirstPersonCharacter.h"
#include "PostProcessingCharacter.generated.h"

UCLASS()
class POSTPROCESSING_API APostProcessingCharacter : public AFirstPersonCharacter
{
	GENERATED_BODY()

public:
	APostProcessingCharacter();

	UCharacterWorldUnloadingComponent *GetWorldUnloadingComponent() const { return WorldUnloadingComponent; }

protected:
	virtual void BeginPlay() override;

private:
	friend APostProcessingPortal;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface *CurrentEntryMaterial = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface *CurrentPostProcessMaterial = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UCharacterWorldUnloadingComponent *WorldUnloadingComponent = nullptr;
};
