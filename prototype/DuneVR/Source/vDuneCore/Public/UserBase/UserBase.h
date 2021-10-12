// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Avatar/Interfaces/Modes/AvatarMode.h"
#include "../Avatar/DuneController.h"
#include "UserBase.generated.h"

UCLASS()
class VDUNECORE_API AUserBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUserBase(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mode, meta = (AllowPrivateAccess = "true"))
    class UAvatarMode * mode_;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void set_user_mode(TSubclassOf<UAvatarMode>* type);

    UFUNCTION(BlueprintCallable, Category=ModeLogic)
    class UAvatarMode* get_user_mode() const;
};
