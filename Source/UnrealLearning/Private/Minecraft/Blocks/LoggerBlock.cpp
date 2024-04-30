// Copyright Atennop. All Rights Reserved.

#include "Minecraft/Blocks/LoggerBlock.h"

ALoggerBlock::ALoggerBlock() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALoggerBlock::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Interacted using E button");
}
