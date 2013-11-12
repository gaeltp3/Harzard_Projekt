#include <string>
#include <vector>
#include "stdafx.h"
#include "PrimImplikant.h"

using namespace std;

bool PrimImplikant::valueAt(int pos) {
	for (vector<int>::iterator i = implikanten.begin(); i < implikanten.end(); ++i)
	{
		if (*i == pos)
			return true;
	}
	return false;
}

void PrimImplikant::parser(string input) {  // Analyser
	int implikant = 0;
	string text0 = "";
	string text1 = "";
	for (int i = 0; i < input.size(); i++)
	{
		char c = input[i];
		if (c == 'x' || c == 'X')
		{
			text0 = input;
			text1 = input;
			text0[i] = '0';
			text1[i] = '1';
			parser(text0);
			parser(text1);
			return;
		}
		if (c != '0' && c != '1')
		{
			printf("**** FATAL ERROR **** %s is not binary\n", input);
			return;
		}
		implikant <<= 1;	// *2
		implikant += (int)c - (int)'0';
	}
	implikanten.push_back(implikant);
}