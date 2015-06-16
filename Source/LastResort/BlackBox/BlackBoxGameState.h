// Copyright (c) 2015 Mateus Bezerra

#pragma once

#include "GameFramework/GameState.h"
#include <LastResort/BlackBoxGameMode.h>
#include "Tabuleiro.h"
#include "BlackBoxGameState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTickSegundo, int32, Tempo, FString, TempoTexto);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FUpdateAtomos, int32, AtomosSelecionados, int32, X, int32, Y);

UCLASS()
class LASTRESORT_API ABlackBoxGameState : public AGameState
{
	GENERATED_BODY()


public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AAtomo*> ReferenciaAtomosSelecionados;

	ABlackBoxGameState();

	UPROPERTY(BlueprintAssignable)
	FUpdateAtomos OnUpdateAtomos;

	UPROPERTY(BlueprintAssignable)
	FTickSegundo OnTickSegundo;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 AtomosSelecionados;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 Tempo;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	ATabuleiro* Tabuleiro;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool RelogioPassando;

	virtual void BeginPlay() override;

	UFUNCTION()
	bool IncrementarAtomos(AAtomo* Atomo);
	
	UFUNCTION()
	bool DecrementarAtomos(AAtomo* Atomo);

	void TickSegundo();

};
