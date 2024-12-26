#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PerceptionSubsystem.generated.h"

struct FPerceptionInfo_Struct;
class UPerceptionComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActorDetectedPerception, AActor*, Detector, AActor*, Detected);

UCLASS()
class TAREA2_PERCEPCION_API UPerceptionSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	
	// Inicialización del subsistema
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	// Configurar los parámetros de percepción
	UFUNCTION(BlueprintCallable, Category = "Perception Subsystem")
	void InitPerceptionInfo(AActor* InActor, FPerceptionInfo_Struct InPerceptionInfo);

	// Activar/Desactivar percepción
	UFUNCTION(BlueprintCallable, Category = "Perception Subsystem")
	void SetPerceptionEnabled(TArray<AActor*> ActorsList, const bool bEnable);

	UPROPERTY(BlueprintAssignable, Category = "Perception Subsystem")
	FOnActorDetectedPerception OnActorDetectedPerception;
	
	//UPROPERTY(BlueprintAssignable, Category = "Perception Subsystem")
	FDelegateHandle OnActorSpawnedDelegateHandle;

private:
	
	UPROPERTY()
	TArray<AActor*> RegisteredActors;

	// Registrar y desregistrar componentes
	void RegisterActor(AActor* InActor);
	void UnregisterActor(AActor* InActor);
	void RegisterNewActor(AActor* Actor);

	// Callback de inicialización del mundo
	void OnWorldInitialized(UWorld* World, const UWorld::InitializationValues IVS);
};
