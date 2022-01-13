#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BallState.generated.h"

UCLASS(BlueprintType)
class UBallState : public UObject
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category=Dimensions)
    FVector velocity() const;

	UFUNCTION(BlueprintCallable, Category=Dimensions)
	float distance() const;

	UFUNCTION(BlueprintCallable, Category=Dimensions)
	float time() const;

	void set(FVector velocity, double distance, double time);

protected:
    UPROPERTY(BlueprintReadonly, Category=Dimensions)
    FVector velocity_ = FVector(0);

    UPROPERTY(BlueprintReadonly, Category=Dimensions)
    float total_distance_ = 0.0f;

	UPROPERTY(BlueprintReadonly, Category=Dimensions)
	float t_ = 0.0f;
};
