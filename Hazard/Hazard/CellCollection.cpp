#include "stdafx.h"
#include <vector>
#include <iostream>
#include "Cell.h"
#include "CellCollection.h"

using namespace std;

extern uint dimension;			// number of variables
extern uint numElements;		// number of Cells/possible numbers

/// <summary>
/// Add a Cell to the collection
/// </summary>
void CellCollection::add(Cell* &cell)
{
	this->cells.push_back(cell);
}

/// <summary>
/// Creates all Cells that exist with the specified number of variables
/// </summary>
void CellCollection::init()
{
	this->cells.resize(numElements);

	for (uint i = 0; i < numElements; i++)
		this->cells[i] = new Cell(i, this->globalPIC);
}

/// <summary>
/// <para>The hazard detection algorithm</para>
/// <para>We look at every second Cell and if this Cell's value is true (DNF) we asksits neighbors whether there is a PrimImplikant that covers both Cells. If not, we have found a hazard and can create a PrimImplikant that solves it.
/// </summary>
void CellCollection::findHazards()
{
	for (uint i = 0; i < numElements; i += 2)				// only every 2nd Cell because hazards are checked on all sides of the Cell
	{
		uint I = i ^ (i/2);									// transform to gray code --> Schachbrettmuster
		Cell* currentCell = cells[I];						// this is the cell we are currently checking

		if (currentCell->value == false)					// no hazard can occur because no PrimImplikant covers this Cell
			continue;

		cout << "   Checking cell " << I << endl;
		vector<Cell*>* hazardousNeighbors = currentCell->getHazards(this->cells);	// get neighbor Cells with hazards

		if (hazardousNeighbors->size() == 0)				// no hazard was found
		{
			delete hazardousNeighbors;
			continue;
		}

		for (CellIt nc = hazardousNeighbors->begin(); nc < hazardousNeighbors->end(); nc++) // foreach neighbor Cell with hazard
		{
			printf("Hazard found! Cell %d <--> Cell %d\n", I, (*nc)->index);
			this->globalPIC->add(I, (*nc)->index);			// add PI that solves hazard. Not quite smart...
			(*nc)->refresh(this->globalPIC);				// refresh the foreign PIC (a PI was added)
			this->hazardsFound = true;
		}
		currentCell->refresh(this->globalPIC);				// refresh the current PIC (a PI was added)
		delete hazardousNeighbors;
	}
}



/// <summary>
/// Deletes all Cell instances in this collection
/// <para>Beware: Only do this at the end! All collections are storing pointers to the Cells and maybe some other object is still using them. Dispose() may only be called by the last instance of this class (which we could check programmatically and then integrate it into the destructor)</para>
/// </summary>
void CellCollection::Dispose()
{
	for (CellIt i = this->cells.begin(); i < this->cells.end(); i++)
		delete (*i);
	this->cells.clear();
}



/// <summary>
/// Returns the number of Cells in this Collection
/// </summary>
uint CellCollection::size()
{
	return cells.size();
}

/// <summary>
/// Returns the last Cell in here
/// </summary>
Cell* CellCollection::back()
{
	return cells.back();
}

/// <summary>
/// Returns the first Cell in here
/// </summary>
Cell* CellCollection::front()
{
	return cells.front();
}

/// <summary>
/// Returns the Cell at the specified index
/// </summary>
Cell* CellCollection::at(const uint index)
{
	return cells.at(index);
}
/// <summary>
/// Returns the Cell at the specified index
/// </summary>
Cell * CellCollection::operator[](const uint &index)
{
	return cells.at(index);
}