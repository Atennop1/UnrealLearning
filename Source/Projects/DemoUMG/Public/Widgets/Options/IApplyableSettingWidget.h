// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IApplyableSettingWidget.generated.h"

UINTERFACE()
class UAppliableSettingWidget : public UInterface
{
	GENERATED_BODY()
};

class DEMOUMG_API IAppliableSettingWidget
{
	GENERATED_BODY()

public:
	virtual void Apply() = 0;
};
