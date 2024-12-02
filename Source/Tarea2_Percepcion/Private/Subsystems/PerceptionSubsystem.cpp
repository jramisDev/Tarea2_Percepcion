#include "Tarea2_Percepcion/Public/Subsystems/PerceptionSubsystem.h"

void UPerceptionSubsystem::RegisterPerceptionComponent(UPerceptionComponent* Component)
{
	if (!RegisteredComponents.Contains(Component))
	{
		RegisteredComponents.Add(Component);
	}
}

void UPerceptionSubsystem::UnregisterPerceptionComponent(UPerceptionComponent* Component)
{
	RegisteredComponents.Remove(Component);
}

void UPerceptionSubsystem::NotifyActorDetected(AActor* DetectedActor)
{
	OnGlobalActorDetected.Broadcast(DetectedActor);
}

void UPerceptionSubsystem::GetRegisteredComponents(TArray<UPerceptionComponent*>& RegisteredComponents)
{
}
