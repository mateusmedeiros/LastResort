// Copyright (c) 2015 Mateus Bezerra

#include "LastResort.h"
#include "Components/TextRenderComponent.h"
#include "Atomo.h"
#include <LastResort/BlackBoxGameMode.h>
#include "BlackBoxGameState.h"
#include "Solucao/Solucao.h"
#include "Tabuleiro.h"

#define LOCTEXT_NAMESPACE "BlackBox.Tabuleiro"

ATabuleiro::ATabuleiro(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
	this -> DR = CreateDefaultSubobject<USceneComponent>(TEXT("DRTabuleiro"));
	this -> RootComponent = this -> DR;

	this->ComponenteCamera = CreateDefaultSubobject<UChildActorComponent>(TEXT("Componente Camera"));
	this->ComponenteCamera->SetChildActorClass(ATopCamera::StaticClass());
	this->ComponenteCamera->SetRelativeLocation(FVector(320.f, 0.f, 1200.f));
	this->ComponenteCamera->SetRelativeRotation(FRotator(-80.f, 180.f, 0.f));
	this->ComponenteCamera->AttachTo(this->DR);

	this -> Espacamento = 100.f;
}


void ATabuleiro::BeginDestroy()
{
	Super::BeginDestroy();

	delete this->Solucao;
}

