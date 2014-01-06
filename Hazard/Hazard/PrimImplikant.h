#pragma once

#include <string>
#include <vector>
#include "KV_PiEleLoc.h"

using namespace std;

class PrimImplikant
{
private:
	static bool compareGray(uint a, uint b);
	void makeLocations();

	vector<KV_PiEleLoc*>* _locations;

public:
	string name;
	uint id;
	vector<uint> elements;

	PrimImplikant(string input)
	{
		this->name = input;
		this->parser(input);
		this->_locations = NULL;
	}
	PrimImplikant(uint input)
	{
		char nameC[sizeof(uint)*8+1];
		_itoa_s(input, nameC, sizeof(uint)*8+1, 10);
		this->name = nameC;

		this->elements.push_back(input);
		this->_locations = NULL;
	}
	PrimImplikant(uint input1, uint input2)
	{
		char nameC[sizeof(uint)*8+1];
		_itoa_s(input1, nameC, sizeof(uint)*8+1, 10);
		this->name = nameC;
		_itoa_s(input2, nameC, sizeof(uint)*8+1, 10);
		this->name.append("|");
		this->name.append(nameC);

		this->elements.push_back(input1);
		this->elements.push_back(input2);
		this->_locations = NULL;
	}

	bool valueAt(uint position);
	void parser(string input);
	void sort();
	vector<KV_PiEleLoc*>* locations();

	~PrimImplikant()
	{
		if (this->_locations)
		{
			for (uint i = 0; i < this->_locations->size(); i++)
				delete this->_locations->at(i);

			delete this->_locations;
			this->_locations = NULL;
		}
	}
};