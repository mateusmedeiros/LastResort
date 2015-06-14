// Copyright (c) 2015 Mateus Bezerra

#include "LastResort.h"
#include "BlackBox/BlackBoxPlayerController.h"
#include "BlackBox/BlackBoxGameState.h"
#include "BlackBox/Tabuleiro.h"
#include "BlackBoxGameMode.h"

ABlackBoxGameMode::ABlackBoxGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	this->DefaultPawnClass = nullptr;
	this->PlayerControllerClass = ABlackBoxPlayerController::StaticClass();
	//this->GameStateClass = ABlackBoxGameState::StaticClass();

	TArray<FaseStruct> Fases{};
	this->Fases = Fases;

	//this->GameStateClass = AFasesGameState::StaticClass();
	FaseStruct Fase1{};
	Fase1.Tamanho = 8;
	this->Fases.Add(Fase1);

	FaseStruct Fase2{};
	Fase2.Tamanho = 9;
	this->Fases.Add(Fase2);

	FaseStruct Fase3{};
	Fase3.Tamanho = 10;
	this->Fases.Add(Fase3);

	this->Fase = this->Fases[0];
}

void ABlackBoxGameMode::BeginPlay()
{
	Super::BeginPlay();
	InitTabuleiro();
}

void ABlackBoxGameMode::InitTabuleiro()
{
	if (GetWorld() != nullptr) {

		ATabuleiro* Tabuleiro = GetWorld()->SpawnActor<ATabuleiro>(FVector(-340, 0, 40), FRotator::ZeroRotator);
		if (Tabuleiro != nullptr)
		{
			this->Tabuleiro = Tabuleiro;
			GetWorld()->GetLevel(0)->Actors.Add(this->Tabuleiro);
		}
	}
}

void ABlackBoxGameMode::NextLevel()
{
	// Indice do struct não é zero-based
	this->Fase = this->Fases[this->Fase.Indice];

	this->ResetLevel();
	this->InitTabuleiro();
}

bool ABlackBoxGameMode::IsFirstLevel()
{
	return this->Fase.Indice == 1;
}

bool ABlackBoxGameMode::IsLastLevel()
{
	return this->Fase.Indice == this->Fases.Num();
}

const FaseStruct* ABlackBoxGameMode::GetFase()
{
	return &(this->Fase);
}