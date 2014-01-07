#include "stdafx.h"
#include <string>
#include <vector>
#include "PrimImplikantCollection.h"
#include "Cell.h"

using namespace std;

extern uint dimension;
extern bool KNF;

void Cell::refresh(PrimImplikantCollection* &globalPIC)
{
	this->primImplikanten = globalPIC->primImplikantenAt(index);
}

vector<Cell*>* Cell::getNeighbors(vector<Cell*> &allCells)
{
	vector<Cell*>* neighbors = new vector<Cell*>();

	uint j = 1;
	for (unsigned char i = 0; i < dimension; i++)
	{
		neighbors->push_back(allCells[this->index ^ j]);
		j <<= 1;
	}
	
	return neighbors;
}

vector<Cell*>* Cell::getHazards(vector<Cell*> &allCells)
{
	vector<Cell*>* hazardous = new vector<Cell*>();
	vector<Cell*>* neighbors = this->getNeighbors(allCells);

	for (vector<Cell*>::iterator neighbor = neighbors->begin(); neighbor < neighbors->end(); neighbor++)
	{
		
			if ((*neighbor)->value == KNF)
				continue;
			if ((*neighbor)->hasOneOfThose(this->primImplikanten) == false)
				hazardous->push_back(*neighbor);
		
	}

	delete neighbors;
	return hazardous;
}

bool Cell::hasOneOfThose(PrimImplikantCollection &foreignPic)
{
	for (uint i = 0; i < foreignPic.size(); i++)
		if (this->primImplikanten.contains(foreignPic[i]))
			return true;
	return false;
}