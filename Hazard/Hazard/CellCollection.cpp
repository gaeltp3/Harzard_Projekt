#include "stdafx.h"
#include <vector>
#include <iostream>
#include "Cell.h"
#include "CellCollection.h"

using namespace std;

extern uint dimension;
extern uint numElements;

void CellCollection::add(Cell* &cell)
{
	this->cells.push_back(cell);
}

void CellCollection::init(PrimImplikantCollection* &globalPIC)
{
	this->globalPIC = globalPIC;
	this->cells.resize(numElements);

	for (uint i = 0; i < numElements; i++)
		this->cells[i] = new Cell(i, globalPIC);
}

void CellCollection::findHazards()
{
	for (uint i = 0; i < numElements; i += 2)				// we only need to check every 2nd as long as it's gray
	{
		uint I = i ^ (i/2);									// transform to gray code --> Schachbrettmuster
		Cell* currentCell = cells[I];						// this is the cell we are currently checking

		if (currentCell->value == KNF)					// no hazard can occur
			continue;

		cout << "   Checking cell " << I << endl;
		vector<Cell*>* hazardousNeighbors = currentCell->getHazards(this->cells);

		if (hazardousNeighbors->size() == 0)				// no hazard found
		{
			delete hazardousNeighbors;
			continue;
		}

		for (vector<Cell*>::iterator nc = hazardousNeighbors->begin(); nc < hazardousNeighbors->end(); nc++)
		{
			printf("Hazard found! Cell %d <--> Cell %d\n", I, (*nc)->index);
			this->globalPIC->add(I, (*nc)->index);			// add PI that solves hazard. Not quite smart...
			(*nc)->refresh(this->globalPIC);				// refresh the foreign PIC (a PI was added)
		}
		currentCell->refresh(this->globalPIC);				// refresh the current PIC (a PI was added)
		delete hazardousNeighbors;
	}
}



void CellCollection::Dispose()
{
	for (uint i = 0; i < this->cells.size(); i++)
		delete cells[i];
}



uint CellCollection::size()
{
	return cells.size();
}

Cell* CellCollection::back()
{
	return cells.back();
}

Cell* CellCollection::front()
{
	return cells.front();
}

Cell* CellCollection::at(uint index)
{
	return cells.at(index);
}

Cell * CellCollection::operator[](uint &index)
{
	return cells.at(index);
}