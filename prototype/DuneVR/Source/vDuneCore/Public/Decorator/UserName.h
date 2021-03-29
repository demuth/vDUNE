#pragma once

#include "CoreMinimal.h"
#include "vDuneCore/Public/Decorator/Decorator.h"

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
