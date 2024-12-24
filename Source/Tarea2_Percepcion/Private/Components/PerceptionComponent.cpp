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
	if(!bPerceptionActive)
	{
		UE_LOG(LogPerceptionSystem, Error, TEXT("UPerceptionComponent::PerformDetection() - Perception System is DISABLED"));
		return;
	}

	//UE_LOG(LogPerceptionSystem, Display, TEXT("UPerceptionComponent::PerformDetection() - Perception Component Detection"));
	
	// Obtener actores en el radio de detección
	TArray<AActor*> OverlappingActors;

	// Esfera de detección
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(GetOwner());
	
	UKismetSystemLibrary::SphereOverlapActors(
		this,
		GetOwner()->GetActorLocation(),
		PerceptionInfo.DistanceDetection,
		ObjectTypes,
		nullptr,
		IgnoredActors,
		OverlappingActors
	);

	DetectedActors.Empty();
	
	// Detectar nuevos actores
	for (AActor* Actor : OverlappingActors)
	{
		if (Actor->FindComponentByClass<UPerceptionComponent>())
		{
			DetectedActors.AddUnique(Actor);
			OnActorPerceptionDetected.Broadcast(Actor);
		}
	}
}

void UPerceptionComponent::ActivatePerception(const bool Active)
{
	if(!GetWorld())
	{
		UE_LOG(LogPerceptionSystem, Error, TEXT("UPerceptionComponent::ActivatePerception - World not loaded"));
		return;
	}

	bPerceptionActive = Active;

	if(Active)
	{
		GetWorld()->GetTimerManager().SetTimer(
			DetectionTimerHandle,
			this,
			&UPerceptionComponent::PerformDetection,
			PerceptionInfo.DetectionInterval,
			true
		);

		UE_LOG(LogPerceptionSystem, Display, TEXT("UPerceptionComponent::ActivatePerception - Perception Component ENABLED"));

	}else {
		GetWorld()->GetTimerManager().ClearTimer(DetectionTimerHandle);
		OnActorPerceptionDetected.Clear();
		
		UE_LOG(LogPerceptionSystem, Display, TEXT("UPerceptionComponent::ActivatePerception - Perception Component DISABLED"));
	}
}

void UPerceptionComponent::SetPerceptionSettings(const FPerceptionInfo_Struct InPerceptionInfo)
{
	PerceptionInfo = InPerceptionInfo;
}