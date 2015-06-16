// Copyright (c) 2015 Mateus Bezerra

#pragma once

#include "Engine/GameInstance.h"
#include "LastResortGameInstance.generated.h"

USTRUCT()
struct FDificuldadeStruct
{
	GENERATED_USTRUCT_BODY()
	static const FDificuldadeStruct* FACIL;
	static const FDificuldadeStruct* MEDIO;
	static const FDificuldadeStruct* DIFICIL;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 TempoMaximo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 PenalidadeLaser;

	FDificuldadeStruct() : TempoMaximo(0), PenalidadeLaser(0) {}
	FDificuldadeStruct(int32 Tempo, int32 Penalidade) : TempoMaximo(Tempo), PenalidadeLaser(Penalidade) {}
};

UCLASS()
class LASTRESORT_API ULastResortGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	
public:

	ULastResortGameInstance();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool PularInstrucoes;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FDificuldadeStruct Dificuldade;

	
};
