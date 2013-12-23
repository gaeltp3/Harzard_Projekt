//#include <iostream>
#include <string>
#include <vector>
#include "PrimImplikant.h"
#include "Implikant_localisation.h"

using namespace std;
extern uint dimension;
extern uint numElements;
extern bool KNF;

#ifndef PRIMIMPLIKANTCOLLEC
#define PRIMIMPLIKANTCOLLEC

class PrimImplikantCollection{
public:
	void add(PrimImplikant* &PI);
	void add(string input);
	void add(uint input);
	void add(uint input1, uint input2);

	bool valueAt(uint position);
	PrimImplikantCollection primImplikantenAt(uint position);
	bool contains(PrimImplikant* foreign);
	void setgroupCollection1(PrimImplikant* &currentPI);
	void setgroupCollection2(PrimImplikant* &currentPI,vector<Implikant_localisation*> &group);
	bool Anwesenheit(Implikant_localisation* &I, vector<Implikant_localisation*> &group);

	void Dispose();

	uint size();
	PrimImplikant* back();
	PrimImplikant* front();
	PrimImplikant* at(uint &index);
	PrimImplikant* operator[](uint &index);
private:
	vector<PrimImplikant*> PIVector;
};

#endif