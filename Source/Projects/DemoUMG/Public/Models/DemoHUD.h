// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Widgets/HealthWidget.h"
#include "DemoHUD.generated.h"

UCLASS()
class DEMOUMG_API ADemoHUD : public AHUD
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHealthWidget> HealthWidgetClass;

	UPROPERTY()
	TObjectPtr<UHealthWidget> HealthWidget;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
