// Copyright (c) 2015 Mateus Bezerra

#include "LastResort.h"
#include "TopCamera.h"
#include "BlackBoxPlayerController.h"

ABlackBoxPlayerController::ABlackBoxPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	this -> bShowMouseCursor = true;
	this -> bEnableClickEvents = true;
	this -> bEnableTouchEvents = true;
	this -> bEnableMouseOverEvents = true;
	this -> DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ABlackBoxPlayerController::BeginPlay()
{
	/*
	ATopCamera* Camera = GetWorld()->SpawnActor<ATopCamera>(FVector(-320, 820, 1200), FRotator(-70, -90, 0));
	this->SetViewTarget(Cast<AActor>(Camera)); 
	*/

}