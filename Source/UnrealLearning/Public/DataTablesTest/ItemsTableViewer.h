// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "ItemsTableViewer.generated.h"

UCLASS()
class UNREALLEARNING_API AItemsTableViewer : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly)
	UDataTable *Table;

protected:
	virtual void BeginPlay() override;

public:
	AItemsTableViewer();
};
