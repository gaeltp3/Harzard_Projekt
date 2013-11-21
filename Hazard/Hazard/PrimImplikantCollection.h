//#include <iostream>
#include <string>
#include <vector>
#include "PrimImplikant.h"

using namespace std;

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