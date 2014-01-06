#include "stdafx.h"
#include "KV_PiEleLoc.h"
#include "KV_PiGroup.h"

using namespace std;


bool KV_PiGroup::LiesNextTo(KV_PiEleLoc* &el)
{
	for (uint i = 0; i < this->elements.size(); i++)
	{
		KV_PiEleLoc* elG = this->elements[i];
		if (elG->h - el->h == 0 && abs((int)elG->w - (int)el->w) == 1	||
			elG->w - el->w == 0 && abs((int)elG->h - (int)el->h) == 1)
			return true;
	}
	return false;
}

void KV_PiGroup::Add(KV_PiEleLoc* &el)
{
	this->elements.push_back(el);
}

void KV_PiGroup::MakeCoords(uint edgeLength, uint VarX_Length, uint VarY_Length)
{
	uint x1, x2, y1, y2;
	uint X1 = -1, X2 = 0, Y1 = -1, Y2 = 0;
	KV_PiEleLoc* loc;
	for (uint i = 0; i < this->elements.size(); i++)
	{
		loc = this->elements[i];
		x1 = loc->w  * (edgeLength + 1) + VarY_Length;			// Upper coord
		x2 = x1 + edgeLength;									// Lower coord
		y1 = loc->h * (edgeLength + 1) + VarX_Length;			// Left  coord
		y2 = y1 + edgeLength;									// Right coord

		X1 = min(X1, x1);
		X2 = max(X2, x2);
		Y1 = min(Y1, y1);
		Y2 = max(Y2, y2);
	}

	this->X1 = X1;
	this->X2 = X2;
	this->Y1 = Y1;
	this->Y2 = Y2;
}

KV_PiEleLoc* KV_PiGroup::operator[](uint &index)
{
	return this->elements.at(index);
}
KV_PiEleLoc* KV_PiGroup::at(uint &index)
{
	return this->elements.at(index);
}

uint KV_PiGroup::size()
{
	return this->elements.size();
}