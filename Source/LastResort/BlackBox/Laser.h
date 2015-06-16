// Copyright (c) 2015 Mateus Bezerra

#pragma once

#include "GameFramework/Actor.h"
#include "Laser.generated.h"


class ATabuleiro;

UCLASS()
class LASTRESORT_API ALaser : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	ATabuleiro* Tabuleiro;

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	USceneComponent* DR;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* BaseTraseira;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* BaseDianteira;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* Corpo;

	
public:	
	ALaser();

	virtual void BeginPlay() override;	

	const ATabuleiro* GetTabuleiro()
	{
		return Tabuleiro;
	}
	
	void SetTabuleiro(ATabuleiro* Tabuleiro)
	{
		this->Tabuleiro = Tabuleiro;
	}
};
