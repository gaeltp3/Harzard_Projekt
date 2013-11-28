#include <string>
#include <vector>
#include "PrimImplikantCollection.h"
#include "typedef.h"

using namespace std;

#ifndef CELL
#define CELL

class Cell {
public:
	bool value;
	unsigned int index;

	vector<Cell*>* getNeighbors(vector<Cell*> &allCells);			// returns numElements Cells
	vector<Cell*>* getHazards(vector<Cell*> &allCells);				// returns the neighbor Cells which are hazardous
	bool hasOneOfThose(PrimImplikantCollection &foreignPIC);
	void refresh(PrimImplikantCollection* &globalPIC);				// refreshes the local primImplikantCollection

	Cell(unsigned int index, PrimImplikantCollection* &globalPIC)
	{
		this->index = index;
		this->refresh(globalPIC);
		this->value = this->primImplikanten.size() > 0;
	}

	PrimImplikantCollection primImplikanten;
};

#endif