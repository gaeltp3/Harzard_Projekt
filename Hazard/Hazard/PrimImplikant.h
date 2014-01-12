#pragma once

#include <string>
#include <vector>
#include "KV_PiEleLoc.h"

using namespace std;

/// <summary>
/// This class represents a PrimImplikant. It contains a vector with all covered positions/locations
/// <summary>
class PrimImplikant
{
private:
	vector<uint> elements;								// The positions this PrimImplikant covers
	vector<KV_PiEleLoc*>* _locations;					// The XY coordinates in a KV for each position

	static uint globalCount;							// A counter used for ID generation

	/// <summary>
	/// Sets default values for id and _locations
	/// </summary>
	void init()
	{
		this->id = PrimImplikant::globalCount++;
		this->_locations = NULL;
	}

	void makeLocations();								// Generates _locations
	void parser(string input);							// Parses an input string to fill elements
public:
	string name;										// The name of the PrimImplikant as imported
	uint id;											// The unique identifier (see ::globalCount)

	/// <summary>
	/// Sets name and calls this->parser(input)
	/// </summary>
	/// <param name="input">The imported string that defines this PrimImplikant</param>
	PrimImplikant(string input)
	{
		init();
		this->name = input;
		this->parser(input);
	}
	/// <summary>
	/// Creates a PrimImplikant that covoers only the specified input position
	/// </summary>
	/// <param name="input">The imported position</param>
	PrimImplikant(uint input)
	{
		init();
		char nameC[sizeof(uint)*8+1];
		_itoa_s(input, nameC, sizeof(uint)*8+1, 10);
		this->name = nameC;

		this->elements.push_back(input);
	}
	/// <summary>
	/// <para>Creates a PrimImplikant that covers two positions. This is used to solve detected hazards</para>
	/// <para>Beware: No checks are done here, you could easily add a PrimImplikant that cannot exist logically!</para>
	/// </summary>
	/// <param name="input1">A number</param>
	/// <param name="input2">A number which's Hanning distance to input1 is only 1</param>
	PrimImplikant(uint input1, uint input2)
	{
		init();
		char nameC[sizeof(uint)*8+1];					// generate the name
		_itoa_s(input1, nameC, sizeof(uint)*8+1, 10);	// convert input1
		this->name = nameC;
		this->name.append("|");							// add delimiter
		_itoa_s(input2, nameC, sizeof(uint)*8+1, 10);	// convert inpiut2
		this->name.append(nameC);

		this->elements.push_back(input1);				// add both input1 and input2 to elements
		this->elements.push_back(input2);
	}

	//vector<uint>* elements();							// returns elements
	uint size();										// returns the number of elements in elements
	bool valueAt(uint position);						// returns whether this PrimImplikant covers the specified position
	void sort();										// sort elements as Gray numbers
	vector<KV_PiEleLoc*>* locations();					// get the locations of elements in a KV

	/// <summary>
	/// Deletes all KV_PiLocs and _locations itself
	/// </summary>
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



#ifndef PRIMIMPLIKANTITERATOR
#define PRIMIMPLIKANTITERATOR
typedef vector<PrimImplikant*>::iterator PrimImplikantIt;
#endif