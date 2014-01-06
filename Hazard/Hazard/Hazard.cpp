#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
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
bool fileChosen = false;
char fnInput[256];
char fnError[256];
char fnLists[256];


int open_files(FILE * &input, FILE * &error, FILE * &list)
{
	if (fileChosen == false)
	{
		GetCurrentDirectory(sizeof(fnInput), fnInput);
		strcpy_s(fnError, (string(fnInput) + "\\res\\errorParser.txt").c_str());
		strcpy_s(fnLists, (string(fnInput) + "\\res\\listParser.txt").c_str());
		strcpy_s(fnInput, (string(fnInput) + "\\res\\input.txt").c_str());

		OPENFILENAME ofn;
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = fnInput;
		ofn.nMaxFile = sizeof(fnInput);
		ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetOpenFileName(&ofn) != TRUE)
		{
			cout << "Auswahl der Inputdatei abgebrochen!";
			return 1;
		}
		fileChosen = true;
	}

	fopen_s(&input, fnInput, "r");
	if (input == NULL)
	{
		perror("Fehler beim Lesen der Inputdatei");
		return 1;
	}
	fopen_s(&error, fnError, "a");
	if (error == NULL)
	{
		perror("Fehler beim Öffnen der Fehlerdatei");
		return 1;
	}
	fopen_s(&list, fnLists, "w");
	if (list == NULL)
	{
		perror("Fehler beim Öffnen der Listdatei");
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
	FILE * input, * error, * list;
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