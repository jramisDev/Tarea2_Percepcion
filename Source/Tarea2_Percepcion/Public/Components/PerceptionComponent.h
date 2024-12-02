#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PerceptionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TAREA2_PERCEPCION_API UPerceptionComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UPerceptionComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
