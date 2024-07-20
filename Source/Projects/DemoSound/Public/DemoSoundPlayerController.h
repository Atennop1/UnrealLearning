// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GuardAI/Public/Breaker/BreakerPlayerController.h"
#include "DemoSoundPlayerController.generated.h"

UCLASS()
class DEMOSOUND_API ADemoSoundPlayerController : public ABreakerPlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
