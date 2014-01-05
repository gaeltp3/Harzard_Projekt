#pragma once

#include <string>
#include <vector>
#include "Implikant_localisation.h"

using namespace std;

class PrimImplikant
{
private:
	bool compareGray(uint &a, uint &b);
	void makeLocations();

	vector<KV_PiEleLoc*>* locations = NULL;

public:
	string name;
	uint id;
	vector<uint> elements;

	PrimImplikant(string input)
	{
		name = input;
		parser(input);
	}
	PrimImplikant(uint input)
	{
		char nameC[sizeof(uint)*8+1];
		_itoa_s(input, nameC, sizeof(uint)*8+1, 10);
		name = nameC;

		implikanten.push_back(input);
		I_Vector.push_back(new Implikant_localisation(input));
	}
	PrimImplikant(uint input1, uint input2)
	{
		char nameC[sizeof(uint)*8+1];
		_itoa_s(input1, nameC, sizeof(uint)*8+1, 10);
		name = nameC;
		_itoa_s(input2, nameC, sizeof(uint)*8+1, 10);
		name.append("|");
		name.append(nameC);

		implikanten.push_back(input1);
		I_Vector.push_back(new Implikant_localisation(input1));
		implikanten.push_back(input2);
		I_Vector.push_back(new Implikant_localisation(input2));
	}

	bool valueAt(uint position);
	void parser(string input);
	void sort();
	vector<KV_PiEleLoc*>* locations();

	~PrimImplikant()
	{
		if (this->locations)
		{
			for (uint i = 0; i < this->locations.size(); i++)
			{
				delete this->locations[i];
				this->locations[i] = NULL;
			}
			delete this->locations;
			this->locations = NULL;
		}
	}
};