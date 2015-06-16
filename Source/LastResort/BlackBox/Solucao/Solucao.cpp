// Copyright (c) 2015 Mateus Bezerra

#include "LastResort.h"
#include <LastResort/BlackBox/Tabuleiro.h>
#include "Solucao.h"
#include "LaserSolucao.h"

FSolucao::FSolucao(ATabuleiro* Tabuleiro)
{
	this->Tamanho = Tabuleiro->Tamanho;

	for (int32 i = 0; i < Tabuleiro->Tamanho; i++)
	{
		FLaserSolucao Laser;
		Laser.Indice = i;
		Laser.Estado = ELaserEstado::NENHUM;
		Laser.Lado = CIMA;
		this->LasersCima.Add(Laser);
	}

	for (int32 i = 0; i < Tabuleiro->Tamanho; i++)
	{
		FLaserSolucao Laser;
		Laser.Indice = i;
		Laser.Estado = ELaserEstado::NENHUM;
		Laser.Lado = DIREITA;
		this->LasersDireita.Add(Laser);
	}

	for (int32 i = 0; i < Tabuleiro->Tamanho; i++)
	{
		FLaserSolucao Laser;
		Laser.Indice = i;
		Laser.Estado = ELaserEstado::NENHUM;
		Laser.Lado = BAIXO;
		this->LasersBaixo.Add(Laser);
	}

	for (int32 i = 0; i < Tabuleiro->Tamanho; i++)
	{
		FLaserSolucao Laser;
		Laser.Indice = i;
		Laser.Estado = ELaserEstado::NENHUM;
		Laser.Lado = ESQUERDA;
		this->LasersEsquerda.Add(Laser);
	}

	for (int32 i = 0; i < (Tabuleiro->Tamanho * Tabuleiro->Tamanho); i++)
	{
		FAtomoSolucao Atomo(i % Tabuleiro->Tamanho, i / Tabuleiro->Tamanho);
		Atomo.Existe = Tabuleiro->GetAtomo(i % Tabuleiro->Tamanho, i / Tabuleiro->Tamanho)->Ativo;
		this->Atomos.Add(Atomo);
	}

	this->CriarLasers();
}

FSolucao::FSolucao(ATabuleiro* Tabuleiro, int32 NumeroAtomosExistentes)
{
	this->Tamanho = Tabuleiro->Tamanho;

	for (int32 i = 0; i < Tabuleiro->Tamanho; i++)
	{
		FLaserSolucao Laser;
		Laser.Indice = i;
		Laser.Estado = ELaserEstado::NENHUM;
		Laser.Lado = CIMA;
		this->LasersCima.Add(Laser);
	}

	for (int32 i = 0; i < Tabuleiro->Tamanho; i++)
	{
		FLaserSolucao Laser;
		Laser.Indice = i;
		Laser.Estado = ELaserEstado::NENHUM;
		Laser.Lado = DIREITA;
		this->LasersDireita.Add(Laser);
	}

	for (int32 i = 0; i < Tabuleiro->Tamanho; i++)
	{
		FLaserSolucao Laser;
		Laser.Indice = i;
		Laser.Estado = ELaserEstado::NENHUM;
		Laser.Lado = BAIXO;
		this->LasersBaixo.Add(Laser);
	}

	for (int32 i = 0; i < Tabuleiro->Tamanho; i++)
	{
		FLaserSolucao Laser;
		Laser.Indice = i;
		Laser.Estado = ELaserEstado::NENHUM;
		Laser.Lado = ESQUERDA;
		this->LasersEsquerda.Add(Laser);
	}

	for (int32 i = 0; i < (Tabuleiro->Tamanho * Tabuleiro->Tamanho); i++)
	{
		this->Atomos.Add(FAtomoSolucao(i % Tabuleiro->Tamanho, i / Tabuleiro->Tamanho));
	}

	this->CriarNovaSolucao(NumeroAtomosExistentes);
	//this->CriarLasers();
}

