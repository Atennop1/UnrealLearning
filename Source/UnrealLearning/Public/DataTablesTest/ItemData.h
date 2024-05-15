// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Description;
};
