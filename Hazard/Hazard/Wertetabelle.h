#pragma once

#include "stdafx.h"
#include <vector>
#include <string>
#include <fstream>
#include "PrimImplikant.h"
#include "Cell.h"
#include "CellCollection.h"

using namespace std;

/// <summary>
/// This class is responsible for the printing of truth tables to cout and the output file
/// </summary>
class Wertetabelle
{
public:
	void Print();							// print the complete truth table

	/// <summary>
	/// Constructor of Wertetabelle
	/// </summary>
	Wertetabelle(CellCollection* cells, vector<string>* variables, ofstream &fWt)
	{
		this->cells = cells;				// store a reference to allCells (thus we will get all changes)
		this->variables = variables;
		this->fot = &fWt;
	}

private:
	void makeHeader();						// Generates the header lines
	void printHeader();						// Prints the header lines
	void printI(uint i);					// Prints the binary representation of the specified i in table format
	void printPrimImplikanten(uint i);		// Print all PrimImplikants that cover the specified position i

	CellCollection* cells;					// all cells
	vector<string>* variables;				// variable names
	vector<float> padding;					// padding depending on length of variable names
	uint width;								// with of truth table
	ofstream* fot;							// output file stream
	string header;							// header line
};