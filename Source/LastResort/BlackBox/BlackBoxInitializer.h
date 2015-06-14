// Copyright (c) 2015 Mateus Bezerra

#pragma once

#include "GameFramework/Actor.h"
#include "BlackBoxInitializer.generated.h"

UCLASS()
class LASTRESORT_API ABlackBoxInitializer : public AActor
{
	GENERATED_BODY()
	
public:	

	virtual void BeginPlay() override;
	
};
