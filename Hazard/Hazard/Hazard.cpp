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


int open_files(ifstream &input, ofstream &error, ofstream &list, ofstream &wt)
{
	if (fileChosen == true)		// don't reopen files
		return 9;

	GetCurrentDirectory(sizeof(fnInput), fnInput);

	if (!error.is_open())
	{
		char fnError[256];
		strcpy_s(fnError, (string(fnInput) + "\\res\\errorParser.txt").c_str());
		error.open(fnError, ofstream::out|ofstream::app);
		if (!error.is_open())
		{
			perror("Fehler beim Öffnen der Fehlerdatei");
			return 1;
		}
	}
	if (!list.is_open())
	{
		char fnLists[256];
		strcpy_s(fnLists, (string(fnInput) + "\\res\\listParser.txt").c_str());
		list.open(fnLists, ofstream::out|ofstream::trunc);
		if (!list.is_open())
		{
			perror("Fehler beim Öffnen der Listdatei");
			return 1;
		}
	}
	if (!wt.is_open())
	{
		char fnWt[256];
		strcpy_s(fnWt, (string(fnInput) + "\\res\\Wertetabelle.txt").c_str());
		wt.open(fnWt, ofstream::out|ofstream::trunc);
		if (!wt.is_open())
		{
			perror("Fehler beim Öffnen der Wertetabellendatei");
			return 1;
		}
	}

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
		return 2;
	}
	fileChosen = true;

	if (input.is_open())
		input.close();
	input.open(fnInput, ifstream::in);
	if (!input.is_open())
	{
		perror("Fehler beim Lesen der Inputdatei");
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
	ifstream fInput;
	ofstream fError, fList, fWt;
	KV* kv;
	while(1)
	{
		switch(open_files(fInput, fError, fList, fWt))
		{
		case 1:		// some error
			fileChosen = false;
			perror("Error while opening a file (1)");
			continue;
		case 2:		// user aborted
			ExitProcess(2);
			break;
		case 9:		// same input as before
					// We could skip recalculation, but then the GDE is not redrawn (updatescr doesn't help) :/
		case 0:		// new file opened
		{
			cout << endl << endl << endl << endl;

			PrimImplikantCollection* globalPIC = new PrimImplikantCollection();
			vector<string>* variables = new vector<string>();

			fInput.clear();
			fInput.seekg(0, fInput.beg);
			CParser* parser = new CParser(fInput, fError, fList);
			int parseFailure = parser->yyparse(globalPIC, variables);
			delete parser;

			if (parseFailure != 0)
			{
				fileChosen = false;
				string error = "Error while parsing the input (";
				char buf[5];
				_itoa_s(parseFailure, buf, 10);
				error += buf;
				error += ")";
				perror(error.c_str());
				fError << error << endl;
				continue;
			}
	
			// initialize Cells
			CellCollection* allCells = new CellCollection(globalPIC);


			fWt.seekp(0, fWt.beg);
			// print Wertetabelle and KV of imported data
			Wertetabelle* wt = new Wertetabelle(allCells, variables, fWt);
			wt->Print();

			kv = new KV(globalPIC, allCells, 30,variables);
			kv->Print(30);


			// find and solve Hazards
			allCells->findHazards();


			if (allCells->hazardsFound)
				// print Wertetabelle and KV of corrected data
				wt->Print();

			kv->Print(30 + kv->width() + 30, 30);	// Diagramm neben dem vorherigen

			kv->Buttons();
			
			delete wt;
			wt = NULL;
			
			globalPIC->Dispose();
			delete globalPIC;
			globalPIC = NULL;
			
			allCells->Dispose();
			delete allCells;
			allCells = NULL;
			delete variables;
			variables = NULL;
			break;}
		}

		if (kv->StopProcess())
		{
			if (kv != NULL)
			delete kv;
			kv = NULL;
			fInput.close();
			fList.close();
			fError.close();
			fWt.close();
			fileChosen = false;
			break;
		}
	}
}