void FSolucao::CriarNovaSolucao(int32 NumeroAtomosExistentes)
{
	//NumeroAtomosExistentes
	while (true)
	{
		int32 r = FMath::RandRange(0, this->Atomos.Num());
		if (this->Atomos[r].Existe)
		{
			continue;
		}
		else
		{
			this->Atomos[r].Existe = true;
			if (!(--NumeroAtomosExistentes))
			{
				break;
			}
		}
	}
	
	/*
	TLockFreePointerList<int32> Stack;
	TQueue<bool> FilaEscolhas{};
	TArray<int32> Escolhidos{};

	for (int32 i = 0; i < NumeroAtomosExistentes; i++)
	{
		int32 r = FMath::RandRange(0, (Tamanho * Tamanho) - 1);
		while (Escolhidos.Contains(r)) {
			r = FMath::RandRange(0, (Tamanho * Tamanho) - 1);
		}
		Escolhidos.AddUnique(r);
	}

	for (int32 i = 0; i < (Tamanho * Tamanho); i++)
	{
		if (Escolhidos.Contains(i))
		{
			FilaEscolhas.Enqueue(true);
		} else
		{
			FilaEscolhas.Enqueue(false);
		}
	}

	int32 IndiceInicial = FMath::RandRange(0, (Tamanho * Tamanho) - 1);

	int32 i = IndiceInicial;
	int32 Vizinho;
	while (true)
	{
		if (!Atomos[i].Visitado)
		{
			bool Existira;
			FilaEscolhas.Dequeue(Existira);
			Atomos[i].Existe = Existira;
			Stack.Push(&i);
			Atomos[i].Visitado = true;
		}

		if (!this->AtomoNaoVisitado())
		{
			break;
		}

		Vizinho = this->VizinhoAleatorioNaoVisitadoOuMenos1(Atomos[i].X, Atomos[i].Y);

		if (Vizinho == -1)
		{
			i = *(Stack.Pop());
		} else
		{
			i = Vizinho;
		}
	}
	*/
}

void FSolucao::CriarLasers()
{
	// LasersCima
	// LasersDireita
	// LasersBaixo
	// LasersEsquerda
	FAtomoSolucao* AtomoAnterior = nullptr;
	FAtomoSolucao* Atomos[3];
	FLaserSolucao* Laser;
	ELaserLado Direcao;
	int32 IteradorLaser = 0;

	for (int32 i = 0; i < this->Tamanho * 4; i++)
	{
		Laser = GetLaserIndexHelper(i);
		Direcao = LadoContrario(Laser->Lado);
		GetAtomosIniciaisLaser(*Laser, Atomos);

		if ((Atomos[0] != nullptr && Atomos[0]->Existe) || (Atomos[2] != nullptr && Atomos[2]->Existe))
		{
			Laser->Estado = ELaserEstado::R;
			continue;
		}

		while (Atomos[1] != nullptr)
		{
			if (Atomos[1]->Existe)
			{
				Laser->Estado = ELaserEstado::H;
				goto ContinueLaserLoop;
			} 
			else if ((Atomos[0] != nullptr && Atomos[0]->Existe) && (Atomos[2] != nullptr && Atomos[2]->Existe))
			{
				Laser->Estado = ELaserEstado::R;
				goto ContinueLaserLoop;
			} 
			else if ((Atomos[0] != nullptr && Atomos[0]->Existe))
			{
				if (Direcao == ESQUERDA)
				{
					Direcao = CIMA;
				}
				else
				{
					Direcao = static_cast<ELaserLado>(static_cast<int32>(Direcao) + 1);
				}
			} 
			else if ((Atomos[2] != nullptr && Atomos[2]->Existe))
			{
				if (Direcao == CIMA)
				{
					Direcao = ESQUERDA;
				}
				else
				{
					Direcao = static_cast<ELaserLado>(static_cast<int32>(Direcao)-1);
				}
			}

			AtomoAnterior = Atomos[1];
			GetAtomosSeguintesLaser(Direcao, *Atomos[1], Atomos);
		}

		int IL = ++IteradorLaser;
		
		ELaserLado Lado = LadoContrario(Direcao);
		switch (Lado)
		{
		case CIMA:
			this->LasersCima[AtomoAnterior->X].Estado = ELaserEstado::NUMERO;
			this->LasersCima[AtomoAnterior->X].Numero = IL;
			Laser->Estado = ELaserEstado::NUMERO;
			Laser->Numero = IL;
			break;

		case DIREITA:
			this->LasersDireita[AtomoAnterior->Y].Estado = ELaserEstado::NUMERO;
			this->LasersDireita[AtomoAnterior->Y].Numero = IL;
			Laser->Estado = ELaserEstado::NUMERO;
			Laser->Numero = IL;
			break;

		case BAIXO:
			this->LasersBaixo[(this->Tamanho - 1) - AtomoAnterior->X].Estado = ELaserEstado::NUMERO;
			this->LasersBaixo[(this->Tamanho - 1) - AtomoAnterior->X].Numero = IL;
			Laser->Estado = ELaserEstado::NUMERO;
			Laser->Numero = IL;
			break;

		case ESQUERDA:
			this->LasersEsquerda[(this->Tamanho - 1) - AtomoAnterior->Y].Estado = ELaserEstado::NUMERO;
			this->LasersEsquerda[(this->Tamanho - 1) - AtomoAnterior->Y].Numero = IL;
			Laser->Estado = ELaserEstado::NUMERO;
			Laser->Numero = IL;
			break;
		}

		// LABEL
		ContinueLaserLoop:
		continue;
	}

}



