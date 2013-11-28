#include <vector>
#include <string>
#include <iostream>
#include "Cell.h"
#include "PrimImplikant.h"
#include "Cell.h"
#include "typedef.h"

using namespace std;

#ifndef WERTETABELLE
#define WERTETABELLE

class Wertetabelle
{
public:
	void Print();

	Wertetabelle(vector<Cell*>* cells, vector<string>* variables)
	{
		this->cells = cells;
		this->variables = variables;
	}

private:
	string makeHeader();
	void printHeader();
	void printI(unsigned int i);
	void printPrimImplikanten(unsigned int i);

	vector<Cell*>* cells;
	vector<string>* variables;
	vector<float> padding;
	uint width;
};

#endif