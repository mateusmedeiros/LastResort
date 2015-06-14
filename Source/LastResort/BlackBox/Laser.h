// Copyright (c) 2015 Mateus Bezerra

#pragma once

#include "GameFramework/Actor.h"
#include "Laser.generated.h"

UCLASS()
class LASTRESORT_API ALaser : public AActor
{
	GENERATED_BODY()

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
	
};
