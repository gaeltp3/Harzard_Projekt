#pragma once

#include "stdafx.h"
#include <vector>
#include <string>
#include <fstream>
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

	Wertetabelle(CellCollection* cells, vector<string>* variables, ofstream &fWt)
	{
		this->cells = cells;
		this->variables = variables;
		this->fot = &fWt;
	}

private:
	string makeHeader();
	void printHeader();
	void printI(uint i);
	void printPrimImplikanten(uint i);

	CellCollection* cells;
	vector<string>* variables;
	vector<float> padding;
	uint width;
	ofstream* fot;
};

#endif