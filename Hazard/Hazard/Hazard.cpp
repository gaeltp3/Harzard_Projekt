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
#include "Wertetabelle.h"

using namespace std;

uint dimension = 0;			// = variables.size()
uint numElements = 0;		// = 2 ^ dimension
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
	fopen_s(&error, "..\\res\\errorParser.txt", "a");
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

	
	// initialize Cells
	vector<Cell*> cells;
	cells.resize(numElements);
	uint numOnes = 0;
	for (uint i = 0; i < numElements; i++)
	{
		cells[i] = new Cell(i, globalPIC);
	}

	
	Wertetabelle* wt = new Wertetabelle(&cells, variables);
	wt->Print();
	delete wt;
	system("pause");


	// find hazards
	for (uint i = 0; i < numElements; i += 2)
	{
		uint grayI = i ^ (i/2);								// transform to gray code --> Schachbrettmuster
		Cell* currentCell = cells[grayI];					// this is the cell we are currently checking

		if (currentCell->value == false)					// no hazard can occur
			continue;

		cout << "   Checking cell " << grayI << endl;
		vector<Cell*>* hazardousNeighbors = currentCell->getHazards(cells);

		if (hazardousNeighbors->size() == 0)				// no hazard found
		{
			delete hazardousNeighbors;
			continue;
		}

		for (vector<Cell*>::iterator c = hazardousNeighbors->begin(); c < hazardousNeighbors->end(); c++)
		{
			printf("Hazard found! Cell %d <--> Cell %d\n", grayI, (*c)->index);
			globalPIC->add(grayI, (*c)->index);				// add PI that solves hazard. Not quite smart...
			(*c)->refresh(globalPIC);						// refresh the local PIC (a PI was added)
		}
		currentCell->refresh(globalPIC);
		delete hazardousNeighbors;
	}
	system("pause");

	wt = new Wertetabelle(&cells, variables);
	wt->Print();
	delete wt;

	globalPIC->Dispose();
	system("pause");
	return 0;
}