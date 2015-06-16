// Copyright (c) 2015 Mateus Bezerra

#include "LastResort.h"
#include "Algoritmos.h"

Algoritmos::Algoritmos()
{
}

Algoritmos::~Algoritmos()
{
}

int Algoritmos::doStuff()
{

	int32 a = 8;
	int32 b = 8;
	TArray<int32> IntArray;
	IntArray.SetNumUninitialized(8 * 8);



	return 0;
	

	/*
	get random laser
		make that laser the current cell and mark it as visited

		while there are unvisited cells
			random take off 1 - 9
			mark if lucky
			if the current cell has any neighbours which have not been visited
				choose randomly one of the unvisited neighbours
				Push the current cell to the stack
				Remove the wall between the current cell and the chosen cell
				Make the chosen cell the current cell and mark it as visited
				Else if stack is not empty
				Pop a cell from the stack
				Make it the current cell
				Else
				Pick a random unvisited cell, make it the current cell and mark it as visited
				*/



}

