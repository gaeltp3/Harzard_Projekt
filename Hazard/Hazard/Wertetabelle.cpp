#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "Cell.h"
#include "PrimImplikant.h"
#include "Wertetabelle.h"

using namespace std;

extern uint dimension;
extern uint numElements;
extern bool KNF;

/// <summary>
/// Prints the complete truth table
/// </summary>
void Wertetabelle::Print()
{
	this->makeHeader();

	this->printHeader();										// print the header lines

	ushort w = (ushort)ceil(log10((float)numElements));			// calculate width of decimal maximum number

	for (uint i = 0; i < numElements; i++)
	{
		cout << "| ";											//	=> |
		cout << setfill(' ') << setw(w) << i;					//	=>    5
		cout << " |";											//	=>      |
		*fot << "| ";
		*fot << setfill(' ') << setw(w) << i;
		*fot << " |";
		this->printI(i);										//	=>        0  1  0 1
		cout << "| ";											//	=>                   |
		cout << ((*this->cells)[i]->value ^ KNF);				//	=>                     1
		cout << " |";											//	=>                       |
		*fot << "| ";
		*fot << ((*this->cells)[i]->value ^ KNF);
		*fot << " |";
		this->printPrimImplikanten(i);							//	=>                         0 x01 5|3
		cout << endl;											// ==> |  5 | 0  1  0 1  | 1 | 0 x01 5|3
		*fot << endl;

		if (i > 0 && i % 31 == 0 && numElements - i > 5)		// reprint header so you do not have to scroll
			this->printHeader();
	}

	cout << string(this->width, '-') << endl;
	*fot << string(this->width, '-') << endl;
}

/// <summary>
/// Generates the header line of the truth table with the variable names
/// </summary>
void Wertetabelle::makeHeader()
{
	ushort w = (ushort)ceil(log10((float)numElements));	// calculate width of decimal maximum number
	this->header = "|" + string(w + 2, ' ') + "|";		// spare out line number

	for (vector<string>::iterator v = variables->begin(); v < variables->end(); v++)	// for each variable
	{
		this->header += " " + *v;						// add variable name to string
		padding.push_back((v->size()-1) / 2.0f);		// calculate the padding (spaces left & right) depending on string length
	}
	
	this->header += " | y |";							// output variable

	this->width = this->header.size();					// set global with of truth table (for horizontal lines)

	this->header += " PrimImplikanten";					// add header for PIs
}

/// <summary>
/// Print the header lines
/// </summary>
void Wertetabelle::printHeader()
{	
	cout << string(this->width, '-') << endl;	// repeat '-' several times	=> ---------------------
	cout << this->header << endl;				// print header row			=> | a bärchen c d | y | PrimtImpl.
	cout << string(this->width, '-') << endl;	// repeat '-' several times	=> ---------------------
	
	*fot << string(this->width, '-') << endl;
	*fot << this->header << endl;
	*fot << string(this->width, '-') << endl;
}

/// <summary>
/// <para>Print the binary repesentation of i</para>
/// <para>This method also takes care of the padding around the single bits (depending on the length of their variable names)</para>
/// </summary>
void Wertetabelle::printI(uint i)
{
	string row = " ";
	for (int j = dimension - 1; j >= 0; j--)			// iterate variables backwards for shifting i rightwards
	{
		char iAtJ = (i & 0x1) + '0';					// masking current bit (position j is being printed) and converting to char
		i >>= 1;										// Shift right for next round

		//		' ' + Padding left (' ')			+ 1 | 0 +     Padding right (' ')	 + row
		row = string((uint)ceil(padding[j]) + 1, ' ') + iAtJ + string((uint)floor(padding[j]), ' ') + row;
	}

	cout << row;
	*fot << row;
}

/// <summary>
/// Prints the names of all PrimImplikants at the current position
/// </summary>
void Wertetabelle::printPrimImplikanten(uint i)
{
	Cell* cell = cells->at(i);										// get current Cell

	for (uint pi = 0; pi < cell->primImplikanten.size(); pi++)		// for each PrimImplikant in Cell
	{
		cout << ' ' << cell->primImplikanten[pi]->name;				// print name
		*fot << ' ' << cell->primImplikanten[pi]->name;	
	}
}