#include "stdafx.h"
#include <string>
#include <vector>
#include "PrimImplikantCollection.h"

using namespace std;

uint PrimImplikantCollection::globalCount = 0;

void PrimImplikantCollection::add(PrimImplikant* &PI)
{
	PIVector.push_back(PI);
}
void PrimImplikantCollection::add(string input)
{
	PrimImplikant* PI = new PrimImplikant(input);

	PI->id = PrimImplikantCollection::globalCount++;
	this->add(PI);
}
void PrimImplikantCollection::add(uint input)
{
	PrimImplikant* PI = new PrimImplikant(input);
	PI->id = PrimImplikantCollection::globalCount++;
	this->add(PI);
}
void PrimImplikantCollection::add(uint input1, uint input2)
{
	PrimImplikant* PI = new PrimImplikant(input1, input2);
	PI->id = PrimImplikantCollection::globalCount++;
	this->add(PI);
}

bool PrimImplikantCollection::valueAt(uint position)
{
	for (vector<PrimImplikant*>::iterator i = PIVector.begin(); i < PIVector.end(); i++)
		if ((*i)->valueAt(position))
			return true;
	return false;
}

PrimImplikantCollection PrimImplikantCollection::primImplikantenAt(uint position)
{
	PrimImplikantCollection pic;
	for (vector<PrimImplikant*>::iterator i = PIVector.begin(); i < PIVector.end(); i++)
		if ((*i)->valueAt(position))
			pic.add(*i);
	return pic;
}

bool PrimImplikantCollection::contains(PrimImplikant* foreign)
{
	for (vector<PrimImplikant*>::iterator i = PIVector.begin(); i < PIVector.end(); i++)
		if ((*i)->id == foreign->id)
			return true;
	return false;
}

uint PrimImplikantCollection::size()
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

PrimImplikant* PrimImplikantCollection::at(uint &index)
{
	return this->PIVector.at(index);
}

PrimImplikant* PrimImplikantCollection::operator[](uint &index){
	if (index < PIVector.size())
		return this->PIVector.at(index);

	return 0;
}


void PrimImplikantCollection::Dispose()
{
	for (uint i = 0; i < this->size(); i++)
		delete this->at(i);
}