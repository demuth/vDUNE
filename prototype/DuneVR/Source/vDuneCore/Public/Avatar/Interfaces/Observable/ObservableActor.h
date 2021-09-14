#pragma once

#include "CoreMinimal.h"
#include "../PalpableActor.h"
#include "ObservableActor.generated.h"


UCLASS()
class AObservableActor : public APalpableActor
{
	GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category=Viewer, meta = (AllowPrivateAccess = "true"))
	class AObjectViewer * viewer_;

    UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* mesh_;

    UPROPERTY(EditAnywhere, BlueprintReadonly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
    FRotator viewer_rotation_;

    UPROPERTY(EditAnywhere, BlueprintReadonly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
    float viewer_start_distance_ = 80.0f;

public:	
	// Sets default values for this actor's properties
	AObservableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    virtual bool actor_interaction_viable(const ADuneAvatar * const avatar) const override;

    virtual void interact(class ADuneAvatar * const avatar, class UViableInteraction * interaction, bool &is_active) override;

    void fun(class AController * controller, class ADuneAvatar * const avatar);
};
