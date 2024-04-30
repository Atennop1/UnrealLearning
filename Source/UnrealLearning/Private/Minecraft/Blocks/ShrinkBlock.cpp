// Copyright Atennop. All Rights Reserved.

#include "Minecraft/Blocks/ShrinkBlock.h"

AShrinkBlock::AShrinkBlock() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShrinkBlock::Interact()
{
	const FTransform Transform = GetMesh()->GetComponentTransform();
	GetMesh()->SetWorldTransform(FTransform(Transform.GetRotation(), Transform.GetTranslation(), Transform.GetScale3D() * (IsDecreasing ? 0.5f : 2.f)));
	AmountOfShrinks += IsDecreasing ? -1 : 1;
	
	if (AmountOfShrinks == 0 || AmountOfShrinks == 3)
		IsDecreasing = !IsDecreasing;
}

