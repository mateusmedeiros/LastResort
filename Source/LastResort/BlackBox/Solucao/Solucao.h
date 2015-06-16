// Copyright (c) 2015 Mateus Bezerra

#pragma once
#include "LastResort.h"
#include <LastResort/BlackBox/Tabuleiro.h>
#include "AtomoSolucao.h"
#include "LaserSolucao.h"

/**
 * 
 */
struct LASTRESORT_API FSolucao
{
		// EditAnywhere,BlueprintReadWrite,Category("your category")

	TArray< FAtomoSolucao > Atomos;

	TArray< FLaserSolucao > LasersCima;

	TArray< FLaserSolucao > LasersDireita;

	TArray< FLaserSolucao > LasersBaixo;

	TArray< FLaserSolucao > LasersEsquerda;

	int32 Tamanho;

	int32 NumeroAtomosExistentes;
		
	FSolucao(ATabuleiro* Tabuleiro);
	FSolucao(ATabuleiro* Tabuleiro, int32 NumeroAtomosExistentes);

	void CriarNovaSolucao(int32 NumeroAtomosExistentes);
	void CriarLasers();
	bool AtomoNaoVisitado();
	int32 VizinhoAleatorioNaoVisitadoOuMenos1(int32 X, int32 Y);

	FLaserSolucao* GetLaserIndexHelper(int32 Index);
	ELaserLado LadoContrario(ELaserLado Lado);
	FAtomoSolucao** GetAtomosIniciaisLaser(FLaserSolucao& Laser, FAtomoSolucao** ArrayAtomo);
	FAtomoSolucao** GetAtomosSeguintesLaser(ELaserLado Direcao, FAtomoSolucao& AtomoAtual, FAtomoSolucao** ArrayAtomo);
	FAtomoSolucao* GetAtomo(int32 X, int32 Y);
};
