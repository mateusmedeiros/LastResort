// Copyright (c) 2015 Mateus Bezerra

#pragma once
#include "GameFramework/Actor.h"
#include "Atomo.generated.h"

UCLASS(minimalapi)
class AAtomo : public AActor
{
	GENERATED_BODY()


protected:

	AAtomo(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(Category = "Atomo", BlueprintReadOnly, VisibleAnywhere)
	class USceneComponent* DR;

	UPROPERTY(Category = "Atomo", BlueprintReadOnly, VisibleAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(Category = "Atomo", BlueprintReadWrite, VisibleAnywhere)
	class UMaterialInstanceConstant* MaterialSelecionado;

	UPROPERTY(Category = "Atomo", BlueprintReadWrite, VisibleAnywhere)
	class UMaterialInstanceConstant* MaterialNaoSelecionado;

	UPROPERTY()
	class ATabuleiro* Tabuleiro;

	UFUNCTION()
	void BlockClicked(UPrimitiveComponent* ClickedComp);

	UFUNCTION()
	void OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

public:

	UPROPERTY(Category = "Atomo", BlueprintReadWrite, VisibleAnywhere)
	bool Ativo = false;

	UPROPERTY(Category = "Atomo", BlueprintReadOnly, VisibleAnywhere)
	int32 X;

	UPROPERTY(Category = "Atomo", BlueprintReadOnly, VisibleAnywhere)
	int32 Y;
	
	FORCEINLINE class USceneComponent* GetDR() const
	{
		return this -> DR;
	}
	
	FORCEINLINE class UStaticMeshComponent* GetMeshHighlightAtomo() const
	{
		return this -> Mesh;
	}
	/*
	FORCEINLINE class ATabuleiro* GetTabuleiro() const
	{
		return this -> Tabuleiro;
	}
	*/
	FORCEINLINE void SetTabuleiro(class ATabuleiro* Tabuleiro)
	{
		this -> Tabuleiro = Tabuleiro;
	}
};



