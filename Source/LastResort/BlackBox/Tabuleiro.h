// Copyright (c) 2015 Mateus Bezerra

#pragma once
#include "GameFramework/Actor.h"
#include "Tabuleiro.generated.h"

UCLASS(minimalapi)
class ATabuleiro : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(Category = "Tabuleiro", BlueprintReadOnly, VisibleAnywhere)
	class USceneComponent* DR;

	UPROPERTY(Category = "Tabuleiro", VisibleDefaultsOnly, BlueprintReadOnly)
	class UTextRenderComponent* Tempo;

public:

	ATabuleiro(const FObjectInitializer& ObjectInitializer);

	int32 _tempo;

	UPROPERTY(Category = "Tabuleiro", VisibleAnywhere, BlueprintReadOnly)
	int32 Tamanho;

	UPROPERTY(Category = "Tabuleiro", VisibleAnywhere, BlueprintReadOnly)
	float Espacamento;

	virtual void BeginPlay() override;

	void Marcar();
	
	FORCEINLINE class USceneComponent* GetDR() const
	{
		return DR;
	}
	
	FORCEINLINE class UTextRenderComponent* GetTempo() const
	{
		return Tempo;
	}
};



