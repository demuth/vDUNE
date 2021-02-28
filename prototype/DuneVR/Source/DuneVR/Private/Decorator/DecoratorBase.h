#pragma once
#include <vector>
#include "CoreMinimal.h"

/**
 * 
 */
class DecoratorBase
{
public:
	DecoratorBase();
	~DecoratorBase();

protected:
    void set_decorator_name(FString new_name);

    template<class T>
    void add_decorator();
	virtual void update(float dt);
	virtual bool is_base();

	FString decorator_name_;
    std::vector<DecoratorBase*> decorator_list_;
};

template<class T>
void DecoratorBase::add_decorator()
{
    decorator_list_.push_back(new T());
}