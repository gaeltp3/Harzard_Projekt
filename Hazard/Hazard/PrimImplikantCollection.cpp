#include "stdafx.h"
#include <string>
#include <vector>
#include "PrimImplikantCollection.h"

using namespace std;

void PrimImplikantCollection::add(PrimImplikant* &PI)
{
	PIVector.push_back(PI);
}
void PrimImplikantCollection::add(string input)
{
	PrimImplikant* PI = new PrimImplikant(input);
	PIVector.push_back(PI);
}
void PrimImplikantCollection::add(int input)
{
	PrimImplikant* PI = new PrimImplikant(input);
	PIVector.push_back(PI);
}

bool PrimImplikantCollection::valueAt(int position)
{
	for (vector<PrimImplikant*>::iterator i = PIVector.begin(); i < PIVector.end(); i++)
		if ((*i)->valueAt(position))
			return true;
	return false;
}

PrimImplikantCollection PrimImplikantCollection::primImplikantenAt(int position)
{
	PrimImplikantCollection pic;
	for (vector<PrimImplikant*>::iterator i = PIVector.begin(); i < PIVector.end(); i++)
		if ((*i)->valueAt(position))
			pic.add(*i);
	return pic;
}

unsigned int PrimImplikantCollection::size()
{
	return this->PIVector.size();
}

PrimImplikant* PrimImplikantCollection::back()
{
	return this->PIVector.back();
}

PrimImplikant* PrimImplikantCollection::front()
{
	return this->PIVector.front();
}

PrimImplikant* PrimImplikantCollection::at(int const &index)
{
	return this->PIVector.at(index);
}