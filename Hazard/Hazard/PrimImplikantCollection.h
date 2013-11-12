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
	void add(int input);

	bool valueAt(int position);
	PrimImplikantCollection primImplikantenAt(int position);

	unsigned int size();
	PrimImplikant* back();
	PrimImplikant* front();
	PrimImplikant* at(int const &index);
	PrimImplikant* operator[](int const &index);
	const PrimImplikant* operator[](int const &index) const;	
	
	~PrimImplikantCollection()	// destructor
	{
		for (unsigned int i = 0; i < this->size(); i++)
			delete this->at(i);
	}
private:
	vector<PrimImplikant*> PIVector;
};

#endif