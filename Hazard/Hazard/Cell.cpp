#include "stdafx.h"
#include <string>
#include <vector>
#include "PrimImplikantCollection.h"
#include "Cell.h"

using namespace std;

extern uint dimension;		// number of variables

/// <summary>
/// Gets all PrimImplikants that cover this Cell from globalPIC
/// </summary>
void Cell::refresh(PrimImplikantCollection* &globalPIC)
{
	this->primImplikanten = globalPIC->primImplikantenAt(index);
}

/// <summary>
/// Gets all Cells that lie next to this Cell (Hamming distance = 1)
/// </summary>
/// <returns>A vector with Cells with size: dimension</returna>
vector<Cell*>* Cell::getNeighbors(vector<Cell*> &allCells)
{
	vector<Cell*>* neighbors = new vector<Cell*>();
	neighbors->resize(dimension);

	uint j = 1;
	for (unsigned char i = 0; i < dimension; i++)			// for all bits
	{
		neighbors->at(i) = allCells[this->index ^ j];			// add Cell that is different at one bit (j)
		j <<= 1;
	}
	
	return neighbors;
}

/// <summary>
/// Looks for hazards around this Cell
/// </summary>
/// <returns>A vector with those Cells that lie next to this Cell and to which a hazard may occur</returns>
vector<Cell*>* Cell::getHazards(vector<Cell*> &allCells)
{
	vector<Cell*>* hazardous = new vector<Cell*>();
	vector<Cell*>* neighbors = this->getNeighbors(allCells);

	for (vector<Cell*>::iterator neighbor = neighbors->begin(); neighbor < neighbors->end(); neighbor++)	// for each neighbor
	{
		if ((*neighbor)->value == false)		// if the neighbor is not covered by a PrimImpliaknt, no hazard can occur
			continue;
		if ((*neighbor)->hasOneOfThose(this->primImplikanten) == false)	// check whether at least one PrimImplikant that covers this Cell also covers the neighbor cell
			hazardous->push_back(*neighbor);							// if not, add it to hazardous
	}

	delete neighbors;
	return hazardous;
}

/// <summary>
/// Checks whether this Cell is covered by a PrimImplikant that is member of the specified PrimImplikantCollection (of another Cell)
/// </summary>
/// <returns>True: A PrimImplikant in foreignPic also covers this Cell</returns>
bool Cell::hasOneOfThose(PrimImplikantCollection &foreignPic)
{
	for (uint i = 0; i < foreignPic.size(); i++)				// for each foreign PrimImplikant
		if (this->primImplikanten.contains(foreignPic[i]))		// check whether it also covers this Cell
			return true;

	return false;
}