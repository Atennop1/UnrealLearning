﻿// Copyright Atennop. All Rights Reserved.

#include "DataTablesTest/ItemsTableViewer.h"
#include "DataTablesTest/ItemData.h"

AItemsTableViewer::AItemsTableViewer()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AItemsTableViewer::BeginPlay()
{
	Super::BeginPlay();

	TArray<FItemData*> Rows;
	Table->GetAllRows("DataTableViewerContext", Rows);
	
	for (const auto Row : Rows)
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, Row->Name + ": " + Row->Description);
}

