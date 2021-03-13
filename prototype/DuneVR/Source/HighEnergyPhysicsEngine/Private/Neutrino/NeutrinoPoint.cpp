#include "Neutrino/NeutrinoPoint.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Math/Color.h"

// Sets default values
ANeutrinoPoint::ANeutrinoPoint()
: ASubject()
, max_charge_(5000.0f)
, charge_(-1)
{
    point_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("point_mesh"));
    RootComponent = point_mesh_;
}

void ANeutrinoPoint::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    this->set_color_by_charge(charge_);
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

void ANeutrinoPoint::set_charge_info(double charge)
{
    charge_ = charge;
    UE_LOG(LogClass, Error, TEXT("Charge set: %f "), charge);
    this->set_color_by_charge(charge_);
}

void ANeutrinoPoint::set_color_by_charge(double charge)
{
    UE_LOG(LogClass, Error, TEXT("setting color"));
    // if the charge is less than zero, the parameter is invalid.
    if (charge < 0) return;
    // if the mesh is null, no color can be assigned.
    if (!mesh_) return;

    // normalize charge
    float spectrum_position;
    spectrum_position = charge / max_charge_;
    UE_LOG(LogClass, Error, TEXT("Charge: %f Max Charge: %f"), charge, max_charge_);

    // Try to create a material.  If it fails don't try to apply it.
    UMaterialInstanceDynamic *material = UMaterialInstanceDynamic::Create(material_interface_, this);
    if (!material) return;

    material->SetVectorParameterValue("BaseColor", FLinearColor(spectrum_position, spectrum_position, spectrum_position, 1.0f));
    mesh_->SetMaterial(0, material);
}