FLaserSolucao* FSolucao::GetLaserIndexHelper(int32 Index)
{
	switch (Index / this->Tamanho)
	{
	case CIMA:
		return &(this->LasersCima[Index % this->Tamanho]);
	
	case DIREITA:
		return &(this->LasersDireita[Index % this->Tamanho]);

	case BAIXO:
		return &(this->LasersBaixo[Index % this->Tamanho]);

	case ESQUERDA:
		return &(this->LasersEsquerda[Index % this->Tamanho]);
	}

	return nullptr;
}

ELaserLado FSolucao::LadoContrario(ELaserLado Lado)
{
	switch (Lado)
	{
	case CIMA:
		return BAIXO;

	case DIREITA:
		return ESQUERDA;

	case BAIXO:
		return CIMA;

	case ESQUERDA:
		return DIREITA;
	}

	return Lado;
}


FAtomoSolucao** FSolucao::GetAtomosIniciaisLaser(FLaserSolucao& Laser, FAtomoSolucao** ArrayAtomo) 
{
	switch (Laser.Lado)
	{
	case CIMA:
		ArrayAtomo[0] = &(this->Atomos[1]);
		ArrayAtomo[1] = &(this->Atomos[0]);
		ArrayAtomo[2] = nullptr;
		break;

	case DIREITA:
		ArrayAtomo[0] = &(this->Atomos[this->Tamanho + (this->Tamanho - 1)]);
		ArrayAtomo[1] = &(this->Atomos[this->Tamanho - 1]);
		ArrayAtomo[2] = nullptr;
		break;

	case BAIXO:
		ArrayAtomo[0] = &(this->Atomos[(this->Tamanho * this->Tamanho) - 2]);
		ArrayAtomo[1] = &(this->Atomos[(this->Tamanho * this->Tamanho) - 1]);
		ArrayAtomo[2] = nullptr;
		break;

	case ESQUERDA:
		ArrayAtomo[0] = &(this->Atomos[this->Tamanho * (this->Tamanho - 2)]);
		ArrayAtomo[1] = &(this->Atomos[this->Tamanho * (this->Tamanho - 1)]);
		ArrayAtomo[2] = nullptr;
		break;
	}

	return ArrayAtomo;
}


