//#include <iostream>
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
void PrimImplikantCollection::add(unsigned int input)
{
	PrimImplikant* PI = new PrimImplikant(input);
	PIVector.push_back(PI);
}
void PrimImplikantCollection::add(unsigned int input1, unsigned int input2)
{
	PrimImplikant* PI = new PrimImplikant(input1, input2);
	PIVector.push_back(PI);
}

bool PrimImplikantCollection::valueAt(unsigned int position)
{
	for (vector<PrimImplikant*>::iterator i = PIVector.begin(); i < PIVector.end(); i++)
		if ((*i)->valueAt(position))
			return true;
	return false;
}

PrimImplikantCollection PrimImplikantCollection::primImplikantenAt(unsigned int position)
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

PrimImplikant* PrimImplikantCollection::at(unsigned int const &index)
{
	return this->PIVector.at(index);
}

/*PrimImplikant* PrimImplikantCollection::operator[](unsigned int const &index){
	if (index <= PIVector.size()){

		return this->PIVector.at(index);
	}

	cerr << "Fehler!!!!  PIVector.size()=" << PIVector.size() << endl;
	return 0;
}*/