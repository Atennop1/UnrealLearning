// Copyright Atennop. All Rights Reserved.

#include "Minecraft/DefaultBlock.h"

ADefaultBlock::ADefaultBlock()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADefaultBlock::Destroy()
{
	GetWorld()->DestroyActor(this);
}

