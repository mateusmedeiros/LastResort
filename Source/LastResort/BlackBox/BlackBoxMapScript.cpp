// Copyright (c) 2015 Mateus Bezerra

#include "LastResort.h"
#include "Tabuleiro.h"
#include "BlackBoxMapScript.h"

void ABlackBoxMapScript::BeginPlay()
{
	Super::BeginPlay();

	/*
	if (GetWorld() != nullptr) {
		
		ATabuleiro* Tabuleiro = GetWorld()->SpawnActor<ATabuleiro>(FVector(-340, 0, 40), FRotator::ZeroRotator);
		if (Tabuleiro != nullptr)
		{
			//VSCREENMSG(TEXT("C"));
			GetWorld()->GetLevel(0)->Actors.Add(Tabuleiro);
		}
	}
	*/

	//this->SetViewTarget(Cast<AActor>(Camera));
}
