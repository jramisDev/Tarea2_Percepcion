#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Structs/FPerceptionInfo_Struct.h"
#include "PerceptionComponent.generated.h"

class USphereComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorPerceptionDetected, AActor*, DetectedActor);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TAREA2_PERCEPCION_API UPerceptionComponent : public USceneComponent
{
    GENERATED_BODY()

public:
    UPerceptionComponent();

protected:
    virtual void BeginPlay() override;

private:
    FTimerHandle DetectionTimerHandle;

    // Lista de actores detectados
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception Info", meta=(AllowPrivateAccess=true))
    TSet<AActor*> DetectedActors;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception Info", meta=(AllowPrivateAccess=true))
    bool PerceptionActive;

    // Comprueba si hay actores en el radio de detección
    void PerformDetection();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception Settings")
    FPerceptionInfo_Struct PerceptionInfo;

    // Delegado para detecciones
    UPROPERTY(BlueprintAssignable, Category = "Perception Info")
    FOnActorPerceptionDetected OnActorPerceptionDetected;

    // Métodos públicos
    UFUNCTION(BlueprintCallable, Category = "Perception Info")
    void ActivatePerception(const bool Active);
};
