// Copyright (c) 2015 Mateus Bezerra

#pragma once
#include "GameFramework/Actor.h"
#include "Atomo.h"
#include "Laser.h"
#include "TopCamera.h"
#include "Solucao/Solucao.h"
#include "Tabuleiro.generated.h"

UCLASS(minimalapi)
class ATabuleiro : public AActor
{
	GENERATED_BODY()

	TArray< AAtomo* > Atomos;

	TArray< ALaser* > LasersCima;
	TArray< ALaser* > LasersDireita;
	TArray< ALaser* > LasersBaixo;
	TArray< ALaser* > LasersEsquerda;


protected:

	UPROPERTY(Category = "Tabuleiro", BlueprintReadOnly, VisibleAnywhere)
	USceneComponent* DR;

	UPROPERTY(Category = "Tabuleiro", BlueprintReadOnly, VisibleAnywhere)
	UChildActorComponent* ComponenteCamera;

	ATopCamera* AtorCamera;

public:

	enum class DirecaoLaser { CIMA, DIREITA, BAIXO, ESQUERDA };

	ATabuleiro(const FObjectInitializer& ObjectInitializer);

	FSolucao* Solucao;

	int32 _tempo;

	UPROPERTY(Category = "Tabuleiro", VisibleAnywhere, BlueprintReadOnly)
	int32 Tamanho;

	UPROPERTY(Category = "Tabuleiro", VisibleAnywhere, BlueprintReadOnly)
	float Espacamento;

	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

	/*void Marcar();*/
	
	UFUNCTION(Category = "Tabuleiro", BlueprintCallable)
	AAtomo* GetAtomo(int32 X, int32 Y) const;

	const ALaser* GetLaser(DirecaoLaser Direcao, int8 Index) const;

	FORCEINLINE USceneComponent* GetDR() const
	{
		return DR;
	}
	
	FORCEINLINE ATopCamera* GetCamera() const
	{
		return AtorCamera;
	}

};



