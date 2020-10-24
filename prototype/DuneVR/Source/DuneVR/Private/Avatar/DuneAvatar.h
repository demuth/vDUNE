// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Tools/AvatarTool.h"
#include "Tools/EAvatarTool.h"
#include "Modes/EAvatarMode.h"
#include "DuneAvatar.generated.h"



UCLASS(config=Game)
class ADuneAvatar : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

    /** Collection Sphere */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pickup, meta = (AllowPrivateAccess = "true"))
    class USphereComponent* collection_sphere_;

    /** Inventory */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
    TArray<class UPickupModel *>  collectibles_;

    /** Interaction objects */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
    TMap<FString, class UViableInteraction *>  viable_interactions_;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mode, meta = (AllowPrivateAccess = "true"))
    class UAvatarMode * mode_;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tools, EditFixedSize = "true")
    TMap<EAvatarTool, TSubclassOf<UAvatarTool>>  available_tool_;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tools, EditFixedSize = "true")
    TMap<EAvatarMode, TSubclassOf<UAvatarMode>>  available_mode_;

public:
	ADuneAvatar();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:
    virtual void Tick(float delta_seconds) override;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	UFUNCTION(BlueprintCallable, Category=Pickup)
	void detect_viable_interactions();

    UFUNCTION(BlueprintCallable, Category=Pickup)
    void update_viable_interactions();

	UFUNCTION(BlueprintCallable, Category=Inventory)
	TArray<class UPickupModel*> get_collectibles() const;

    UFUNCTION(BlueprintCallable, Category=Interfaces)
    TMap<FString, class UViableInteraction *> get_viable_interactions() const;

    UFUNCTION(BlueprintCallable, Category=Mode)
    void use_tool(EAvatarTool tool);



public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
    FORCEINLINE class USphereComponent* GetCollectionSphere() const { return collection_sphere_; }
    FORCEINLINE const class UAvatarMode* GetAvatarMode() const { return mode_; }


    bool add_collectible(class UPickupModel * collectible_data);

    void try_interaction();

    void set_inspect_mode();
    void set_measure_mode();
    void place_measure_marker();

    UFUNCTION(BlueprintCallable, Category=Mode)
    void set_mode(EAvatarMode mode);
};



