#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Structs/FPerceptionInfo_Struct.h"
#include "PerceptionComponent.generated.h"

class UPerceptionSubsystem;
class USphereComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorPerceptionDetected, AActor*, DetectedActor);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TAREA2_PERCEPCION_API UPerceptionComponent : public USceneComponent
{
    GENERATED_BODY()

    friend UPerceptionSubsystem;

public:
    UPerceptionComponent();

protected:
    virtual void BeginPlay() override;

private:
    FTimerHandle DetectionTimerHandle;

    FPerceptionInfo_Struct PerceptionInfo;
    
    // Lista de actores detectados
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception Info", meta=(AllowPrivateAccess=true))
    TArray<AActor*> DetectedActors;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception Info", meta=(AllowPrivateAccess=true))
    bool bPerceptionActive;

    // Comprueba si hay actores en el radio de detección
    void PerformDetection();

    // Métodos públicos
    UFUNCTION(BlueprintCallable, Category = "Perception Info")
    void ActivatePerception(const bool Active);

public:

    // Delegado para detecciones
    UPROPERTY(BlueprintAssignable, Category = "Perception Info")
    FOnActorPerceptionDetected OnActorPerceptionDetected;

    UFUNCTION(BlueprintCallable, Category = "Perception Settings")
    void SetPerceptionSettings(FPerceptionInfo_Struct InPerceptionInfo);
};
