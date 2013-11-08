#ifndef PRIMIMPLIKANTEN
#define PRIMIMPLIKANTEN

#include <string>
#include <vector>
#include <map>

using namespace std;

class PrimImplikant
{
public:
	PrimImplikant(string input);
	//PrimImplikant(int input);

	bool valueAt(int position);
	

private:
	map<string,int> implikant;
}



#endif