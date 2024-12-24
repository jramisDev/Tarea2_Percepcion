#include "Subsystems/PerceptionSubsystem.h"

#include "EngineUtils.h"
#include "Components/PerceptionComponent.h"
#include "Engine/World.h"
#include "Tarea2_Percepcion/Tarea2_Percepcion.h"
#include "UObject/ICookInfo.h"

void UPerceptionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Vincular al delegado de inicialización del mundo
	FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UPerceptionSubsystem::OnWorldInitialized);
	//FWorldDelegates::.AddUObject(this, &UPerceptionSubsystem::RegisterActors);	
}

void UPerceptionSubsystem::Deinitialize()
{
	FWorldDelegates::OnPostWorldInitialization.RemoveAll(this);
	Super::Deinitialize();
}

void UPerceptionSubsystem::OnWorldInitialized(UWorld* World, const UWorld::InitializationValues IVS)
{
	if(!World)
	{
		UE_LOG(LogPerceptionSystem, Error, TEXT("UPerceptionSubsystem::OnWorldInitialized - World not loaded"));
		return;
	}

	for(TActorIterator<AActor> It(World->GetWorld()); It; ++It)
	{
		if (It->FindComponentByClass<UPerceptionComponent>())
		{
			RegisterActor(*It);			
		}
	}	
}

void UPerceptionSubsystem::RegisterActor(AActor* InActor)
{
	if(!InActor)
	{
		UE_LOG(LogPerceptionSystem, Error, TEXT("UPerceptionSubsystem::RegisterActor - Actor empty"));
		return;
	}
	
	if (!RegisteredActors.Contains(InActor))
	{
		RegisteredActors.AddUnique(InActor);
	}
}

void UPerceptionSubsystem::UnregisterActor(AActor* InActor)
{
	if(!InActor)
	{
		UE_LOG(LogPerceptionSystem, Error, TEXT("UPerceptionSubsystem::UnregisterActor - Actor empty"));
		return;
	}
	
	RegisteredActors.Remove(InActor);
}

void UPerceptionSubsystem::InitPerceptionInfo(AActor* InActor, const FPerceptionInfo_Struct InPerceptionInfo)
{
	if(!InActor)
	{
		UE_LOG(LogPerceptionSystem, Error, TEXT("UPerceptionSubsystem::InitPerceptionInfo - Actor empty"));
		return;
	}
	
	if (UPerceptionComponent* Component = InActor->FindComponentByClass<UPerceptionComponent>())
	{
		Component->SetPerceptionSettings(InPerceptionInfo);
	}
	else
	{
		UE_LOG(LogPerceptionSystem, Error, TEXT("UPerceptionSubsystem::InitPerceptionInfo - Actor haven't Perception Component"));
	}
}

void UPerceptionSubsystem::SetPerceptionEnabled(TArray<AActor*> ActorsList, const bool bEnable)
{
	for (const AActor* Actor : ActorsList)
	{
		if (UPerceptionComponent* Component = Actor->FindComponentByClass<UPerceptionComponent>())
		{
			Component->ActivatePerception(bEnable);
		}		
	}
}