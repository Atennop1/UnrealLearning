// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PortalTeleportationComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTALS_API UPortalTeleportationComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class APortal *Owner = nullptr;
	
	FVector LastPosition;
	bool LastInFront = false;

	bool IsCrossing(const class APortalCharacter *Character);
	void Teleport(APortalCharacter *Character) const;
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPortalTeleportationComponent();
};
