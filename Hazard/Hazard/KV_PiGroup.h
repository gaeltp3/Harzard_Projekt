#pragma once

#include "stdafx.h"
#include <vector>
#include "KV_PiEleLoc.h"

using namespace std;

extern uint dimension;

/// <summary>
/// This class stores several KV_PiEleLoc objects and thus represents one "Kuller" of the PrimImplikant
/// </summary>
class KV_PiGroup
{
private:
	vector<KV_PiEleLoc*> elements;			// locations
public:
	bool LiesNextTo(KV_PiEleLoc* &el);		// whether the specified el lies next to this group
	void Add(KV_PiEleLoc* &el);				// add a location to this group
	void MakeCoords(uint edgeLength, uint VarX_Length, uint VarY_Length, uint* X1, uint* Y1, uint* X2, uint* Y2);	// Generates the coordinates for this group

	KV_PiEleLoc* operator[](uint &index);	// location at index
	KV_PiEleLoc* at(uint &index);			// location at index
	uint size();							// number of locations
};