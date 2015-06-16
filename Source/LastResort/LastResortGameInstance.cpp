// Copyright (c) 2015 Mateus Bezerra

#include "LastResort.h"
#include "LastResortGameInstance.h"

const FDificuldadeStruct* FDificuldadeStruct::FACIL = new FDificuldadeStruct(220, 5);
const FDificuldadeStruct* FDificuldadeStruct::MEDIO = new FDificuldadeStruct(180, 5);
const FDificuldadeStruct* FDificuldadeStruct::DIFICIL = new FDificuldadeStruct(180, 6);

ULastResortGameInstance::ULastResortGameInstance()
{
	this->Dificuldade = *FDificuldadeStruct::MEDIO;
	this->PularInstrucoes = false;
}