FAtomoSolucao** FSolucao::GetAtomosSeguintesLaser(ELaserLado Direcao, FAtomoSolucao& AtomoAtual, FAtomoSolucao** ArrayAtomo)
{
	FAtomoSolucao* Atomo;
	switch (Direcao)
	{
	case CIMA:
		if (AtomoAtual.X - 1 < 0 || AtomoAtual.Y - 1 < 0)
		{
			Atomo = nullptr;
		} else
		{
			Atomo = this->GetAtomo(AtomoAtual.X - 1, AtomoAtual.Y - 1);
		}
		ArrayAtomo[0] = Atomo;

		if (AtomoAtual.Y - 1 < 0)
		{
			Atomo = nullptr;
		}
		else
		{
			Atomo = this->GetAtomo(AtomoAtual.X, AtomoAtual.Y - 1);
		}
		ArrayAtomo[1] = Atomo;

		if (AtomoAtual.X + 1 >= this->Tamanho || AtomoAtual.Y - 1 < 0)
		{
			Atomo = nullptr;
		}
		else
		{
			Atomo = this->GetAtomo(AtomoAtual.X + 1, AtomoAtual.Y - 1);
		}
		ArrayAtomo[2] = Atomo;
		break;

	case DIREITA:
		if (AtomoAtual.X + 1 >= this->Tamanho || AtomoAtual.Y - 1 < 0)
		{
			Atomo = nullptr;
		}
		else
		{
			Atomo = this->GetAtomo(AtomoAtual.X + 1, AtomoAtual.Y - 1);
		}
		ArrayAtomo[0] = Atomo;

		if (AtomoAtual.X + 1 >= this->Tamanho)
		{
			Atomo = nullptr;
		}
		else
		{
			Atomo = this->GetAtomo(AtomoAtual.X + 1, AtomoAtual.Y);
		}
		ArrayAtomo[1] = Atomo;

		if (AtomoAtual.X + 1 >= this->Tamanho || AtomoAtual.Y + 1 >= this->Tamanho)
		{
			Atomo = nullptr;
		}
		else
		{
			Atomo = this->GetAtomo(AtomoAtual.X + 1, AtomoAtual.Y + 1);
		}
		ArrayAtomo[2] = Atomo;
		break;

	case BAIXO:
		if (AtomoAtual.X + 1 >= this->Tamanho || AtomoAtual.Y + 1 >= this->Tamanho)
		{
			Atomo = nullptr;
		}
		else
		{
			Atomo = this->GetAtomo(AtomoAtual.X + 1, AtomoAtual.Y + 1);
		}
		ArrayAtomo[0] = Atomo;

		if (AtomoAtual.Y + 1 >= this->Tamanho)
		{
			Atomo = nullptr;
		}
		else
		{
			Atomo = this->GetAtomo(AtomoAtual.X, AtomoAtual.Y + 1);
		}
		ArrayAtomo[1] = Atomo;

		if (AtomoAtual.X - 1 < 0 || AtomoAtual.Y + 1 >= this->Tamanho)
		{
			Atomo = nullptr;
		}
		else
		{
			Atomo = this->GetAtomo(AtomoAtual.X - 1, AtomoAtual.Y + 1);
		}
		ArrayAtomo[2] = Atomo;
		break;

	case ESQUERDA:
		if (AtomoAtual.X - 1 < 0 || AtomoAtual.Y + 1 >= this->Tamanho)
		{
			Atomo = nullptr;
		}
		else
		{
			Atomo = this->GetAtomo(AtomoAtual.X - 1, AtomoAtual.Y + 1);
		}
		ArrayAtomo[0] = Atomo;

		if (AtomoAtual.X - 1 < 0)
		{
			Atomo = nullptr;
		}
		else
		{
			Atomo = this->GetAtomo(AtomoAtual.X - 1, AtomoAtual.Y);
		}
		ArrayAtomo[1] = Atomo;

		if (AtomoAtual.X - 1 < 0 || AtomoAtual.Y - 1 < 0)
		{
			Atomo = nullptr;
		}
		else
		{
			Atomo = this->GetAtomo(AtomoAtual.X - 1, AtomoAtual.Y - 1);
		}
		ArrayAtomo[2] = Atomo;
		break;
	}

	return ArrayAtomo;
}


FAtomoSolucao* FSolucao::GetAtomo(int32 X, int32 Y) 
{
	return &(this->Atomos[X + (this->Tamanho * Y)]);
}
