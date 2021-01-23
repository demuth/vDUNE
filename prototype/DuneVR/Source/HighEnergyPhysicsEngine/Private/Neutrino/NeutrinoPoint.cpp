#include "Neutrino/NeutrinoPoint.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Math/Color.h"

// Sets default values
ANeutrinoPoint::ANeutrinoPoint()
: max_charge_(5000.0f)
, charge_(-1)
{
	PrimaryActorTick.bCanEverTick = true;

    mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("pickup_mesh"));
    RootComponent = mesh_;
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
}

void ANeutrinoPoint::set_color_by_charge(double charge)
{
    // if the charge is less than zero, the parameter is invalid.
    if (charge < 0) return;

    // normalize charge
    float spectrum_position = charge / max_charge_;

    UMaterialInstanceDynamic* material = UMaterialInstanceDynamic::Create(material_interface_, this);
    material->SetVectorParameterValue("BaseColor", FLinearColor(spectrum_position, spectrum_position, spectrum_position, 1.0f));
    mesh_->SetMaterial(0, material);
}

