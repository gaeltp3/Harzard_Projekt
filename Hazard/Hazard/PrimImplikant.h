#ifndef PRIMIMPLIKANT
#define PRIMIMPLIKANT

#include <string>
#include <vector>

using namespace std;

class PrimImplikant
{
public:
	string name;

	PrimImplikant(string input)
	{
		name = input;
		parser(input);
	}
	PrimImplikant(int input)
	{
		char nameC[sizeof(int)*8+1];
		_itoa_s(input, nameC, sizeof(int)*8+1, 10);
		name = nameC;

		implikanten.push_back(input);
	}

	bool PrimImplikant::valueAt(int position);
	void PrimImplikant::parser(string input);
	

private:
	vector<int> implikanten;
};
#endif