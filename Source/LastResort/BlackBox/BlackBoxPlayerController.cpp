// Copyright (c) 2015 Mateus Bezerra

#include "LastResort.h"
#include "BlackBoxPlayerController.h"

ABlackBoxPlayerController::ABlackBoxPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	this -> bShowMouseCursor = true;
	this -> bEnableClickEvents = true;
	this -> bEnableTouchEvents = true;
	this -> DefaultMouseCursor = EMouseCursor::Crosshairs;
}
