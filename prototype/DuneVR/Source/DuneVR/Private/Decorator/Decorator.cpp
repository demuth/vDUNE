#include "Decorator/Decorator.h"

Decorator::Decorator()
{
}

Decorator::~Decorator()
{
}

bool Decorator::is_base() { return false; }

void Decorator::update(float dt)
{
    UE_LOG(LogClass, Log, TEXT("Updating the decorator: %s"), *decorator_name_);
}