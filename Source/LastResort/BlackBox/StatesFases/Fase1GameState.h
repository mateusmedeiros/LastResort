// Copyright (c) 2015 Mateus Bezerra

#pragma once

#include "GameFramework/GameState.h"
#include "FaseGameState.h"
#include <LastResort/BlackBox/Tabuleiro.h>
#include "Fase1GameState.generated.h"

/**
 * 
 */
UCLASS()
class LASTRESORT_API AFase1GameState : public AFaseGameState
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 Colunas;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 Linhas;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	ATabuleiro* Tabuleiro;

public:

	AFase1GameState();

	int16 TempoRestante;

	virtual void BeginPlay() override;

	virtual int32 GetColunas() override
	{
		return Colunas;
	}

	virtual int32 GetLinhas() override
	{
		return Linhas;
	}
	
};
