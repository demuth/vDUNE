// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorator/DecoratorBase.h"

DecoratorBase::DecoratorBase()
{
}

DecoratorBase::~DecoratorBase()
{
}

void DecoratorBase::update(float dt)
{
    UE_LOG(LogTemp, Log, TEXT("Updating the decorator base."));
}