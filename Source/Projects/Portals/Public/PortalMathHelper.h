// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PortalMathHelper.generated.h"

UCLASS()
class PORTALS_API UPortalMathHelper : public UObject
{
	GENERATED_BODY()

public:
	static FVector CalculateNewPosition(const FTransform &PortalTransform, const FTransform &OtherPortalTransform, const FVector& OriginalPosition);
	static FRotator CalculateNewRotation(const FTransform &PortalTransform, const FTransform &OtherPortalTransform, const UE::Math::TQuat<double> &OriginalRotation);
};
