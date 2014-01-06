#pragma once

#include "stdafx.h"
#include "Tools.h"

using namespace std;

extern uint dimension;

class KV_PiEleLoc
{
public:
	uint i;
	uint w;
	uint h;

	KV_PiEleLoc(uint &i)
	{
		const uint numVarX = (uint)floor(dimension / 2.0f);
		
		this->i = i;

		this->w = i & ((0x1 << (numVarX)) - 1);		// get x coord
		this->w = Tools::GrayToBinary(w);

		this->h = i >> numVarX;						// get y coord
		this->h = Tools::GrayToBinary(h);
	}
};
