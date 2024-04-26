﻿// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IBlock.generated.h"

UINTERFACE()
class UBlock : public UInterface
{
	GENERATED_BODY()
};

class UNREALLEARNING_API IBlock
{
	GENERATED_BODY()
	
public:
	virtual void Destroy() = 0;
};
