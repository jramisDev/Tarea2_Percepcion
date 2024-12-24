#include "Components/PerceptionComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Tarea2_Percepcion/Tarea2_Percepcion.h"

UPerceptionComponent::UPerceptionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPerceptionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	ActivatePerception(true);	
}

void UPerceptionComponent::PerformDetection()
{
	if(!PerceptionActive)
	{
		UE_LOG(LogPerceptionSystem, Error, TEXT("Perception System is DISABLED"));
		return;
	}

	UE_LOG(LogPerceptionSystem, Display, TEXT("Perception Component Detection"));
	
	// Obtener actores en el radio de detección
	TArray<AActor*> OverlappingActors;
	FVector OwnerLocation = GetOwner()->GetActorLocation();

	// Esfera de detección
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(GetOwner());
	
	UKismetSystemLibrary::SphereOverlapActors(
		this,
		OwnerLocation,
		PerceptionInfo.DistanceDetection,
		ObjectTypes,
		nullptr,
		IgnoredActors,
		OverlappingActors
	);

	// Detectar nuevos actores
	for (AActor* Actor : OverlappingActors)
	{
		if (Actor->FindComponentByClass<UPerceptionComponent>())
		{
			DetectedActors.Add(Actor);
			OnActorPerceptionDetected.Broadcast(Actor);
		}
	}
}

void UPerceptionComponent::ActivatePerception(const bool Active)
{
	if(!GetWorld()) return;

	PerceptionActive = Active;

	if(Active)
	{
		GetWorld()->GetTimerManager().SetTimer(
			DetectionTimerHandle,
			this,
			&UPerceptionComponent::PerformDetection,
			PerceptionInfo.DetectionInterval,
			true
		);

		UE_LOG(LogPerceptionSystem, Display, TEXT("Perception Component ENABLED"));

	}else {
		GetWorld()->GetTimerManager().ClearTimer(DetectionTimerHandle);
		OnActorPerceptionDetected.Clear();
		
		UE_LOG(LogPerceptionSystem, Display, TEXT("Perception Component DISABLED"));
	}
}