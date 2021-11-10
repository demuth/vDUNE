#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

enum class BallDropState
{
    Held = 0,
    Released,
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

	TSubclassOf<class UUserWidget> widget() const;
	void set_widget(class UUserWidget* widget);

	void face_camera(FVector camera_location);
	void drop();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category=Configuration, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* mesh_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Configuration)
	TSubclassOf<class UUserWidget> ball_widget_;

	class UWidgetComponent* widget_;

private:
	BallDropState state_;

	/// Current velocity in meters per second,
	double velocity_;
};
