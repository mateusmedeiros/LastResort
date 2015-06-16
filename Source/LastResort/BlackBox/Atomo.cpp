// Copyright (c) 2015 Mateus Bezerra

#include "LastResort.h"
#include "BlackBoxGameState.h"
#include <LastResort/BlackBoxGameMode.h>
#include "Tabuleiro.h"
#include "Atomo.h"

AAtomo::AAtomo(const FObjectInitializer& ObjectInitializer)	: Super(ObjectInitializer)
{

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> MeshEsfera;
		ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> MaterialNaoSelecionado;
		ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> MaterialSelecionado;

		FConstructorStatics()
			: 
		MeshEsfera(TEXT("/Game/Mesh/Shape_Sphere.Shape_Sphere")), 
		MaterialNaoSelecionado(TEXT("MaterialInstanceConstant'/Game/Materials/AtomoNaoSelecionado.AtomoNaoSelecionado'")),
		MaterialSelecionado(TEXT("MaterialInstanceConstant'/Game/Materials/AtomoSelecionado.AtomoSelecionado'")) {}
	};

	static FConstructorStatics ObjetosEstaticos;

	this -> DR = CreateDefaultSubobject<USceneComponent>(TEXT("DRAtomo"));
	this -> RootComponent = this -> DR;

	this->Ativo = false;

	this -> Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AtomoMesh"));
	this -> Mesh -> SetStaticMesh(ObjetosEstaticos.MeshEsfera.Object);
	this -> Mesh -> SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
	this -> Mesh -> SetRelativeLocation(FVector(0.f, 0.f, 25.f));
	this -> Mesh -> SetMaterial(0, Cast<UMaterialInterface>(ObjetosEstaticos.MaterialNaoSelecionado.Object));
	this -> Mesh -> AttachTo(this -> DR);
	this -> Mesh -> OnClicked.AddDynamic(this, &AAtomo::BlockClicked);

	this->MaterialNaoSelecionado = ObjetosEstaticos.MaterialNaoSelecionado.Object;
	this->MaterialSelecionado = ObjetosEstaticos.MaterialSelecionado.Object;
	//this -> Mesh -> OnInputTouchBegin.AddDynamic(this, &AAtomo::OnFingerPressedBlock);

	//this -> MaterialHighlightAtomo = ObjetosEstaticos.OrangeMaterial.Get();
}

void AAtomo::BlockClicked(UPrimitiveComponent* ClickedComp)
{
	/*
	FVector Local = this->GetActorLocation();
	int32 It = 0;
	int32 It2 = 0;
	for (It = 0; It < this->Tabuleiro->Tamanho * this->Tabuleiro->Tamanho; It++)
	{
		if (this == this->Tabuleiro->Atomos[It])
		{
			break;
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, FString::Printf(TEXT("X: %f  Y: %f  Z: %f "), Local.X, Local.Y, Local.Z));

	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Blue, FString::Printf(TEXT("Atomos[%d];"), It));
	*/
	if (Ativo)
	{
		if (Cast<ABlackBoxGameState>(GetWorld()->GetGameState())->DecrementarAtomos(this))
		{
			Ativo = false;
			this->Mesh->SetMaterial(0, Cast<UMaterialInterface>(this->MaterialNaoSelecionado));
		}
	} 
	else 
	{
		if (Cast<ABlackBoxGameState>(GetWorld()->GetGameState())->IncrementarAtomos(this)) 
		{
			Ativo = true;
			this->Mesh->SetMaterial(0, Cast<UMaterialInterface>(this->MaterialSelecionado));
		}
	}
}


void AAtomo::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	this -> BlockClicked(TouchedComponent);
}
