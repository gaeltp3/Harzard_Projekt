// Hazard.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include "CParser.h"
#include "PrimImplikant.h"
#include "PrimImplikantCollection.h"
#include "Cell.h"

using namespace std;

unsigned int dimension = 0;
unsigned int numElements = 0;
bool KNF = false;

int _tmain(int argc, _TCHAR* argv[])
{
	FILE * input;
	FILE * error;
	FILE * list;
	fopen_s(&input, "..\\res\\input.txt", "r");
	if (input == 0)
	{
		cout << "Fehler Inputdatei";
		system("pause");
		return -1;
	}
	fopen_s(&error, "..\\res\\errorParser.txt", "w");
	if (error == 0)
	{
		cout << "Fehler Fehlerdatei";
		system("pause");
		return -1;
	}
	fopen_s(&list, "..\\res\\listParser.txt", "w");
	if (list == 0)
	{
		cout << "Fehler Listdatei";
		system("pause");
		return -1;
	}

	PrimImplikantCollection* globalPIC = new PrimImplikantCollection();
	vector<string>* variables = new vector<string>();

	CParser parser;
	parser.IP_init_token_table();
	parser.pr_tokentable();
	parser.InitParse(input, error, list);
	if (parser.yyparse(globalPIC, variables) != 0)
	{
		system("pause");
		return 1;
	}
	system("pause");
	
	/*pic.add(7);
	pic.add("0x1");
	pic.add("100");
	pic.add("00x");
	pic.add(4);

	PrimImplikant prim7(7);
	PrimImplikant prim13("0x1");
	PrimImplikant prim4("100");
	PrimImplikant prim4567("1xx");
	pic.add(prim4567);*/

	/*for (int p = 0; p < numElements; p++)
	{
		//printf("Pos %d: prim7=%d, prim13=%d, prim4=%d, prim4567=%d, pic=%d\n", p, prim7.valueAt(p), prim13.valueAt(p), prim4.valueAt(p), prim4567.valueAt(p), pic.valueAt(p));
			printf("Pos %d: Matching collections: ", p);
			PrimImplikantCollection matchingPIs = globalPIC->primImplikantenAt(p);
			for (int i = 0; i < matchingPIs.size(); i++)
				//cout << i->name < ", ";
				printf("%s, ", matchingPIs[i]->name.c_str());
			cout << endl;
	}*/

	vector<Cell*> cells;
	cells.resize(numElements);
	for (unsigned int i = 0; i < numElements; i++)
	{
		cells[i] = new Cell(i, globalPIC);
		printf("Pos %2d: %d\n", i, cells[i]->value);
	}

	system("pause");
	return 0;
}