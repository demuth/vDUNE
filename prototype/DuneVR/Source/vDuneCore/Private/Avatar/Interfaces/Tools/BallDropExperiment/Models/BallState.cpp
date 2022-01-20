#include "BallState.h"

FVector UBallState::velocity() const { return velocity_; }
float UBallState::distance() const { return total_distance_; }
float UBallState::time() const { return t_; }

void UBallState::set(FVector velocity, double distance, double time)
{
    velocity_ = velocity;
    total_distance_ = distance;
    t_ = time;
}
