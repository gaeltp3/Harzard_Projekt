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
	PrimImplikant(unsigned int input)
	{
		char nameC[sizeof(unsigned int)*8+1];
		_itoa_s(input, nameC, sizeof(unsigned int)*8+1, 10);
		name = nameC;

		implikanten.push_back(input);
	}
	PrimImplikant(unsigned int input1, unsigned int input2)
	{
		char nameC[sizeof(unsigned int)*8+1];
		_itoa_s(input1, nameC, sizeof(unsigned int)*8+1, 10);
		name = nameC;
		_itoa_s(input2, nameC, sizeof(unsigned int)*8+1, 10);
		name.append(" & ");
		name.append(nameC);

		implikanten.push_back(input1);
		implikanten.push_back(input2);
	}

	bool PrimImplikant::valueAt(unsigned int position);
	void PrimImplikant::parser(string input);
	

private:
	vector<unsigned int> implikanten;
};
#endif