void ATabuleiro::BeginPlay()
{
	Super::BeginPlay();

	this->AtorCamera = Cast<ATopCamera>(this->ComponenteCamera->ChildActor);

	if (GetWorld() && GetWorld()->GetGameState())
	{
		ABlackBoxGameMode* GameMode = Cast<ABlackBoxGameMode>(GetWorld()->GetAuthGameMode());
		this->Tamanho = GameMode->GetFase()->Tamanho;

		const int32 Blocos = (this -> Tamanho) * (this -> Tamanho);

		for(int32 i = 0; i < Blocos; i++)
		{
			const float XOffset = (i / (this -> Tamanho)) * (this -> Espacamento);
			const float YOffset = (i % (this -> Tamanho)) * (this -> Espacamento); 


			const FVector Local = FVector(XOffset, YOffset, 0.f) + GetActorLocation();
		
			AAtomo* NovoBloco = GetWorld() -> SpawnActor<AAtomo>(Local, FRotator(0,0,0));

			if(NovoBloco != nullptr)
			{
				NovoBloco->AttachRootComponentToActor(this);
				NovoBloco -> SetActorScale3D(FVector(0.4f));
				NovoBloco -> SetTabuleiro(this);
				NovoBloco->X = (this->Tamanho - 1) - (i % (this->Tamanho));
				NovoBloco->Y = (i / (this->Tamanho));
				this->Atomos.Add(NovoBloco);
			}
		}

		FVector ScaleLaser = FVector(0.35f);
		/*
		FVector OrigemAtomo;
		FVector DestinoAtomo;

		this->Atomos[2]->GetActorBounds(false, OrigemAtomo, DestinoAtomo);

		//float AtomoX = (DestinoAtomo.X - OrigemAtomo.X) * 2.f;
		//float AtomoY = (DestinoAtomo.Y - OrigemAtomo.Y) * 2.f;

		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, *FString::Printf(TEXT("Origem X: %f  Y: %f  Z: %f"), OrigemAtomo.X, OrigemAtomo.Y, OrigemAtomo.Z));
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, *FString::Printf(TEXT("Destino X: %f  Y: %f  Z: %f"), DestinoAtomo.X, DestinoAtomo.Y, DestinoAtomo.Z));*/

		this->Solucao = new FSolucao(this, Cast<ABlackBoxGameMode>(GetWorld()->GetAuthGameMode())->GetTotalAtomos());
		// Lasers de cima
		for (int32 i = 0; i < this->Tamanho; i++)
		{
			FVector AtomoCorrespondente = this->GetAtomo(i, 0)->GetActorLocation();
			const float XOffset = AtomoCorrespondente.X - (this->Espacamento * 1.5f);
			const float YOffset = AtomoCorrespondente.Y;

			ALaser* NovoLaser = GetWorld()->SpawnActor<ALaser>(FVector(XOffset + 350, YOffset, 100), FRotator(0, 0, 0));

			if (NovoLaser != nullptr)
			{
				NovoLaser->AttachRootComponentToActor(this);
				NovoLaser->SetActorScale3D(ScaleLaser);
				NovoLaser->SetTabuleiro(this);
				
				if (Solucao->LasersCima[i].Estado == ELaserEstado::H)
				{
					NovoLaser->Valor->SetText(LOCTEXT("ValorH", "H"));
				} 
				else if (Solucao->LasersCima[i].Estado == ELaserEstado::R)
				{
					NovoLaser->Valor->SetText(LOCTEXT("ValorR", "R"));
				}
				else
				{
					NovoLaser->Valor->SetText(FString::Printf(TEXT("%d"), Solucao->LasersCima[i].Numero));
				}
				this->LasersCima.Add(NovoLaser);
			}
		}

		// Lasers da direita
		for (int32 i = 0; i < this->Tamanho; i++)
		{
			FVector AtomoCorrespondente = this->GetAtomo(this->Tamanho - 1, i)->GetActorLocation();
			const float XOffset = AtomoCorrespondente.X;
			const float YOffset = AtomoCorrespondente.Y - (this->Espacamento * 1.5f);

			ALaser* NovoLaser = GetWorld()->SpawnActor<ALaser>(FVector(XOffset + 350, YOffset, 100), FRotator(0, 90, 0));

			if (NovoLaser != nullptr)
			{
				NovoLaser->AttachRootComponentToActor(this);
				NovoLaser->SetActorScale3D(ScaleLaser);
				NovoLaser->SetTabuleiro(this);
				if (Solucao->LasersDireita[i].Estado == ELaserEstado::H)
				{
					NovoLaser->Valor->SetText(LOCTEXT("ValorH", "H"));
				}
				else if (Solucao->LasersDireita[i].Estado == ELaserEstado::R)
				{
					NovoLaser->Valor->SetText(LOCTEXT("ValorR", "R"));
				}
				else
				{
					NovoLaser->Valor->SetText(FString::Printf(TEXT("%d"), Solucao->LasersDireita[i].Numero));
				}
				this->LasersDireita.Add(NovoLaser);
			}
		}

		// Lasers de baixo
		for (int32 i = 0; i < this->Tamanho; i++)
		{
			FVector AtomoCorrespondente = this->GetAtomo((this->Tamanho - 1) - i, this->Tamanho - 1)->GetActorLocation();
			const float XOffset = AtomoCorrespondente.X + (this->Espacamento * 1.5f);
			const float YOffset = AtomoCorrespondente.Y;

			ALaser* NovoLaser = GetWorld()->SpawnActor<ALaser>(FVector(XOffset + 350, YOffset, 100), FRotator(0, 180, 0));

			if (NovoLaser != nullptr)
			{
				NovoLaser->AttachRootComponentToActor(this);
				NovoLaser->SetActorScale3D(ScaleLaser);
				NovoLaser->SetTabuleiro(this);
				if (Solucao->LasersBaixo[i].Estado == ELaserEstado::H)
				{
					NovoLaser->Valor->SetText(LOCTEXT("ValorH", "H"));
				}
				else if (Solucao->LasersBaixo[i].Estado == ELaserEstado::R)
				{
					NovoLaser->Valor->SetText(LOCTEXT("ValorR", "R"));
				}
				else
				{
					NovoLaser->Valor->SetText(FString::Printf(TEXT("%d"), Solucao->LasersBaixo[i].Numero));
				}
				this->LasersBaixo.Add(NovoLaser);
			}
		}

		// Lasers da esquerda
		for (int32 i = 0; i < this->Tamanho; i++)
		{
			FVector AtomoCorrespondente = this->GetAtomo(0, (this->Tamanho - 1) - i)->GetActorLocation();
			const float XOffset = AtomoCorrespondente.X;
			const float YOffset = AtomoCorrespondente.Y + (this->Espacamento * 1.5f);

			ALaser* NovoLaser = GetWorld()->SpawnActor<ALaser>(FVector(XOffset + 350, YOffset, 100.f), FRotator(0, 270, 0));

			if (NovoLaser != nullptr)
			{
				NovoLaser->AttachRootComponentToActor(this);
				NovoLaser->SetActorScale3D(ScaleLaser);
				NovoLaser->SetTabuleiro(this);
				if (Solucao->LasersEsquerda[i].Estado == ELaserEstado::H)
				{
					NovoLaser->Valor->SetText(LOCTEXT("ValorH", "H"));
				}
				else if (Solucao->LasersEsquerda[i].Estado == ELaserEstado::R)
				{
					NovoLaser->Valor->SetText(LOCTEXT("ValorR", "R"));
				}
				else
				{
					NovoLaser->Valor->SetText(FString::Printf(TEXT("%d"), Solucao->LasersEsquerda[i].Numero));
				}
				this->LasersEsquerda.Add(NovoLaser);
			}
		}

		// Faz os cálculos da posição da câmera de acordo com o espaçamento e o tamanho da matriz
		// para dar um pouco de flexibilidade à escolha do tamanho e espaçamento, dentro do possível.
		float PosicaoCameraX = ((static_cast<float>(this->Tamanho) * this->Espacamento) / 8.f) + (this->Espacamento * (static_cast<float>(this->Tamanho) / 4.f));
		float PosicaoCameraY = ((static_cast<float>(this->Tamanho) * this->Espacamento) / 2.f) - ((static_cast<float>(this->Tamanho) * this->Espacamento) / 16.f);
		float PosicaoCameraZ = ((static_cast<float>(this->Tamanho) * this->Espacamento) + 450.f);
		//this->Tamanho * this->Espacamento


		//FVector PosicaoCamera;

		//if (this->Tamanho % 2)
		//{
//			PosicaoCamera = this->GetAtomo((this->Tamanho / 2) + 1, (this->Tamanho / 2) + 1)->GetActorLocation();
//		} else
		//{
//			PosicaoCamera = this->GetAtomo(this->Tamanho / 2, this->Tamanho / 2)->GetActorLocation();
//			PosicaoCamera = (this->GetAtomo((this->Tamanho / 2) + 1, (this->Tamanho / 2) + 1) ->GetActorLocation() + PosicaoCamera) / 2.f;
//		}
		
		//this->ComponenteCamera->SetRelativeLocation(FVector(PosicaoCamera.X, PosicaoCamera.Y, 20));
		this->ComponenteCamera->SetRelativeLocation(FVector(PosicaoCameraX, PosicaoCameraY, PosicaoCameraZ));
		GetWorld()->GetFirstPlayerController()->SetViewTarget(Cast<AActor>(this->GetCamera()));

		Cast<ABlackBoxGameState>(GetWorld()->GetGameState())->Tabuleiro = this;
	}

}


