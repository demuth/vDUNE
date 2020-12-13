// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Delegates/DelegateInstanceInterface.h"
#include "ObjectViewer.generated.h"


DECLARE_DELEGATE(EndSessionDelegate)

UCLASS()
class AObjectViewer : public APawn
{
	GENERATED_BODY()

    /** Camera boom positioning the camera behind the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* camera_boom_;

    /** Follow camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* viewer_camera_;

public:
	// Sets default values for this pawn's properties
	AObjectViewer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    EndSessionDelegate delegate_;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void update_spring_arm_location(FVector location, FRotator rotator);
	void set_distance(float distance);

    void try_end_viewer_session();

    void bind_delegate(class AObservableActor * actor, void (AObservableActor::*fptr)());
};
