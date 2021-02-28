#pragma once

#include "CoreMinimal.h"
#include "DecoratorBase.h"

/**
 * 
 */
class Decorator : public DecoratorBase
{
public:
	Decorator();
	~Decorator();

private:
    virtual void update(float dt);
    virtual bool is_base();
};
