#include "stdafx.h"
#include "KV_PiEleLoc.h"
#include "KV_PiGroup.h"

using namespace std;


/// <summary>
/// <para>Checks whether the specified el lies next to this group (in 2D, not Hamming distance)</para>
/// </summary>
/// <param name="el">The element that shall be checked</param>
bool KV_PiGroup::LiesNextTo(KV_PiEleLoc* &el)
{
	for (uint i = 0; i < this->elements.size(); i++)						// for each element in this group
	{																		// (there should be a better way)
		KV_PiEleLoc* elG = this->elements[i];
		if (elG->h - el->h == 0 && abs((int)elG->w - (int)el->w) == 1	||	// if el lies next to elG in X direction
			elG->w - el->w == 0 && abs((int)elG->h - (int)el->h) == 1)		// or el lies next to elG in Y direction
			return true;
	}

	return false;
}

/// <summary>
/// Add the specified  KV_PiElelLoc el to this group
/// </summary>
void KV_PiGroup::Add(KV_PiEleLoc* &el)
{
	this->elements.push_back(el);
}

/// <summary>
/// Calculate the X and Y coordinates with all elements
/// </summary>
void KV_PiGroup::MakeCoords(uint edgeLength, uint VarX_Length, uint VarY_Length, uint* XX1, uint* YY1, uint* XX2, uint* YY2)
{
	uint x1, x2, y1, y2;									// coords for each single element
	uint X1 = -1, X2 = 0, Y1 = -1, Y2 = 0;					// resulting group coords with initial maximum/minimum values

	for (uint i = 0; i < this->elements.size(); i++)		// for all locations in this group
	{
		KV_PiEleLoc* loc = this->elements[i];				// current location
		x1 = loc->w  * (edgeLength + 1) + VarY_Length;		// Upper coord for rectangle around loc
		x2 = x1 + edgeLength;								// Lower coord for rectangle around loc
		y1 = loc->h * (edgeLength + 1) + VarX_Length;		// Left  coord for rectangle around loc
		y2 = y1 + edgeLength;								// Right coord for rectangle around loc

		X1 = min(X1, x1);									// Store it if upper coord is higher  than previous X1
		X2 = max(X2, x2);									// Store it if lower coord is lower   than previous X2
		Y1 = min(Y1, y1);									// Store it if left  coord is lefter  than previous Y1
		Y2 = max(Y2, y2);									// Store it if right coord is righter than previous Y2
	}
	
	*XX1 = X1;
	*YY1 = Y1;
	*XX2 = X2;
	*YY2 = Y2;
}

/// <summary>
/// Returns the KV_PiEleLoc at the specified index
/// </summary>
KV_PiEleLoc* KV_PiGroup::operator[](uint &index)
{
	return this->elements.at(index);
}
/// <summary>
/// Returns the KV_PiEleLoc at the specified index
/// </summary>
KV_PiEleLoc* KV_PiGroup::at(uint &index)
{
	return this->elements.at(index);
}

/// <summary>
/// Returns the size of this KV_PiGroup
/// </summary>
uint KV_PiGroup::size()
{
	return this->elements.size();
}