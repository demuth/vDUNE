// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../UserBase/UserBase.h"
#include "MenuUser.generated.h"

UENUM(BlueprintType)
enum class EMenu : uint8
{
    Initial = 0
};


UCLASS()
class VDUNECORE_API AMenuUser : public AUserBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMenuUser(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MenuModes, EditFixedSize = "true")
    TMap<EMenu, TSubclassOf<class UAvatarMode>>  available_mode_;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
