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
	uint currentI;
	uint w;
	uint h;
	const uint numVarX;
	

public:
	void setElement(uint currentI){
		this->currentI = currentI;
		this->w = (currentI & ((0x1 << (this->numVarX)) - 1)) ^ ((currentI & ((0x1 << (this->numVarX)) - 1)) / 2); //   w^=w/2 
		this->h = (currentI >> this->numVarX) ^ ((currentI >> this->numVarX) / 2); 
	}
	
	Implikant_localisation(uint currentI) :numVarX(((uint)floor(dimension / 2.0f))){

		setElement(currentI);
	}
};

#endif;
