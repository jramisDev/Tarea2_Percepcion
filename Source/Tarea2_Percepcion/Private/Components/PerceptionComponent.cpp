#include "Components/PerceptionComponent.h"

#include "MovieSceneSequenceID.h"
#include "Components/SphereComponent.h"

UPerceptionComponent::UPerceptionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SphereDetection = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Detection"));
	SphereDetection->SetHiddenInGame(false);
	
	if(PerceptionInfo.DistanceDetection > 0) SphereDetection->SetWorldScale3D(FVector{PerceptionInfo.DistanceDetection});
}

void UPerceptionComponent::BeginPlay()
{
	Super::BeginPlay();

	//SphereDetection->OnComponentBeginOverlap.AddDynamic(this, &UPerceptionComponent::SphereDetectionBeginOverlap);
	//SphereDetection->OnComponentEndOverlap.AddDynamic(this, &UPerceptionComponent::SphereDetectionEndOverlap);

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(TimerHandle_Perception, this, &ThisClass::CheckActorsInDetectionArea, PerceptionInfo.DetectionInterval, true);
	
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Green, TEXT("Hola"));
}

void UPerceptionComponent::CheckActorsInDetectionArea() const
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Red, TEXT("Hola"));
	
	TArray<AActor*> OverlappingActors;
	SphereDetection->GetOverlappingActors(OverlappingActors, AActor::StaticClass());

	
}
