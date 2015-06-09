// Copyright (c) 2015 Mateus Bezerra

#include "LastResort.h"
#include "BlackBoxGameMode.h"
#include "BlackBox/BlackBoxPlayerController.h"

ABlackBoxGameMode::ABlackBoxGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
	this -> DefaultPawnClass = NULL;
	this -> PlayerControllerClass = ABlackBoxPlayerController::StaticClass();
}
