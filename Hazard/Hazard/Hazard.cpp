#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include "CParser.h"
#include "PrimImplikant.h"
#include "PrimImplikantCollection.h"
#include "Cell.h"
#include "CellCollection.h"
#include "Wertetabelle.h"
#include "KV.h"

using namespace std;

uint dimension = 0;			// = variables.size()
uint numElements = 0;		// = 2 ^ dimension
bool KNF = false;


int open_files(FILE * &input, FILE * &error, FILE * &list)
{
	fopen_s(&input, "res\\input.txt", "r");
	if (input == 0)
	{
		cout << "Fehler Inputdatei";
		return 1;
	}
	fopen_s(&error, "res\\errorParser.txt", "a");
	if (error == 0)
	{
		cout << "Fehler Fehlerdatei";
		return 1;
	}
	fopen_s(&list, "res\\listParser.txt", "w");
	if (list == 0)
	{
		cout << "Fehler Listdatei";
		return 1;
	}
	return 0;
}

void pause()
{
#ifdef DEBUG
	system("pause");
#endif
}

void user_main(void)
{
	FILE * input;
	FILE * error;
	FILE * list;
	if (open_files(input, error, list) != 0)
	{
		pause();
		return;
	}

	PrimImplikantCollection* globalPIC = new PrimImplikantCollection();
	vector<string>* variables = new vector<string>();

	CParser* parser = new CParser(input, error, list);
	bool parseFailure = parser->yyparse(globalPIC, variables) != 0;

	fclose(input);
	fclose(error);
	fclose(list);
	delete parser;

	if (parseFailure)
	{
		pause();
		return;
	}
	
	// initialize Cells
	CellCollection* allCells = new CellCollection(globalPIC);

	
	// print Wertetabelle and KV of imported data
	Wertetabelle* wt = new Wertetabelle(allCells, variables);
	wt->Print();

	KV* kv = new KV(globalPIC, allCells, 30,variables);
	kv->Print(30);


	// find and solve Hazards
	allCells->findHazards();

	
	// print Wertetabelle and KV of corrected data
	wt->Print();
	delete wt;

	kv->Print(30 + kv->width() + 30, 30);	// Diagramm neben dem vorherigen
	delete kv;

	globalPIC->Dispose();
	allCells->Dispose();
	delete globalPIC;
	delete allCells;
	delete variables;
	cout << endl << endl << endl << endl;
	return;
}