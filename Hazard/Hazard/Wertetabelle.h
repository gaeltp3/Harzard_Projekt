#pragma once

#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include "PrimImplikant.h"
#include "Cell.h"
#include "CellCollection.h"

using namespace std;

#ifndef WERTETABELLE
#define WERTETABELLE

class Wertetabelle
{
public:
	void Print();

	Wertetabelle(CellCollection* cells, vector<string>* variables)
	{
		this->cells = cells;
		this->variables = variables;
	}

private:
	string makeHeader();
	void printHeader();
	void printI(unsigned int i);
	void printPrimImplikanten(unsigned int i);

	CellCollection* cells;
	vector<string>* variables;
	vector<float> padding;
	uint width;
};

#endif