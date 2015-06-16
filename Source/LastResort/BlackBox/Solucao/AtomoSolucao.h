// Copyright (c) 2015 Mateus Bezerra

#pragma once
#include "LastResort.h"
/**
*
*/
struct LASTRESORT_API FAtomoSolucao
{
	int32 X;

	int32 Y;

	bool Existe;

	bool Visitado;

	FAtomoSolucao(int32 X, int32 Y)
	{
		this->X = X;
		this->Y = Y;
		this->Existe = false;
		this->Visitado = false;
	}
};
