// Copyright (c) 2015 Mateus Bezerra

#include "LastResort.h"
#include "Laser.h"

#define LOCTEXT_NAMESPACE "ALaser"

ALaser::ALaser()
{

	static struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> MeshBaseTraseira;
		ConstructorHelpers::FObjectFinder<UStaticMesh> MeshBaseDianteira;
		ConstructorHelpers::FObjectFinder<UStaticMesh> MeshCorpo;

		ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialBaseTraseira;
		ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialBaseDianteira;
		ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialCorpo0;
		ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialCorpo1;


		FConstructorStatics()
			: 
		MeshBaseTraseira(TEXT("StaticMesh'/Game/Mesh/Shape_Wedge_A.Shape_Wedge_A'")),
		MeshBaseDianteira(TEXT("StaticMesh'/Game/Mesh/SM_CornerFrame.SM_CornerFrame'")),
		MeshCorpo(TEXT("StaticMesh'/Game/Mesh/SM_MatPreviewMesh_02.SM_MatPreviewMesh_02'")),

		MaterialBaseTraseira(TEXT("Material'/Game/Materials/M_Basic_Wall.M_Basic_Wall'")),
		MaterialBaseDianteira(TEXT("Material'/Game/Materials/M_Basic_Wall.M_Basic_Wall'")),
		MaterialCorpo0(TEXT("Material'/Game/Materials/M_Basic_Floor.M_Basic_Floor'")),
		MaterialCorpo1(TEXT("Material'/Game/Materials/M_Basic_Wall.M_Basic_Wall'")) {}
	} ObjetosEstaticos;


	this->DR = CreateDefaultSubobject<USceneComponent>(TEXT("Laser"));
	this->RootComponent = this->DR;

	UStaticMeshComponent* BaseTraseira = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Traseira"));
	BaseTraseira->SetStaticMesh(ObjetosEstaticos.MeshBaseTraseira.Object);
	BaseTraseira->SetMaterial(0, ObjetosEstaticos.MaterialBaseTraseira.Object);
	BaseTraseira->SetRelativeLocationAndRotation(FVector(-103.f, -108.5f, 13.2f), FRotator(0.f, 0.f, 90.f));
	BaseTraseira->SetRelativeScale3D(FVector(1.86f, 1.4f, 2.16f));
	BaseTraseira->AttachTo(this->DR);

	UStaticMeshComponent* BaseDianteira = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Dianteira"));
	BaseDianteira->SetStaticMesh(ObjetosEstaticos.MeshBaseDianteira.Object);
	BaseDianteira->SetMaterial(0, ObjetosEstaticos.MaterialBaseDianteira.Object);
	BaseDianteira->SetRelativeLocationAndRotation(FVector(-102.5f, 0.f, -50.f), FRotator(0.f));
	BaseDianteira->SetRelativeScale3D(FVector(12.9f, 10.9f, 6.6f));
	BaseDianteira->AttachTo(this->DR);


	UStaticMeshComponent* Corpo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Corpo"));
	Corpo->SetStaticMesh(ObjetosEstaticos.MeshCorpo.Object);
	Corpo->SetMaterial(0, ObjetosEstaticos.MaterialCorpo0.Object);
	Corpo->SetMaterial(1, ObjetosEstaticos.MaterialCorpo1.Object);
	Corpo->SetRelativeLocationAndRotation(FVector(0.f), FRotator(-20.f, 0.f, 0.f));
	Corpo->SetRelativeScale3D(FVector(1));
	Corpo->OnClicked.AddDynamic(this, &ALaser::ActionClick);
	Corpo->AttachTo(this->DR);
	
	UTextRenderComponent* Valor = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Corpo"));
	Valor->SetRelativeLocationAndRotation(FVector(180.f, 75.f, 265.f), FRotator(90.f, 0.f, 0.f));
	Valor->SetWorldSize(0.f);
	Valor->bCastDynamicShadow = true;
	Valor->AttachTo(this->DR);
	Valor->SetText(FText::GetEmpty());
	Valor->SetTextRenderColor(FColor::Blue);

}

void ALaser::ActionClick(UPrimitiveComponent* ClickedComp)
{
	static bool Ativado = false;
	if (!Ativado)
	{
		Ativado = true;
		this->Valor->SetWorldSize(240.f);
	}
}

void ALaser::BeginPlay()
{
	Super::BeginPlay();
	
}

#undef LOCTEXT_NAMESPACE