#pragma once

#include <string>
#include <vector>
#include "PrimImplikantCollection.h"

using namespace std;


class Cell {
public:
	bool value;														// DNF value
	unsigned int index;												// position of this Cell

	vector<Cell*>* getNeighbors(vector<Cell*> &allCells);			// returns all Cells which's Hamming distance 1
	vector<Cell*>* getHazards(vector<Cell*> &allCells);				// returns the neighbor Cells which are hazardous
	bool hasOneOfThose(PrimImplikantCollection &foreignPIC);		// returns whether this Cell is covered by a PrimImplikant of the specified foreignPIC
	void refresh(PrimImplikantCollection* &globalPIC);				// refreshes the local primImplikantCollection from globalPIC

	/// <summary>
	/// Constructor of Cell
	/// </summary>
	Cell(uint index, PrimImplikantCollection* &globalPIC)
	{
		this->index = index;
		this->refresh(globalPIC);
		this->value = this->primImplikanten.size() > 0;				// if a PrimImplikant covers this Cell, it is true in DNF
	}

	PrimImplikantCollection primImplikanten;						// all PrimImplikants that cover this Cell
};

#ifndef CELLITERATOR
#define CELLITERATOR
typedef vector<Cell*>::iterator CellIt;
#endif