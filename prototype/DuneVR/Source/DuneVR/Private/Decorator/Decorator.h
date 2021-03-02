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

protected:
    virtual void update(float dt);

private:
    bool is_base();
};
