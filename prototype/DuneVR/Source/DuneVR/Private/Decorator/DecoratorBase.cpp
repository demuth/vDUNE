#include "Decorator/DecoratorBase.h"
#include "Decorator/Decorator.h"

DecoratorBase::DecoratorBase()
: decorator_name_("unnamed decorator")
{
    UE_LOG(LogTemp, Log, TEXT("Constructing a decorator base."));
    decorator_list_.push_back(this);
}

DecoratorBase::~DecoratorBase()
{
    UE_LOG(LogTemp, Log, TEXT("Deconstructing a decorator base. %d"), decorator_list_.size());
}

void DecoratorBase::set_decorator_name(FString new_name)
{
    decorator_name_ = new_name;
}

bool DecoratorBase::is_base() { return true; }

void DecoratorBase::update(float dt)
{
    UE_LOG(LogClass, Log, TEXT("Updating the decorator: %s"), *decorator_name_);
    for(auto &decorator : decorator_list_)
    {
        // update non-base decorators
        if (!decorator->is_base()) decorator->update(dt);
    }
}