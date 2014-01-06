#include "stdafx.h"
#include <string>
#include <algorithm>
#include <vector>
#include "PrimImplikant.h"

using namespace std;

extern uint dimension;
extern uint numElements;

bool PrimImplikant::valueAt(uint pos) {
	for (vector<uint>::iterator i = elements.begin(); i < elements.end(); ++i)
		if (*i == pos)
			return true;

	return false;
}

void PrimImplikant::parser(string input) {  // Analyser
	uint implikant = 0;
	string text0 = "";
	string text1 = "";
	for (uint i = 0; i < input.size(); i++)
	{
		char c = input[i];
		if (c == 'x' || c == 'X')
		{
			text0 = input;
			text1 = input;
			text0[i] = '0';
			text1[i] = '1';
			parser(text0);
			parser(text1);
			return;
		}
		if (c != '0' && c != '1')
		{
			printf("**** FATAL ERROR **** %s is not binary\n", input);
			return;
		}
		implikant <<= 1;	// *2
		implikant += (uint)c - (uint)'0';
	}

	elements.push_back(implikant);
}

void PrimImplikant::sort()
{
	std::sort(this->elements.begin(), this->elements.end(), &PrimImplikant::compareGray);
}

bool PrimImplikant::compareGray(uint a, uint b)
{
	for (uint i = 1; i < dimension; i++)
		a ^= a / 2;		// convert a from gray to binary
	for (uint i = 1; i < dimension; i++)
		b ^= b / 2;		// convert b from gray to binary
	return a < b;
}

void PrimImplikant::makeLocations()
{
	this->sort();
	this->_locations = new vector<KV_PiEleLoc*>();
	this->_locations->resize(this->elements.size());
	for (uint i = 0; i < this->elements.size(); i++)
		(*this->_locations)[i] = new KV_PiEleLoc(this->elements[i]);
}

vector<KV_PiEleLoc*>* PrimImplikant::locations()
{
	if (this->_locations == NULL)
		this->makeLocations();
	return this->_locations;
}