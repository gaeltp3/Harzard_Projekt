#pragma once

#include "stdafx.h"
#include "Tools.h"

using namespace std;

extern uint dimension;

/// <summary>
/// This class saves the X and Y values in a KV diagram for the specified i
/// </summary>
class KV_PiEleLoc
{
public:
	uint i;
	uint w;
	uint h;
	
	/// <summary>
	/// Constructor of KV_PiEleLoc
	/// </summary>
	KV_PiEleLoc(uint &i)
	{
		const uint numVarX = (uint)floor(dimension / 2.0f);	// get the number of variables in X direction
		
		this->i = i;

		// we need numVarX ones here
		// example: numVarX = 3 -->  (0001 << 3) - 1 = 1000 - 1 = 0111
		this->w = i & ((0x1 << (numVarX)) - 1);				// get x coord out of i (lower numVarX bits)
		this->w = Tools::GrayToBinary(w);					// convert from gray to binary

		this->h = i >> numVarX;								// get y coord out of i (higher bits)
		this->h = Tools::GrayToBinary(h);					// convert from gray to binary
	}
};