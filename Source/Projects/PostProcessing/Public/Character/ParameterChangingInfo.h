// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ParameterChangingInfo.generated.h"

USTRUCT()
struct FParameterChangingInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FName ParameterName;
	
	UPROPERTY(EditDefaultsOnly)
	UCurveFloat *ChangingCurve;
};