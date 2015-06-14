// Copyright (c) 2015 Mateus Bezerra

#include "LastResort.h"
#include "Tabuleiro.h"
#include "BlackBoxInitializer.h"


void ABlackBoxInitializer::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetWorld() != nullptr) {

		ATabuleiro* Tabuleiro = GetWorld()->SpawnActor<ATabuleiro>(FVector(-130, -80, 280), FRotator::ZeroRotator);
		if (Tabuleiro != nullptr)
		{
			//GetWorld()->GetLevel(0)->Actors.Add(Tabuleiro);
		}
	}
}


