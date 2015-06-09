// Copyright (c) 2015 Mateus Bezerra

#pragma once
#include "GameFramework/Actor.h"
#include "Atomo.generated.h"

UCLASS(minimalapi)
class AAtomo : public AActor
{
	GENERATED_BODY()

	bool Ativo;

protected:

	AAtomo(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Category = "Atomo", BlueprintReadOnly, VisibleAnywhere)
	class USceneComponent* DR;

	UPROPERTY(Category = "Atomo", BlueprintReadOnly, VisibleAnywhere)
	class UStaticMeshComponent* MeshHighlightAtomo;

	UPROPERTY(Category = "Atomo", BlueprintReadOnly, VisibleAnywhere)
	class UMaterialInstance* MaterialHighlightAtomo;

	UPROPERTY(Category = "Atomo", BlueprintReadOnly, VisibleAnywhere)
	class ATabuleiro* Tabuleiro;

	UFUNCTION()
	void BlockClicked(UPrimitiveComponent* ClickedComp);

	UFUNCTION()
	void OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

public:
	
	FORCEINLINE class USceneComponent* GetDR() const
	{
		return this -> DR;
	}
	
	FORCEINLINE class UStaticMeshComponent* GetMeshHighlightAtomo() const
	{
		return this -> MeshHighlightAtomo;
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



