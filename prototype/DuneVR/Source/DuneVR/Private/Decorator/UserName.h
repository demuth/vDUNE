#pragma once

#include "CoreMinimal.h"
#include "Decorator/Decorator.h"

/**
 * 
 */
class UserName : public Decorator
{
public:
	UserName();
	~UserName();

private:
    virtual void update(float dt);
};
