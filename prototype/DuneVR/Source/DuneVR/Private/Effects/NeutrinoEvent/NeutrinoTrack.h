#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NeutrinoEventStruct.h"
#include "NeutrinoTrack.generated.h"

UCLASS()
class ANeutrinoTrack : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ANeutrinoTrack();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    void add_bounds(FVector location, FVector size);
    void add_points(TArray<FNeutrinoPointData> points);

private:
    TArray<class USphereComponent*> component_list_;
    USphereComponent* sphere_;
};
