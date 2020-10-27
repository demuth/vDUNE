// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Subject.generated.h"

UCLASS()
class ASubject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASubject();

    FString get_name();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SubjectData)
    FString name_;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SubjectData)
    FString details_;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* mesh_;
};
