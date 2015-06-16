// Copyright (c) 2015 Mateus Bezerra

#include "LastResort.h"
#include "BlackBox/BlackBoxPlayerController.h"
#include "BlackBox/BlackBoxGameState.h"
#include "BlackBox/Tabuleiro.h"
#include "LastResortGameInstance.h"
#include "BlackBoxGameMode.h"

ABlackBoxGameMode::ABlackBoxGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	this->DefaultPawnClass = nullptr;
	this->PlayerControllerClass = ABlackBoxPlayerController::StaticClass();
	//this->PlayerControllerClass = ConstructorHelpers::FObjectFinder<UClass>(TEXT("Blueprint'/Game/Blueprints/BlackBoxPlayerController.BlackBoxPlayerController_C'")).Object;
	this->GameStateClass = ABlackBoxGameState::StaticClass();

	TArray<FFaseStruct> Fases{};
	this->Fases = Fases;

	//this->GameStateClass = AFasesGameState::StaticClass();
	FFaseStruct Fase1{};
	Fase1.Tamanho = 8;
	Fase1.Atomos = 3;
	Fase1.Indice = 1;
	this->Fases.Add(Fase1);

	FFaseStruct Fase2{};
	Fase2.Tamanho = 9;
	Fase2.Atomos = 4;
	Fase2.Indice = 2;
	this->Fases.Add(Fase2);

	FFaseStruct Fase3{};
	Fase3.Tamanho = 10;
	Fase2.Atomos = 5;
	Fase2.Indice = 3;
	this->Fases.Add(Fase3);

	this->Fase = this->Fases[0];
}

void ABlackBoxGameMode::BeginPlay()
{
	Super::BeginPlay();
	Cast<ABlackBoxGameState>(GetWorld()->GetGameState())->Tempo = this->GetTempoInicial();
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
	Cast<ABlackBoxGameState>(GetWorld()->GetGameState())->Tempo = this->GetTempoInicial();
	this->InitTabuleiro();
}

int32 ABlackBoxGameMode::GetTempoInicial()
{
	return Cast<ULastResortGameInstance>(GetWorld()->GetGameInstance())->Dificuldade.TempoMaximo;
}

bool ABlackBoxGameMode::IsFirstLevel()
{
	return this->Fase.Indice == 1;
}

bool ABlackBoxGameMode::IsLastLevel()
{
	return this->Fase.Indice == this->Fases.Num();
}

const FFaseStruct* ABlackBoxGameMode::GetFase()
{
	return &(this->Fase);
}

int32 ABlackBoxGameMode::GetTotalAtomos()
{
	return this->GetFase()->Atomos;
}