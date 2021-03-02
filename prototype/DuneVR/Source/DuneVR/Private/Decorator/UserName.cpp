#include "Decorator/UserName.h"

UserName::UserName()
{
    DecoratorBase::set_decorator_name("UserName");
}

UserName::~UserName()
{
    Decorator::~Decorator();
}

void UserName::update(float dt)
{
    Decorator::update(dt);
}
