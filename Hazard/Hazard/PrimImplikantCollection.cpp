#include "stdafx.h"
#include <string>
#include <vector>
#include "PrimImplikantCollection.h"

using namespace std;

void PrimImplikantCollection::add(PrimImplikant &PI)
{
	PIVector.push_back(PI);
}
void PrimImplikantCollection::add(string input)
{
	PrimImplikant PI(input);
	PIVector.push_back(PI);
}
void PrimImplikantCollection::add(int input)
{
	PrimImplikant PI(input);
	PIVector.push_back(PI);
}

bool PrimImplikantCollection::valueAt(int position)
{
	for (vector<PrimImplikant>::iterator i = PIVector.begin(); i < PIVector.end(); i++)
		if (i->valueAt(position))
			return true;
	return false;
}

vector<PrimImplikant> PrimImplikantCollection::primImplikantenAt(int position)
{
	vector<PrimImplikant> pic;
	for (vector<PrimImplikant>::iterator i = PIVector.begin(); i < PIVector.end(); i++)
		if (i->valueAt(position))
			pic.push_back(*i);
	return pic;
}

PrimImplikant PrimImplikantCollection::solveNextHazard()
{
	PrimImplikant PI(0);
	return PI;
}