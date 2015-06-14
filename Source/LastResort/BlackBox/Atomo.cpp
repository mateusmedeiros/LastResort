// Copyright (c) 2015 Mateus Bezerra

#include "LastResort.h"
#include "Atomo.h"
#include "Tabuleiro.h"

AAtomo::AAtomo(const FObjectInitializer& ObjectInitializer)	: Super(ObjectInitializer)
{

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> MeshEsfera;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> MaterialPadraoEsfera;

		FConstructorStatics()
			: MeshEsfera(TEXT("/Game/Mesh/Shape_Sphere.Shape_Sphere")), MaterialPadraoEsfera(TEXT("MaterialInstanceConstant'/Game/Materials/AtomoNaoSelecionado.AtomoNaoSelecionado'")) {}
	};

	static FConstructorStatics ObjetosEstaticos;

	this -> DR = CreateDefaultSubobject<USceneComponent>(TEXT("DRAtomo"));
	this -> RootComponent = this -> DR;

	this -> MeshHighlightAtomo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AtomoMesh"));
	this -> MeshHighlightAtomo -> SetStaticMesh(ObjetosEstaticos.MeshEsfera.Get());
	this -> MeshHighlightAtomo -> SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
	this -> MeshHighlightAtomo -> SetRelativeLocation(FVector(0.f, 0.f, 25.f));
	this -> MeshHighlightAtomo -> SetMaterial(0, Cast<UMaterialInterface>(ObjetosEstaticos.MaterialPadraoEsfera.Get()));
	this -> MeshHighlightAtomo -> AttachTo(this -> DR);
	this -> MeshHighlightAtomo -> OnClicked.AddDynamic(this, &AAtomo::BlockClicked);
	//this -> MeshHighlightAtomo -> OnInputTouchBegin.AddDynamic(this, &AAtomo::OnFingerPressedBlock);

	//this -> MaterialHighlightAtomo = ObjetosEstaticos.OrangeMaterial.Get();
}

void AAtomo::BlockClicked(UPrimitiveComponent* ClickedComp)
{
	if(Ativo)
	{
		Ativo = false;
		static FString CaminhoMaterial = TEXT("MaterialInstanceConstant'/Game/Materials/AtomoNaoSelecionado.AtomoNaoSelecionado'");

		static UMaterialInstance* Material = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), this, *CaminhoMaterial));
		this -> MeshHighlightAtomo -> SetMaterial(0, Cast<UMaterialInterface>(Material));
	} 
	else
	{
		Ativo = true;
		static FString CaminhoMaterial = TEXT("MaterialInstanceConstant'/Game/Materials/AtomoSelecionado.AtomoSelecionado'");

		static UMaterialInstance* Material = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), this, *CaminhoMaterial));
		this -> MeshHighlightAtomo->SetMaterial(0, Cast<UMaterialInterface>(Material));
	}
}


void AAtomo::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	this -> BlockClicked(TouchedComponent);
}
