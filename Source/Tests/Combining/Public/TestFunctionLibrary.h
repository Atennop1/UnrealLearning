// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TestFunctionLibrary.generated.h"

UCLASS()
class COMBINING_API UTestFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Miscellaneous")
	static FString GetMessage();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Math constants", meta=(CompactNodeTitle="π", Tooltip="3.141592..."))
	static double GetPi();
};
