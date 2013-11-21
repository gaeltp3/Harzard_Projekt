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

void Wertetabelle::Print()
{
	printHeader();

	for (uint i = 0; i < numElements; i++)
	{
		cout << "| ";													//	=> |
		cout << setfill(' ') << setw(ceil(log10((float)numElements))) << i;	//	=>    4
		cout << " |";													//	=>      |
		this->printI(i);												//	=>        0    1    0 0
		cout << "| ";													//	=>                      |
		cout << (*this->cells)[i]->value;								//	=>                        1
		cout << " |";													//	=>                          |
		this->printPrimImplikanten(i);									//	=>                            0 0x1 4
		cout << endl;

		if (i > 0 && i % 15 == 0 && numElements - i > 5)
			//cout << this->makeHeader() << endl;
			printHeader();
	}

	cout << string(this->width, '-');
}

string Wertetabelle::makeHeader()
{
	bool setPad = padding.size() == 0;

	string row2 = "|" + string(ceil(log10((float)numElements)) + 2, ' ') + "|";
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
}

void Wertetabelle::printPrimImplikanten(unsigned int i)
{
	cout << ' ';
	Cell* cell = cells->at(i);

	for (unsigned int pi = 0; pi < cell->primImplikanten.size(); pi++)		// for every PrimImplikant in Cell
		cout << cell->primImplikanten[pi]->name << " ";	
}