#include <string>
#include <vector>
#include "PrimImplikantCollection.h"

using namespace std;

#ifndef CELL
#define CELL

class Cell {
public:
	bool value;

	vector<Cell> GetNeighbours();
	bool HasHazard();

	Cell(int index, PrimImplikantCollection* &globalPIC)
	{
		this->index = index;
		this->primImplikanten = globalPIC->primImplikantenAt(index);
		this->value = this->primImplikanten.size() > 0;
	}

private:
	PrimImplikantCollection primImplikanten;
	int index;
};

#endif