#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

enum class BallState
{
    HeldAboveGround = 0,
    FreeFall,
    Unknown
};

UCLASS()
class ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor * OtherActor) override;
	virtual void NotifyHit
	(class UPrimitiveComponent * MyComp, AActor * Other, class UPrimitiveComponent * OtherComp, bool bSelfMoved,
	        FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit) override;

	TSubclassOf<class UUserWidget> widget() const;
	void set_widget(class UUserWidget* widget);

	void face_camera(FVector camera_location);
	void drop();

	TArray<class UBallState*> states() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category=Configuration, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* mesh_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Configuration)
	TSubclassOf<class UUserWidget> ball_widget_;

	class UWidgetComponent* widget_;


	void add_state(FVector velocity, double distance, double time);

private:
    BallState state_;

    TArray<class UBallState*> array_;

	/// Current velocity in meters per second,
	double velocity_;
	double total_time_in_free_fall_;
	double total_distance_in_free_fall_;
};
