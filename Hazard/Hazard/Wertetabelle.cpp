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

void Wertetabelle::Print()
{
	printHeader();

	for (uint i = 0; i < numElements; i++)
	{
		cout << "| ";																//	=> |
		cout << setfill(' ') << setw((uint)ceil(log10((float)numElements))) << i;	//	=>    4
		cout << " |";																//	=>      |
		*fot << "| ";																//	=> |
		*fot << setfill(' ') << setw((uint)ceil(log10((float)numElements))) << i;	//	=>    4
		*fot << " |";																//	=>      |
		this->printI(i);															//	=>        0  1  0 0
		cout << "| ";																//	=>                   |
		cout << ((*this->cells)[i]->value ^ KNF);									//	=>                     1
		cout << " |";																//	=>                       |
		*fot << "| ";																//	=>                   |
		*fot << ((*this->cells)[i]->value ^ KNF);									//	=>                     1
		*fot << " |";																//	=>                       |
		this->printPrimImplikanten(i);												//	=>                         0 0x1 4
		cout << endl;																// ==> |  4 | 0  1  0 0  | 1 | 0 0x1 4
		*fot << endl;																// ==> |  4 | 0  1  0 0  | 1 | 0 0x1 4

		this->printI(i);															//	=>        0  1  0 0
		this->printPrimImplikanten(i);												//	=>                         0 0x1 4

		if (i > 0 && i % 31 == 0 && numElements - i > 5)		// reprint header so you dont have to scroll
			//cout << this->makeHeader() << endl;
			printHeader();
	}

	cout << string(this->width, '-') << endl;
	*fot << string(this->width, '-') << endl;
}

string Wertetabelle::makeHeader()
{
	bool setPad = padding.size() == 0;

	string row2 = "|" + string((uint)ceil(log10((float)numElements)) + 2, ' ') + "|";
	for (vector<string>::iterator v = variables->begin(); v < variables->end(); v++)
	{
		row2 += " " + *v;
		if (setPad)
			padding.push_back((v->size()-1) / 2.0f);
	}
	
	row2 += " | y |";

	this->width = row2.size();

	row2 += " PrimImplikanten";

	return row2;
}

void Wertetabelle::printHeader()
{
	string row2 = this->makeHeader();
	
	cout << string(this->width, '-') << endl;	// repeat '-' several times	=> ---------------------
	cout << row2 << endl;						// print header row			=> | a bärchen c d | y | PrimtImpl.
	cout << string(this->width, '-') << endl;	// repeat '-' several times	=> ---------------------
	
	*fot << string(this->width, '-') << endl;	// repeat '-' several times	=> ---------------------
	*fot << row2 << endl;						// print header row			=> | a bärchen c d | y | PrimtImpl.
	*fot << string(this->width, '-') << endl;	// repeat '-' several times	=> ---------------------
}

void Wertetabelle::printI(uint i)
{
	string row = " ";
	for (int j = dimension - 1; j >= 0; j--)			// Variablen rückwärts durchlaufen (s.u.)
	{
		char iAtJ = (i & 0x1) + '0';					// Maskierung (aktuelle Stelle j, die ausgegeben wird)
		i >>= 1;										// Schieben für nächstes Mal
		//		' ' + Padding left (' ')				+ 1 | 0 +     Padding right (' ')	 + row
		row = string((uint)ceil(padding[j]) + 1, ' ') + iAtJ + string((uint)floor(padding[j]), ' ') + row;
	}
	cout << row;
	*fot << row;
}

void Wertetabelle::printPrimImplikanten(uint i)
{
	cout << ' ';
	*fot << ' ';
	Cell* cell = cells->at(i);

	for (uint pi = 0; pi < cell->primImplikanten.size(); pi++)		// for every PrimImplikant in Cell
	{
		cout << cell->primImplikanten[pi]->name << " ";	
		*fot << cell->primImplikanten[pi]->name << " ";	
	}
}