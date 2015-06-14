// Copyright (c) 2015 Mateus Bezerra
#pragma once
#include "GameFramework/GameMode.h"
#include "BlackBoxGameMode.generated.h"

UENUM(BlueprintType)
enum class DificuldadeEnum : uint8
{
	FACIL UMETA(DisplayName = "F�cil"),
	MEDIO UMETA(DisplayName = "M�dio"),
	DIFICIL UMETA(DisplayName = "Dif�cil")
};

USTRUCT()
struct FaseStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int32 Tamanho;

	UPROPERTY()
	int32 Indice;
};

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class ABlackBoxGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Configura��es")
	DificuldadeEnum Dificuldade;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Configura��es")
	TArray<FaseStruct> Fases;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configura��es")
	FaseStruct Fase;

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

	void NextLevel();

	bool IsLastLevel();

	bool IsFirstLevel();

	const FaseStruct* GetFase();
};



