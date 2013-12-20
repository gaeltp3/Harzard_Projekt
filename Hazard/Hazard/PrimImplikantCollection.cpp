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

	PI->id = this->size();
	setgroupCollection1(PI);
	this->add(PI);
}
void PrimImplikantCollection::add(uint input)
{
	PrimImplikant* PI = new PrimImplikant(input);
	PI->id = this->size();
	setgroupCollection1(PI);
	this->add(PI);
}
void PrimImplikantCollection::add(uint input1, uint input2)
{
	PrimImplikant* PI = new PrimImplikant(input1, input2);
	PI->id = this->size();
	setgroupCollection1(PI);
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

bool PrimImplikantCollection::Anwesenheit(Implikant_localisation* &I, vector<Implikant_localisation*> &group)
{

	for (vector<Implikant_localisation*>::iterator it = group.begin(); it < group.end(); it++)
	{
		if ((*it)->i == (I->i))
		{
			return true;
		}

	}
	return false;
}

void PrimImplikantCollection::setgroupCollection1(PrimImplikant* &currentPI)
{
	vector<Implikant_localisation*>::iterator it1;
	vector<Implikant_localisation*> groupA;            // Jede I_vector wird in einem oder in Zwei vectoren
	vector<Implikant_localisation*> groupB;            //  zuerst gespaltet.

	static int Linie_mitte;
	uint numVarY = (uint)ceil(dimension / 2.0f);
	


	for (it1 = currentPI->I_Vector.begin(); it1 < currentPI->I_Vector.end(); it1++)
	{
		if ((((*it1)->h) = (numVarY / 2) - 1) || (((*it1)->h) = (numVarY / 2)))
		{
			Linie_mitte++;      // test zu wissen ob die MitteLinie h  der KV diagramm erreicht ist.
			// Test zu wissen , wieviele Implikanten in Mitte_tiefe  sind
			//schalter = 1;
		}
		continue;
	}

	if (Linie_mitte)    // Wenn wahr ist. ES geht um Linie_mitte_Y
	{
		for (it1 = currentPI->I_Vector.begin(); it1 < currentPI->I_Vector.end(); it1++)
		{
			groupA.push_back(*it1);
		}

		currentPI->PI_groupCollection.push_back(&groupA);
		Linie_mitte = 0;
	}
	else
	{
		for (it1 = currentPI->I_Vector.begin(); it1 < currentPI->I_Vector.end(); it1++)
		{

			if (((*it1)->h < (numVarY / 2) - 1))  // die Implikanten, deren h <= numVary/2 -1 sind im groupA
			{                                          // gespeichert.

				groupA.push_back(*it1);


			}

			else { groupB.push_back(*it1); }

		}

		setgroupCollection2(currentPI,groupA);
		setgroupCollection2(currentPI,groupB);
	}

}


void PrimImplikantCollection::setgroupCollection2(PrimImplikant* &currentPI, vector<Implikant_localisation*>&group)
{

	vector<Implikant_localisation*> hilfVec1, hilfVec2;
	vector<Implikant_localisation*>::iterator it1;
	uint numVarX = (uint)floor(dimension / 2.0f);
	static int Linie_mitte;								// Zustand 0--> wird h überprüft im Vector
	// Zustand 1-->wird w überprüft im Vector.
	// Ohne Zuweisung hat schalter am Anfang den Wert 0



	for (it1 = group.begin(); it1 < group.end(); it1++)
	{
		if ((((*it1)->h) = (numVarX / 2) - 1) || (((*it1)->h) = (numVarX / 2)))
		{
			Linie_mitte++;      // test zu wissen ob die MitteLinie h  der KV diagramm erreicht ist.
			// Test zu wissen , wieviele Implikanten in Mitte_tiefe  sind
			//schalter = 1;
		}
		continue;
	}

	if (Linie_mitte)    // Wenn wahr ist.--> Linie_mitte_X
	{

		currentPI->PI_groupCollection.push_back(&group);
		Linie_mitte = 0;
	}
	else
	{
		for (it1 = group.begin(); it1 < group.end(); it1++)
		{

			if (((*it1)->w < (numVarX / 2) - 1))  // die Implikanten, deren h <= numVary/2 -1 sind im groupA
			{                                          // gespeichert.

				hilfVec1.push_back(*it1);


			}

			else { hilfVec2.push_back(*it1); }

		}

		currentPI->PI_groupCollection.push_back(&hilfVec1);
		currentPI->PI_groupCollection.push_back(&hilfVec2);
	}
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