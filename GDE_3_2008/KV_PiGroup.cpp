#include "stdafx.h"
#include "KV_PiEleLoc.h"
#include "KV_PiGroup.h"

using namespace std;


bool KV_PiGroup::LiesNextTo(KV_PiEleLoc* &el)
{
	for (uint i = 0; i < this->elements.size(); i++)
	{
		KV_PiEleLoc* elG = this->elements[i];
		if (elG->h - el->h == 0 && abs(elG->w - el->w) == 1	||
			elG->w - el->w == 0 && abs(elG->h - el->h) == 1)
			return true;
	}
	return false;
}

void KV_PiGroup::Add(KV_PiEleLoc* &el)
{
	this->elements.push_back(el);
}

void KV_PiGroup::MakeCoords()
{
	uint x1, x2, y1, y2;
	uint X1 = -1, X2 = 0, Y1 = -1, Y2 = 0;
	KV_PiEleLoc* loc;
	for (uint i = 0; i < this->elements->size(); i++)
	{
		loc = this->elements[i];
		x1 = loc->w  * (this->edgeLength + 1) + this->VarY_Length;			// Upper coord
		x2 = x1 + this->edgeLength;										// Lower coord
		y1 = loc->h * (this->edgeLength + 1) + this->VarX_Length;			// Left  coord
		y2 = y1 + this->edgeLength;										// Right coord

		this->X1 = min(this->X1, x1);
		this->X2 = max(this->X2, x2);
		this->Y1 = min(this->Y1, y1);
		this->Y2 = max(this->Y2, y2);
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