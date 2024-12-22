#pragma once

#include "FPerceptionInfo_Struct.generated.h"

USTRUCT(Blueprintable)
struct FPerceptionInfo_Struct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere) float DistanceDetection = INDEX_NONE;
	UPROPERTY(EditAnywhere) float DetectionInterval = INDEX_NONE;
	UPROPERTY(EditAnywhere) float ForgettingTime = INDEX_NONE;
	
};