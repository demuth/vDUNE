#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Delegates/DelegateInstanceInterface.h"
#include "ObjectViewer.generated.h"


DECLARE_DELEGATE_TwoParams(EndSessionDelegate, class AController *, class ADuneAvatar * const)

UCLASS()
class AObjectViewer : public APawn
{
	GENERATED_BODY()

    /** Camera boom positioning the camera behind the ovservable */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* camera_boom_;

    /** Object Viewer Camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* viewer_camera_;

public:
	/** Sets default values for this pawn's properties */
	AObjectViewer();

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	ADuneAvatar * avatar_;
    EndSessionDelegate delegate_;

public:	
	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	/** Called to bind functionality to input */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void update_spring_arm_location(FVector location, FRotator rotator);
	void set_distance(float distance);

    void try_end_viewer_session();

    void bind_delegate(class AObservableActor* actor, ADuneAvatar* avatar, void (AObservableActor::*fptr)(class AController * controller, class ADuneAvatar * const avatar));
};
