// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	virtual void update(float dt);
};
