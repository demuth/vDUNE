#include "vDuneCore/Public/Decorator/DecoratorBase.h"
#include "vDuneCore/Public/Decorator/Decorator.h"
#include "vDuneCore/Public/Avatar/DuneController.h"
#include "Components/WidgetComponent.h"
#include "Components/SceneComponent.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"

DecoratorBase::DecoratorBase()
: decorator_name_("unnamed decorator")
{
    UE_LOG(LogTemp, Log, TEXT("Constructing a decorator base."));
    decorator_list_.push_back(this);
}

DecoratorBase::~DecoratorBase()
{
    UE_LOG(LogTemp, Log, TEXT("Deconstructing a decorator: %s"), *decorator_name_);
    for(auto &decorator : decorator_list_)
    {
        // update non-base decorators
        if (!decorator->is_base()) delete decorator;
    }

    decorator_list_.clear();
}

void DecoratorBase::set_decorator_name(FString new_name)
{
    decorator_name_ = new_name;
}

bool DecoratorBase::is_base() { return true; }

void DecoratorBase::construct(USceneComponent* rootComponent)
{
    widget_ = NewObject<UWidgetComponent>();
    widget_->SetupAttachment(rootComponent);
}

void DecoratorBase::setup(ADuneController *controller, TSubclassOf<UUserWidget> widget_subclass_)
{
    if (controller == nullptr)
        return;

    auto w = controller->new_widget(widget_subclass_);
    widget_->SetWidget(w);
    widget_->SetDrawSize(FVector2D(50.0f));
    widget_->SetTwoSided(true);
    widget_->SetRelativeLocation(FVector(50.0f, 0.0f, 50.0f));
}

void DecoratorBase::update(float dt)
{
    UE_LOG(LogClass, Log, TEXT("Updating the decorator: %s"), *decorator_name_);
    for(auto &decorator : decorator_list_)
    {
        // update non-base decorators
        if (!decorator->is_base()) decorator->update(dt);
    }
}

void DecoratorBase::teardown()
{

}