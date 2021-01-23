#include "Neutrino/NeutrinoPoint.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Math/Color.h"

// Sets default values
ANeutrinoPoint::ANeutrinoPoint()
{
	PrimaryActorTick.bCanEverTick = true;

    mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("pickup_mesh"));
    RootComponent = mesh_;
}

void ANeutrinoPoint::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    UMaterialInstanceDynamic* material = UMaterialInstanceDynamic::Create(material_interface_, this);
    material->SetVectorParameterValue("BaseColor", FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
    mesh_->SetMaterial(0, material);
}

// Called when the game starts or when spawned
void ANeutrinoPoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ANeutrinoPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

