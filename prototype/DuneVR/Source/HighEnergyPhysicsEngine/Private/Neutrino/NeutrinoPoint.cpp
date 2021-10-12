#include "Neutrino/NeutrinoPoint.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Math/Color.h"
#include <vector>

int get_category(float decimal_value);
std::vector<float> get_rgb(int category);

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
    this->set_color_by_charge(charge);
}

void ANeutrinoPoint::set_color_by_charge(double charge)
{
    UE_LOG(LogClass, Error, TEXT("setting color for charge: %f"), charge);
    // if the charge is less than zero, the parameter is invalid.
    if (charge < 0) return;
    // if the mesh is null, no color can be assigned.
    if (!point_mesh_) return;

    // normalize charge
    float spectrum_position;
    spectrum_position = charge / max_charge_;
    UE_LOG(LogClass, Error, TEXT("Charge: %f Max Charge: %f"), charge, max_charge_);

    auto category = get_category(spectrum_position);

    // Generate a set of rgb values.
    auto rgb = get_rgb(category);

    // Try to create a material.  Skip application if the material construction fails.
    UMaterialInstanceDynamic *material = UMaterialInstanceDynamic::Create(material_interface_, this);
    if (!material) return;

    // Apply the generated color to the material.
    material->SetVectorParameterValue("BaseColor", FLinearColor(rgb[0], rgb[1], rgb[2], 1.0f));
    point_mesh_->SetMaterial(0, material);
}

int get_category(float decimal_value)
{
    if (decimal_value < 0.1) return 1;
    else if (decimal_value < 0.2) return 2;
    else if (decimal_value < 0.3) return 3;
    else if (decimal_value < 0.4) return 4;
    else if (decimal_value < 0.5) return 5;
    else if (decimal_value < 0.6) return 6;
    else if (decimal_value < 0.7) return 7;
    else if (decimal_value < 0.8) return 8;
    else if (decimal_value < 0.9) return 9;
    else return 10;
}

std::vector<float> get_rgb(int category)
{
    switch(category)
    {
        case 0: return {1.0f, 0.0f, 0.0f};
        case 1: return {1.0f, 0.3f, 0.0f};
        case 2: return {1.0f, 0.6f, 0.0f};
        case 3: return {1.0f, 0.9f, 0.0f};
        case 4: return {1.9f, 1.0f, 0.0f};
        case 5: return {0.6f, 1.0f, 0.0f};
        case 6: return {0.3f, 1.0f, 0.0f};
        case 7: return {0.0f, 1.0f, 0.0f};
        case 8: return {0.0f, 1.0f, 0.3f};
        case 9: return {0.0f, 1.0f, 0.6f};
        case 10: return {0.0f, 1.0f, 0.9f};
        default: return {0.0f, 0.0f, 1.0f};
    }
}