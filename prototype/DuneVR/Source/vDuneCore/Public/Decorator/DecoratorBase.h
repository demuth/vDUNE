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
    virtual bool is_base();

    void construct(class USceneComponent* rootComponent);
    void setup(class ADuneController* controller, TSubclassOf<class UUserWidget> widget_subclass_);
	virtual void update(float dt);
	void teardown();

	FString decorator_name_;
	class UWidgetComponent* widget_;
    std::vector<DecoratorBase*> decorator_list_;
};

template<class T>
void DecoratorBase::add_decorator()
{
    decorator_list_.push_back(new T());
}