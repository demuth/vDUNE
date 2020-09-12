#include "CryostatTCO.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ACryostatTCO::ACryostatTCO()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>( TEXT("RootComponent") );
    RootComponent = SphereComponent;
    SphereComponent->InitSphereRadius( 40.0f );
}

void ACryostatTCO::PreInitializeComponents()
{
    Super::PreInitializeComponents();

    for( auto mesh : mesh_list_ )
    {
        auto actor = GetWorld()->SpawnActor<AStaticMeshActor>(FVector(), FRotator());
        actor->GetStaticMeshComponent()->SetStaticMesh(mesh);
        actor->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
        mesh_actors_.Add(actor);
    }
}

// Called when the game starts or when spawned
void ACryostatTCO::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACryostatTCO::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

