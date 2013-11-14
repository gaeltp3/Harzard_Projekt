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
	void add(unsigned int input);
	void add(unsigned int input1, unsigned int input2);

	bool valueAt(unsigned int position);
	PrimImplikantCollection primImplikantenAt(unsigned int position);

	unsigned int size();
	PrimImplikant* back();
	PrimImplikant* front();
	PrimImplikant* at(unsigned int const &index);
	PrimImplikant* operator[](unsigned int const &index);
	const PrimImplikant* operator[](unsigned int const &index) const;	
	
	~PrimImplikantCollection()	// destructor
	{
		for (unsigned int i = 0; i < this->size(); i++)
			delete this->at(i);
	}
private:
	vector<PrimImplikant*> PIVector;
};

#endif