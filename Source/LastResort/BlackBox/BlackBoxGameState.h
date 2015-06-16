// Copyright (c) 2015 Mateus Bezerra

#pragma once

#include "GameFramework/GameState.h"
#include <LastResort/BlackBoxGameMode.h>
#include "Tabuleiro.h"
#include "Runtime/Core/Public/Containers/Queue.h"
#include "BlackBoxGameState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTickSegundo, int32, Tempo, FString, TempoTexto);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FUpdateAtomos, int32, AtomosSelecionados, int32, X, int32, Y);

UCLASS()
class LASTRESORT_API ABlackBoxGameState : public AGameState
{
	GENERATED_BODY()

	TQueue<AAtomo*> ReferenciaAtomosSelecionados;

public:

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

	UFUNCTION(BlueprintCallable, Category = "Atomos Selecionados")
	void AddAtomoSelecionado(AAtomo* Atomo)
	{
		this->ReferenciaAtomosSelecionados.Enqueue(Atomo);
	}

	UFUNCTION(BlueprintCallable, Category = "Atomos Selecionados")
	AAtomo* RemoveAtomoSelecionado()
	{
		AAtomo* Atomo;
		this->ReferenciaAtomosSelecionados.Dequeue(Atomo);
		return Atomo;
	}

	UFUNCTION(BlueprintCallable, Category = "Atomos Selecionados")
	bool IsAtomosSelecionadosVazio()
	{
		return this->ReferenciaAtomosSelecionados.IsEmpty();
	}	
	
	UFUNCTION(BlueprintCallable, Category = "Atomos Selecionados")
	AAtomo* PeekAtomoDaPonta()
	{
		AAtomo* Atomo;
		this->ReferenciaAtomosSelecionados.Peek(Atomo);
		return Atomo;
	}
	
};
