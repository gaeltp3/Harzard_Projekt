#pragma once

#include <string>
#include <vector>
#include "PrimImplikant.h"

using namespace std;

/// <summary>
/// This class contains a vector with pointers to instances of PrimImplikant and also provides some methods to operate on those data
/// </summary>
class PrimImplikantCollection
{
private:
	vector<PrimImplikant*> PIVector;							// vector with PrimImplikants
public:
	void add(PrimImplikant* &PI);								// adds the specified PrimImplikant to the collection
	void add(string input);										// imports the specified input
	void add(uint input);										// imports the specified input
	void add(uint input1, uint input2);							// imports the specified input1 and input2

	bool valueAt(uint position);								// looks for any PrimImplikant that touches the specified position
	PrimImplikantCollection primImplikantenAt(uint position);	// returns the PrimImplikanten that touch the specified position
	bool contains(PrimImplikant* foreign);						// looks for the specified PrimImplikant in this colleciton
	

	void Dispose();												// delete all PrimImplikants in here

	uint size();												// size of vector PIVector
	PrimImplikant* back();										// last element of PIVector
	PrimImplikant* front();										// first element of PIVector
	PrimImplikant* at(const uint &index);								// element at specified index of PIVector
	PrimImplikant* operator[](const uint &index);						// element at specified index of PIVector
};