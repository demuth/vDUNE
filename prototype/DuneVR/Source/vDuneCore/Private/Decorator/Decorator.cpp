#include "vDuneCore/Public/Decorator/Decorator.h"

Decorator::Decorator()
{
}

Decorator::~Decorator()
{
    DecoratorBase::~DecoratorBase();
}

bool Decorator::is_base() { return false; }

void Decorator::update(float dt)
{
    UE_LOG(LogClass, Log, TEXT("Updating the decorator: %s"), *decorator_name_);
}