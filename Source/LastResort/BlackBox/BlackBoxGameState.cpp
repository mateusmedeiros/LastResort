// Copyright (c) 2015 Mateus Bezerra

#include "LastResort.h"
#include "BlackBoxGameState.h"

ABlackBoxGameState::ABlackBoxGameState() {
	this->AtomosSelecionados = 0;
	//this->RelogioPassando = false;
	this->RelogioPassando = true;
}

void ABlackBoxGameState::BeginPlay()
{
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &ABlackBoxGameState::TickSegundo, 1.0f, true, 0.f); 
}

bool ABlackBoxGameState::IncrementarAtomos(AAtomo* Atomo)
{
	if (this->AtomosSelecionados < (Cast<ABlackBoxGameMode>(GetWorld()->GetAuthGameMode())->GetFase()->Atomos))
	{
		this->AtomosSelecionados++;
		this->OnUpdateAtomos.Broadcast(this->AtomosSelecionados, Atomo->X, Atomo->Y);
		return true;
	}

	return false;
}

bool ABlackBoxGameState::DecrementarAtomos(AAtomo* Atomo)
{
	if (this->AtomosSelecionados > 0)
	{
		this->AtomosSelecionados--;
		this->OnUpdateAtomos.Broadcast(this->AtomosSelecionados, Atomo->X, Atomo->Y);
		return true;
	}

	return false;
}

void ABlackBoxGameState::TickSegundo()
{
	if (this->RelogioPassando)
	{
		this->Tempo--;
		int32 Minuto = this->Tempo / 60;
		int32 Segundo = this->Tempo % 60;

		FString TempoTexto = FString::Printf(TEXT("%02d:%02d"), Minuto, Segundo);
		this->OnTickSegundo.Broadcast(this->Tempo, TempoTexto);
	}
}

