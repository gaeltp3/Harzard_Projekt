#pragma once

#include "stdafx.h"
#include <vector>
#include "KV_PiEleLoc.h"

using namespace std;

extern uint dimension;

class KV_PiGroup
{
private:
	vector<KV_PiEleLoc*> elements;
public:
	bool LiesNextTo(KV_PiEleLoc* &el);
	void Add(KV_PiEleLoc* &el);
	void MakeCoords(uint edgeLength, uint VarX_Length, uint VarY_Length);

	KV_PiEleLoc* operator[](uint &index);
	KV_PiEleLoc* at(uint &index);
	uint size();

	uint X1, X2, Y1, Y2;
};