// Copyright (c) 2015 Mateus Bezerra
#pragma once
#include "GameFramework/GameMode.h"
#include "BlackBoxGameMode.generated.h"

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class ABlackBoxGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABlackBoxGameMode(const FObjectInitializer& ObjectInitializer);
};



