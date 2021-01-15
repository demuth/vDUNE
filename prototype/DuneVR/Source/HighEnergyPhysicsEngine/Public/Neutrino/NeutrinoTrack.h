#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "../../Private/Neutrino/NeutrinoEventStruct.h"
#include "NeutrinoTrack.generated.h"

UCLASS()
class HIGHENERGYPHYSICSENGINE_API ANeutrinoTrack : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ANeutrinoTrack();
    void add_bounds(FVector location, FVector size);
    void add_points(TArray<FNeutrinoPointData> points);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mesh)
    UStaticMesh* point_mesh_;

private:
    TArray<class USphereComponent*> component_list_;
    TArray<class UStaticMeshComponent*> mesh_;
};
