#include "stdafx.h"
#include <string>
#include <vector>
#include "PrimImplikant.h"

using namespace std;

extern uint dimension;
extern uint numElements;
extern bool KNF;

#ifndef IMPLIKANT_LOC
#define IMPLIKANT_LOC


class Implikant_localisation{

private:
	void setElement(uint &currentI)
	{
		uint numVarX = (uint)floor(dimension / 2.0f);
		
		this->i = currentI;
		this->w = (currentI & ((0x1 << (numVarX)) - 1)) ^ ((currentI & ((0x1 << (numVarX)) - 1)) / 2); //   w^=w/2 
		this->h = (currentI >> numVarX) ^ ((currentI >> numVarX) / 2); 
	}

public:
	uint i;
	uint w;
	uint h;

	Implikant_localisation(uint &currentI)
	{
		setElement(currentI);
	}
};

#endif;
