// Copyright (c) 2015 Mateus Bezerra
#pragma once

class ATabuleiro;

#include "GameFramework/GameMode.h"
#include "BlackBoxGameMode.generated.h"


USTRUCT(BlueprintType)
struct FFaseStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 Tamanho;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 Atomos;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 Indice;
};

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class ABlackBoxGameMode : public AGameMode
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Configurações")
	TArray<FFaseStruct> Fases;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configurações")
	FFaseStruct Fase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	ATabuleiro* Tabuleiro;

public:
	ABlackBoxGameMode(const FObjectInitializer& ObjectInitializer);

	//void ChangeGameState(AGameState* GameState)
	//{
		//this->GameStat
	//}

	virtual void BeginPlay() override;

	void InitTabuleiro();

	int32 GetTempoInicial();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void NextLevel();

	bool IsLastLevel();

	bool IsFirstLevel();

	const FFaseStruct* GetFase();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	int32 GetTotalAtomos();
};



