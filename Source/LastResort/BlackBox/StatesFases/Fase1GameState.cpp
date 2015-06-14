// Copyright (c) 2015 Mateus Bezerra

#include "LastResort.h"
#include "Fase1GameState.h"

AFase1GameState::AFase1GameState()
{
	this->Colunas = 8;
	this->Linhas = 8;
}

void AFase1GameState::BeginPlay()
{
	if (GetWorld() != nullptr) {

		ATabuleiro* Tabuleiro = GetWorld()->SpawnActor<ATabuleiro>(FVector(-340, 0, 40), FRotator::ZeroRotator);
		if (Tabuleiro != nullptr)
		{
			//VSCREENMSG(TEXT("C"));
			this->Tabuleiro = Tabuleiro;

			GetWorld()->GetLevel(0)->Actors.Add(Tabuleiro);
			GetWorld()->GetFirstPlayerController()->SetViewTarget(Cast<AActor>(this->Tabuleiro->GetCamera()));
		}
	}

	//this->SetViewTarget(Cast<AActor>(Camera));
}




