#include "stdafx.h"
#include <string>
#include <vector>
#include "PrimImplikantCollection.h"

using namespace std;

/// <summary>
/// Adds the specified PrimImplikant PI to the collection
/// </summary>
/// <param name="PI">The PrimImplikant that shall be added to the collection</param>
void PrimImplikantCollection::add(PrimImplikant* &PI)
{
	PIVector.push_back(PI);
}
/// <summary>
/// Adds a PrimImplikant with the specified input to the collection
/// </summary>
/// <param name="input">The parsed data from CParser out of the input file</param>
void PrimImplikantCollection::add(string input)
{
	PrimImplikant* PI = new PrimImplikant(input);
	this->add(PI);
}
/// <summary>
/// Adds a PrimImplikant with the specified input to the collection
/// </summary>
/// <param name="input">The parsed data from CParser out of the input file</param>
void PrimImplikantCollection::add(uint input)
{
	PrimImplikant* PI = new PrimImplikant(input);
	this->add(PI);
}
/// <summary>
/// <para>Adds a PrimImplikant which covers both input1 and input2.</para>
/// <para>Beware: No checks are done here, you could easily add a PrimImplikant that cannot exist logically!</para>
/// </summary>
/// <param name="input1">Some number</param>
/// <param name="input2">Some other number</param>
void PrimImplikantCollection::add(uint input1, uint input2)
{
	PrimImplikant* PI = new PrimImplikant(input1, input2);
	this->add(PI);
}

/// <summary>
/// Returns whether a PrimImplikant covers the specified position
/// </summary>
/// <param name="position">The position you want to check. It is a normal binary number</param>
/// <returns>True: A PrimImplikant was found. False: No was not found at this position</returns>
bool PrimImplikantCollection::valueAt(uint position)
{
	for (PrimImplikantIt i = PIVector.begin(); i < PIVector.end(); i++)		// for each PrimImplikant
		if ((*i)->valueAt(position))										// if one is true
			return true;													// the collection is true, too
	return false;															// nothing found, the collection is false
}

/// <summary>
/// Generates a new PrimImplikantCollection with a subset of the saved PrimImplikants: All those that cover the specified position.
/// </summary>
/// <param name="position">The position. It is a number</param>
/// <returns>A new PrimImplikantCollection with all found PrimImplikants
PrimImplikantCollection PrimImplikantCollection::primImplikantenAt(uint position)
{
	PrimImplikantCollection pic;
	for (PrimImplikantIt i = PIVector.begin(); i < PIVector.end(); i++)		// for every PrimImplikant
		if ((*i)->valueAt(position))										// if it is true
			pic.add(*i);													// add it to the new collection
	return pic;
}

/// <summary>
/// <para>Looks for the specified PrimImplikant foreign in this collection</para>
/// </summary>
/// <returns>True: foreign was found in here and is not foreign. False: foreign is indeed foreign</returns>
bool PrimImplikantCollection::contains(PrimImplikant* foreign)
{
	for (PrimImplikantIt i = PIVector.begin(); i < PIVector.end(); i++)		// for all PrimImplikants
		if ((*i)->id == foreign->id)										// if ID matches
			return true;													// we found it
	return false;
}

/// <summary>
/// Returns the number of PrimImplikants in this collection
/// </summary>
uint PrimImplikantCollection::size()
{
	return this->PIVector.size();
}

/// <summary>
/// Returns the last added PrimImplikant
/// </summary>
PrimImplikant* PrimImplikantCollection::back()
{
	return this->PIVector.back();
}

/// <summary>
/// Returns the first added PrimImplikant
/// </summary>
PrimImplikant* PrimImplikantCollection::front()
{
	return this->PIVector.front();
}

/// <summary>
/// Returns the PrimImplikant at the specified index
/// </summary>
PrimImplikant* PrimImplikantCollection::at(const uint &index)
{
	return this->PIVector.at(index);
}
/// <summary>
/// Returns the PrimImplikant at the specified index
/// </summary>
PrimImplikant* PrimImplikantCollection::operator[](const uint &index){
	return this->PIVector.at(index);
}


/// <summary>
/// <para>Deletes all PrimImplikant instances in this collection.</para>
/// <para>Beware: Only do this at the end! All collections are storing pointers to the PrimImplikants and maybe some other object is still using them. Dispose() may only be called by the last instance of this class (which we could check programmatically and then integrate it into the destructor)</para>
/// </summary>
void PrimImplikantCollection::Dispose()
{
	for (uint i = 0; i < this->size(); i++)
		delete this->at(i);
	this->PIVector.clear();
}