#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NeutrinoPoint.generated.h"

UCLASS()
class HIGHENERGYPHYSICSENGINE_API ANeutrinoPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANeutrinoPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* mesh_;
};
