// Copyright (c) 2015 Mateus Bezerra

#pragma once

#include "GameFramework/GameState.h"
#include "FaseGameState.generated.h"

/**
 * 
 */
UCLASS(abstract)
class LASTRESORT_API AFaseGameState : public AGameState
{
	GENERATED_BODY()
	
public:

	virtual int32 GetColunas() PURE_VIRTUAL(AFaseGameState::GetColunas, ) { return 0; }

	virtual int32 GetLinhas() PURE_VIRTUAL(AFaseGameState::GetLinhas, ) { return 0; }
};
