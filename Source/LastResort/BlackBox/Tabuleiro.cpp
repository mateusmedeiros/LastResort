// Copyright (c) 2015 Mateus Bezerra

#include "LastResort.h"
#include "Components/TextRenderComponent.h"
#include "Tabuleiro.h"
#include "Atomo.h"

ATabuleiro::ATabuleiro(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
	this -> DR = CreateDefaultSubobject<USceneComponent>(TEXT("DRTabuleiro"));
	this -> RootComponent = this -> DR;

	
	this -> Tempo = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TempoBox"));
	this -> Tempo -> SetRelativeLocation(FVector(200.f,0.f,0.f));
	this -> Tempo -> SetRelativeRotation(FRotator(90.f,0.f,0.f));
	this -> Tempo -> SetText(NSLOCTEXT("Doodad.LastResort", "TempoRestante", "Tempo restante: "));
	this -> Tempo -> AttachTo(this -> DR);

	this -> Tamanho = 3;
	this -> Espacamento = 300.f;
}


void ATabuleiro::BeginPlay()
{

	Super::BeginPlay();

	const int32 Blocos = (this -> Tamanho) * (this -> Tamanho);

	for(int32 i = 0; i < Blocos; i++)
	{
		const float XOffset = (i / (this -> Tamanho)) * (this -> Espacamento);
		const float YOffset = (i % (this -> Tamanho)) * (this -> Espacamento); 


		const FVector Local = FVector(XOffset, YOffset, 0.f) + GetActorLocation();
		
		AAtomo* NovoBloco = GetWorld() -> SpawnActor<AAtomo>(Local, FRotator(0,0,0));
		NovoBloco -> SetActorScale3D(FVector(2));

		if(NovoBloco != NULL)
		{
			(NovoBloco -> SetTabuleiro(this));
		}
	}

}


void ATabuleiro::Marcar()
{
	/* Diminui tempo */
	// Update text
	FString NovoTempo = FString::Printf(TEXT("Score: %d"), this -> Tempo);
	this -> Tempo -> SetText(NovoTempo);
}
