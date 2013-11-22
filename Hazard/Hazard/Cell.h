#include <string>
#include <vector>
#include "PrimImplikantCollection.h"

using namespace std;

#ifndef CELL
#define CELL

class Cell {
public:
	bool value;
	unsigned int index;

	vector<Cell*> GetNeighbors();			// returns numElements Cells
	vector<Cell*> GetHazards();				// returns the neighbor Cells which are hazardous

    Cell(unsigned int index, PrimImplikantCollection* &globalPIC)
	{
		this->index = index;
		this->primImplikanten = globalPIC->primImplikantenAt(index);
		this->value = this->primImplikanten.size() > 0;
	}

private:
	PrimImplikantCollection primImplikanten;
};

#endif