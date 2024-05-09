// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PortalTeleportationComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALLEARNING_API UPortalTeleportationComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class APortal *Owner;
	
	FVector LastPosition;
	bool LastInFront;

	bool IsCrossing(const ACharacter *Character);
	void Teleport(ACharacter *Character) const;
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPortalTeleportationComponent();
};
