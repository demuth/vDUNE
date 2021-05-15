#include "Instance/vDuneInstance.h"
#include "Blueprint/UserWidget.h"

UvDuneInstance::UvDuneInstance()
{

}

UvDuneInstance::~UvDuneInstance()
{

}

void UvDuneInstance::Init()
{
    UE_LOG(LogClass, Log, TEXT("*** Instance Init ***"));
    set_state(ApplicationState::Initial);
}


void UvDuneInstance::Shutdown()
{
    UE_LOG(LogClass, Log, TEXT("*** Instance Shutdown ***"));
}

void UvDuneInstance::set_state(ApplicationState new_state)
{
    if (state_ != new_state)
        handle_state(new_state);
}

// handles changes in the application state.
void UvDuneInstance::handle_state(ApplicationState new_state)
{
    switch(new_state)
    {
        case ApplicationState::Initial: on_initial_state(); break;
        case ApplicationState::Active: on_active_state(); break;
    }
}

void UvDuneInstance::on_initial_state()
{
    UE_LOG(LogClass, Log, TEXT("~~~ Initial State ~~~"));

//    for(FConstPawnIterator Iterator = GetWorld()->GetPawnIterator(); Iterator; ++Iterator)
//    {
//        UE_LOG(LogClass, Log, TEXT("Pawn found."));
//    }
}

void UvDuneInstance::on_active_state()
{

}