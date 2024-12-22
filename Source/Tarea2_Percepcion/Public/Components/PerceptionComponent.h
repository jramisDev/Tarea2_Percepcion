#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Structs/FPerceptionInfo_Struct.h"
#include "PerceptionComponent.generated.h"

class USphereComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TAREA2_PERCEPCION_API UPerceptionComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UPerceptionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Perception Settings", meta=(AllowPrivateAccess))
	FPerceptionInfo_Struct PerceptionInfo;

protected:
	virtual void BeginPlay() override;

	void CheckActorsInDetectionArea() const;

private:
	FTimerHandle TimerHandle_Perception;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<AActor*> ActorsDetected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Perception Settings", meta=(AllowPrivateAccess))
	USphereComponent* SphereDetection;
};
