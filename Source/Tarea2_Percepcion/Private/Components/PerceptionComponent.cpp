#include "Components/PerceptionComponent.h"

UPerceptionComponent::UPerceptionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPerceptionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPerceptionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

