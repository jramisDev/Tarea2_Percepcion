#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PerceptionSubsystem.generated.h"

class UPerceptionComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorDetected, AActor*, DetectedActor);

UCLASS()
class TAREA2_PERCEPCION_API UPerceptionSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void RegisterPerceptionComponent(UPerceptionComponent* Component);

	UFUNCTION(BlueprintCallable)
	void UnregisterPerceptionComponent(UPerceptionComponent* Component);
	
	UFUNCTION(BlueprintCallable)
	void NotifyActorDetected(AActor* DetectedActor);

	// UFUNCTION(BlueprintPure)
	// void GetRegisteredComponents(TArray<UPerceptionComponent*> &RegisteredComponents);

protected:
	// Lista de componentes registrados
	TArray<UPerceptionComponent*> RegisteredComponents;

	// Delegado global para detecciones
	UPROPERTY(BlueprintAssignable, Category = "Perception")
	FOnActorDetected OnGlobalActorDetected;
};
