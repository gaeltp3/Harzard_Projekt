#ifndef PRIMIMPLIKANTCOLLEC
#define PRIMIMPLIKANTCOLLEC

#include <string>
#include <vector>
#include "PrimImplikant.h"

using namespace std;

class PrimImplikantCollection{
public:
	void add(PrimImplikant &PI);
	void add(string input);
	void add(int input);

	bool valueAt(int position);
	vector<PrimImplikant> primImplikantenAt(int position);

	PrimImplikant solveNextHazard();
	
private:
	vector<PrimImplikant> PIVector;
};

#endif