/*void ATabuleiro::Marcar()
{
	/* Diminui tempo */
	// Update text
	//FText Pontuacao = LOCTEXT("Pontuacao", "Score: %d");
	//FString NovoTempo = FString::Printf(Pontuacao, this -> Tempo);
	//this -> Tempo -> SetText(NovoTempo);
//}

AAtomo* ATabuleiro::GetAtomo(int32 X, int32 Y) const
{
	if (GetWorld() && GetWorld()->GetAuthGameMode())
	{
		ABlackBoxGameMode* GameMode = Cast<ABlackBoxGameMode>(GetWorld()->GetAuthGameMode());

		X = (this->Tamanho - 1) - X;
		Y = (Y * this->Tamanho);

		return this->Atomos[X + Y];
	}
	return nullptr;
}

const ALaser* ATabuleiro::GetLaser(ATabuleiro::DirecaoLaser Direcao, int8 Index) const
{
	switch (Direcao)
	{
	case ATabuleiro::DirecaoLaser::CIMA:
		return this->LasersCima[Index];

	case ATabuleiro::DirecaoLaser::DIREITA:
		return this->LasersDireita[Index];

	case ATabuleiro::DirecaoLaser::BAIXO:
		return this->LasersBaixo[Index];

	case ATabuleiro::DirecaoLaser::ESQUERDA:
		return this->LasersEsquerda[Index];
	}

	return nullptr;
}

#undef LOCTEXT_NAMESPACE
