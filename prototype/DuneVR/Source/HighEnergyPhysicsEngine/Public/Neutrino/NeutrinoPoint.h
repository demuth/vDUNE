#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "vDuneCore/Public/Avatar/Interfaces/Inspectable/Subject.h"
#include "NeutrinoPoint.generated.h"

UCLASS()
class HIGHENERGYPHYSICSENGINE_API ANeutrinoPoint : public ASubject
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
    virtual void PostInitializeComponents() override;

    void set_charge_info(double charge);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mesh, meta = (AllowPrivateAccess = "true"))
    class UMaterialInterface* material_interface_;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mesh, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* point_mesh_;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Charge, meta = (AllowPrivateAccess = "true"))
    float max_charge_;

private:
    void set_color_by_charge(double charge);
    double charge_;
};
