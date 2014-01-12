#pragma once

#include "stdafx.h"
#include "Cell.h"
#include "CellCollection.h"

using namespace std;


/// <summary>
/// <para>This class contains a number of Cells and provides some methods to operate on/with those</para>
/// </summary>
class CellCollection
{
private:
	void init();						// creates a CellCollection with numElements Cells and adds the associated PrimImplikants to each of those
public:
	void add(Cell* &cell);				// adds a Cell to this collection
	void findHazards();					// the hazard detection algorithm

	void Dispose();						// delete all referenced Cell objects

	uint size();						// the number of Cells in this collection
	Cell* back();						// the last Cell in here
	Cell* front();						// the first Cell in here
	Cell* at(const uint index);			// the Cell at the specified index
	Cell* operator[](const uint &index);// the Cell at the specified index

	/// <summary>
	/// Constructor of CellCollection
	/// </summary>
	CellCollection(PrimImplikantCollection* &globalPIC)
	{
		this->globalPIC = globalPIC;
		this->init();
		this->hazardsFound = false;
	};


	vector<Cell*> cells;				// vector with Cells
	PrimImplikantCollection* globalPIC;	// a reference to the global PrimImplikantCollection
	bool hazardsFound;					// whether findHazards() found hazards =)
};