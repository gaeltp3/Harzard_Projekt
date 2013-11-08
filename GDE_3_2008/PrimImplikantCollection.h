#ifndef PRIMIMPLIKANTCOLLEC
#define PRIMIMPLIKANTCOLLEC

#include <string>
#include <vector>
#include "PrimImplikanten.h"

using namespace std;

class PrimImplikantCollection{
public:
	void Add(PrimImplikant &pi);
	//void Add(string input);
	void Add(int input);

	bool ValueAt(int position);

	PrimImplikant SolveNextHazard();
	
private:
	vector<PrimImplikant> PIVector;
}

#endif