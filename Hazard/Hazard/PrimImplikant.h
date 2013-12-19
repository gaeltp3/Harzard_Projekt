#ifndef PRIMIMPLIKANT
#define PRIMIMPLIKANT

#include <string>
#include <vector>

using namespace std;

class PrimImplikant
{
public:
	string name;
	uint id;

	PrimImplikant(string input)
	{
		name = input;
		parser(input);
	}
	PrimImplikant(uint input)
	{
		char nameC[sizeof(uint)*8+1];
		_itoa_s(input, nameC, sizeof(uint)*8+1, 10);
		name = nameC;

		implikanten.push_back(input);
	}
	PrimImplikant(uint input1, uint input2)
	{
		char nameC[sizeof(uint)*8+1];
		_itoa_s(input1, nameC, sizeof(uint)*8+1, 10);
		name = nameC;
		_itoa_s(input2, nameC, sizeof(uint)*8+1, 10);
		name.append("|");
		name.append(nameC);

		implikanten.push_back(input1);
		implikanten.push_back(input2);
	}

	bool PrimImplikant::valueAt(uint position);
	void PrimImplikant::parser(string input);
	void add(Implikant_localisation* &I);

	vector<uint> implikanten;
	vector<Implikant_localisation*> I_Vector;
};
#endif