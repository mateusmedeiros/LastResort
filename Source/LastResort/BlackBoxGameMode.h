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

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class ABlackBoxGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Configura��es")
	DificuldadeEnum Dificuldade;

public:
	ABlackBoxGameMode(const FObjectInitializer& ObjectInitializer);
};



