#include "stdafx.h"
#include <string>
#include <algorithm>
#include <vector>
#include "Tools.h"
#include "PrimImplikant.h"

using namespace std;

uint PrimImplikant::globalCount = 0;

/// <summary>
/// Checks whether this PrimImplikant covers the specified position
/// </summary>
/// <param name="position">The position that shall be checked</param>
bool PrimImplikant::valueAt(uint position) {
	for (vector<uint>::iterator i = elements.begin(); i < elements.end(); ++i)		// for each element
		if (*i == position)															// if it is matched
			return true;															// this PI covers this position

	return false;
}

/// <summary>
/// Converts the specified input string to a number of elements by replacing a x by 0 and 1 and then calling itself again
/// </summary>
/// <param name="input">The input string from CParser that defines this PrimImplikant</param>
void PrimImplikant::parser(string input) {
	uint implikant = 0;
	for (uint i = 0; i < input.size(); i++)	// for each character
	{
		char c = input[i];					// can we get a pointer to this char?
		if (c == 'x' || c == 'X')			// we found an X
		{
			input[i] = '0';					// replace X by 0 and call parse again
			parser(input);
			input[i] = '1';					// replace X by 1 and call parse again
			parser(input);
			return;
		}
		if (c != '0' && c != '1')			// if the character is neither X nor 0 nor 1: error!
		{
			printf("**** FATAL ERROR **** %s is not binary\n", input);	// perhaps we should log to error file
			return;
		}

		implikant <<= 1;					// no X found yet
		implikant |= (uint)(c - '0');		// convert the string to a number
	}

	this->elements.push_back(implikant);	// add the converted number
}

/// <summary>
/// <para>Sort elements using Tools:compareAsGray. They will be ordered in Gray order ascending</para>
/// <para>algorithm.h uses InsertionSort</para>
/// </summary>
void PrimImplikant::sort()
{
	std::sort(this->elements.begin(), this->elements.end(), &Tools::compareAsGray);
}

/// <summary>
/// Creates a KV_PiEleLoc for each _element. Therefore it has to sort elements first (see this->sort()) and then fills _locations
/// </summary>
void PrimImplikant::makeLocations()
{
	this->sort();
	this->_locations = new vector<KV_PiEleLoc*>();
	this->_locations->resize(this->elements.size());
	for (uint i = 0; i < this->elements.size(); i++)
<<<<<<< HEAD
		this->_locations->at(i) = new KV_PiEleLoc(this->elements[i]); // zu fragen
=======
		this->_locations->at(i) = new KV_PiEleLoc(this->elements[i]);
>>>>>>> Added Comments
}

/// <summary>
/// Lazy initialisation of this->_locations
/// </summary>
vector<KV_PiEleLoc*>* PrimImplikant::locations()
{
	if (this->_locations == NULL)
		this->makeLocations();
	return this->_locations;
}

/// <summary>
/// Returns the number of Cells that this PrimImplikant covers
/// </summary>
uint PrimImplikant::size()
{
	return this->elements.size();
}