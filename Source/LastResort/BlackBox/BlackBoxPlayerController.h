// Copyright (c) 2015 Mateus Bezerra

#pragma once
#include "GameFramework/PlayerController.h"
#include "BlackBoxPlayerController.generated.h"

UCLASS()
class ABlackBoxPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABlackBoxPlayerController(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
};


