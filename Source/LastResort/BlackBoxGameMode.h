// Copyright (c) 2015 Mateus Bezerra
#pragma once
#include "GameFramework/GameMode.h"
#include "BlackBoxGameMode.generated.h"

UENUM(BlueprintType)
enum class DificuldadeEnum : uint8
{
	FACIL UMETA(DisplayName = "Fácil"),
	MEDIO UMETA(DisplayName = "Médio"),
	DIFICIL UMETA(DisplayName = "Difícil")
};

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class ABlackBoxGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Configurações")
	DificuldadeEnum Dificuldade;

public:
	ABlackBoxGameMode(const FObjectInitializer& ObjectInitializer);
};



