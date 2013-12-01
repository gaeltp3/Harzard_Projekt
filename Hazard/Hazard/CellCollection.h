#pragma once

#include "stdafx.h"
#include "Cell.h"
#include "CellCollection.h"

using namespace std;

#ifndef _CELLCOLLEC_H
#define _CELLCOLLEC_H


class CellCollection {
public:
	void add(Cell* &cell);
	void init(PrimImplikantCollection* &globalPIC);
	void findHazards();

	void Dispose();

	uint size();
	Cell* back();
	Cell* front();
	Cell* at(uint index);
	Cell* operator[](uint &index);

	CellCollection(PrimImplikantCollection* &globalPIC)
	{
		this->init(globalPIC);
	};


	vector<Cell*> cells;
	PrimImplikantCollection* globalPIC;
};

#endif