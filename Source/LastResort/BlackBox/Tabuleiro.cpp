// Copyright (c) 2015 Mateus Bezerra

#include "LastResort.h"
#include "Components/TextRenderComponent.h"
#include "Atomo.h"
#include "Tabuleiro.h"

#define LOCTEXT_NAMESPACE "BlackBox.Tabuleiro"

ATabuleiro::ATabuleiro(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
	this -> DR = CreateDefaultSubobject<USceneComponent>(TEXT("DRTabuleiro"));
	this -> RootComponent = this -> DR;

	
	this -> Tempo = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TempoBox"));
	this -> Tempo -> SetRelativeLocation(FVector(200.f,0.f,0.f));
	this -> Tempo -> SetRelativeRotation(FRotator(90.f,0.f,0.f));
	this -> Tempo -> SetText(LOCTEXT("TempoRestante", "Tempo restante: "));
	this -> Tempo -> AttachTo(this -> DR);

	this->ComponenteCamera = CreateDefaultSubobject<UChildActorComponent>(TEXT("Componente Camera"));
	this->ComponenteCamera->SetChildActorClass(ATopCamera::StaticClass());
	this->ComponenteCamera->SetRelativeLocation(FVector(320.f, 0.f, 1200.f));
	this->ComponenteCamera->SetRelativeRotation(FRotator(-70.f, 180.f, 0.f));
	this->ComponenteCamera->AttachTo(this->DR);

	this -> Espacamento = 100.f;
}


void ATabuleiro::BeginPlay()
{
	Super::BeginPlay();

	this->AtorCamera = Cast<ATopCamera>(this->ComponenteCamera->ChildActor);

	if (GetWorld() && GetWorld()->GetGameState())
	{
		if (GetWorld()->GetGameState()->IsA(AFaseGameState::StaticClass()))
		{
			AFaseGameState* Fase = Cast<AFaseGameState>(GetWorld()->GetGameState());
			this->Tamanho = Fase->GetColunas();

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
				}
			}

			this->ComponenteCamera->SetRelativeLocation(FVector(320.f, this->Tamanho * this->Espacamento, 1200.f));
			/*
			const int32 Lasers = (this->Tamanho) * 4;

			for (int32 i = 0; i < Lasers; i++)
			{
				const float XOffset = (i / (this->Tamanho)) * (this->Espacamento);
				const float YOffset = (i % (this->Tamanho)) * (this->Espacamento);


				const FVector Local = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

				AAtomo* NovoBloco = GetWorld()->SpawnActor<AAtomo>(Local, FRotator(0, 0, 0));

				if (NovoBloco != nullptr)
				{
					NovoBloco->AttachRootComponentToActor(this);
					NovoBloco->SetActorScale3D(FVector(0.4f));
					NovoBloco->SetTabuleiro(this);
				}
			} /**/
		}
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

#undef LOCTEXT_NAMESPACE
