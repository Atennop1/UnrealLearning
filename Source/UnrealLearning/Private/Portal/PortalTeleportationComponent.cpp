// Copyright Atennop. All Rights Reserved.

#include "Portal/PortalTeleportationComponent.h"
#include "Portal/Portal.h"

UPortalTeleportationComponent::UPortalTeleportationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPortalTeleportationComponent::BeginPlay()
{
	Super::BeginPlay();
	check(Cast<APortal>(GetOwner()));
	Owner = Cast<APortal>(GetOwner());
}

void UPortalTeleportationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

