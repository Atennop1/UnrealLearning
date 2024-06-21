// Copyright Atennop. All Rights Reserved.

#include "PortalMathHelper.h"
#include "Kismet/KismetMathLibrary.h"

FVector UPortalMathHelper::CalculateNewPosition(const FTransform& PortalTransform, const FTransform& OtherPortalTransform, const FVector& OriginalPosition)
{
	const FVector PortalScale = PortalTransform.GetScale3D();
	return UKismetMathLibrary::TransformLocation(OtherPortalTransform, UKismetMathLibrary::InverseTransformLocation(FTransform(PortalTransform.GetRotation(), PortalTransform.GetLocation(), FVector(-PortalScale.X, -PortalScale.Y, PortalScale.Z)), OriginalPosition));
}

FRotator UPortalMathHelper::CalculateNewRotation(const FTransform& PortalTransform, const FTransform& OtherPortalTransform, const UE::Math::TQuat<double>& OriginalRotation)
{
	return UKismetMathLibrary::MakeRotationFromAxes(
		UKismetMathLibrary::TransformDirection(OtherPortalTransform, UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::InverseTransformDirection(PortalTransform, OriginalRotation.GetAxisX()), FVector(1, 0, 0)), FVector(0, 1, 0))),
		UKismetMathLibrary::TransformDirection(OtherPortalTransform, UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::InverseTransformDirection(PortalTransform, OriginalRotation.GetAxisY()), FVector(1, 0, 0)), FVector(0, 1, 0))),
		UKismetMathLibrary::TransformDirection(OtherPortalTransform, UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::MirrorVectorByNormal(UKismetMathLibrary::InverseTransformDirection(PortalTransform, OriginalRotation.GetAxisZ()), FVector(1, 0, 0)), FVector(0, 1, 0))));
}
