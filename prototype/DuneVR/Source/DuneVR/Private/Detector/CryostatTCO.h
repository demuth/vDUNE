// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "CryostatTCO.generated.h"


UCLASS()
class ACryostatTCO : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACryostatTCO();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PreInitializeComponents() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TArray<UStaticMesh*> mesh_list_;

	TArray<AStaticMeshActor*> mesh_actors_;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
