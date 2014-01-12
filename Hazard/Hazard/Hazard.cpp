#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include "CParser.h"
#include "PrimImplikant.h"
#include "PrimImplikantCollection.h"
#include "CellCollection.h"
#include "Wertetabelle.h"
#include "KV.h"

using namespace std;

uint dimension = 0;			// number of variables = variables.size()
uint numElements = 0;		// number of elements/cells = 2 ^ dimension
bool KNF = false;			// Is the output in KNF or DNF. This is only used for output. All calc is done in DNF
bool fileChosen = false;	// Whether the input file shall be opened again next time
char fnInput[256];			// The path to the input file

/// <summary>
/// <para>Takes care of opening the input and output file streams.</para>
/// <para>It also asks the user to select the input file using GetOpenFileName</para>
/// </summary>
/// <param name="input">The input file where we will read the data from</param>
/// <param name="error">The parser error log file</param>
/// <param name="list">The parser listing log file</param>
/// <param name="wt">The output file for the Wertetabelle</param>
/// <returns>An error code:
/// - 0, 9:	Everything fine
/// - 1:	File open error
/// - 2:	User aborted GetOpenFileName
/// </returns>
int open_files(ifstream &input, ofstream &error, ofstream &list, ofstream &wt)
{
	if (fileChosen == true)							// do not reopen files
		return 9;

	GetCurrentDirectory(sizeof(fnInput), fnInput);	// returns the current working directory

	if (!error.is_open())							// if we have not opened the parser error log file before
	{
		char fnError[256];							// create path: .\res\errorParser.txt
		strcpy_s(fnError, (string(fnInput) + "\\res\\errorParser.txt").c_str());
		error.open(fnError, ofstream::out|ofstream::app);
		if (!error.is_open())
		{
			perror("Fehler beim Öffnen der Fehlerdatei");
			return 1;
		}
	}
	if (!list.is_open())							// if we have not opened the parser listing log file before
	{
		char fnLists[256];							// create path: .\res\listParser.txt
		strcpy_s(fnLists, (string(fnInput) + "\\res\\listParser.txt").c_str());
		list.open(fnLists, ofstream::out|ofstream::trunc);
		if (!list.is_open())
		{
			perror("Fehler beim Öffnen der Listdatei");
			return 1;
		}
	}
	if (!wt.is_open())							// if we have not opened the Wertetabelle file before
	{
		char fnWt[256];							// create path: .\res\Wertetabelle.txt
		strcpy_s(fnWt, (string(fnInput) + "\\res\\Wertetabelle.txt").c_str());
		wt.open(fnWt, ofstream::out|ofstream::trunc);
		if (!wt.is_open())
		{
			perror("Fehler beim Öffnen der Wertetabellendatei");
			return 1;
		}
	}

	strcpy_s(fnInput, (string(fnInput) + "\\res\\input.txt").c_str());	// create initial input path: .\res\input.txt

	OPENFILENAME ofn;							// create OPENFILENAME structure for Windows method
	ZeroMemory(&ofn, sizeof(ofn));				// zero everything
	ofn.lStructSize = sizeof(ofn);				// tell windows the size of the struct
	ofn.hwndOwner = NULL;						// we do not have a window handle (perhaps GDE does?)
	ofn.lpstrFile = fnInput;					// input file path
	ofn.nMaxFile = sizeof(fnInput);				// maximum input file path length
	ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";// selection filter
	ofn.nFilterIndex = 1;						// default selected filter
	ofn.lpstrFileTitle = NULL;					
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) != TRUE)			// if the user aborted GetOpenFileName or something else went wrong
	{
		cout << "Auswahl der Inputdatei abgebrochen!";
		return 2;
	}
	fileChosen = true;							// do not reload input file next time again

	if (input.is_open())						// if a input file was opened before
		input.close();							// close it
	input.open(fnInput, ifstream::in);			// and then open the new file
	if (!input.is_open())
	{
		perror("Fehler beim Lesen der Inputdatei");
		return 1;
	}

	return 0;
}

/// <summary>
/// <para>The main user function that is called by the GDE.</para>
/// <para>It is running in a global while and performs all calculation.</para>
void user_main(void)
{
	ifstream fInput;					// the input file
	ofstream fError, fList, fWt;		// some output files: parser error, parser listing, Wertetabelle
	KV* kv;								// pointer to KV class
	while(1)
	{
		switch(open_files(fInput, fError, fList, fWt))	// try to open the file streams
		{
		case 1:							// some error
			fileChosen = false;
			perror("Error while opening a file (1)");
			continue;
		case 2:							// user aborted GetOpenFileName
			ExitProcess(2);				// we do not tolerate those users! :>
			break;
		case 9:							// same input file as before
										// We could skip recalculation, but then the GDE is not redrawn (updatescr only doesn't help. And since we are not storing the PrimImplikantCollection without solved Hazards we have to do everything again) :/
		case 0:							// new file opened
		{
			cout << endl << endl << endl << endl;

			PrimImplikantCollection* globalPIC = new PrimImplikantCollection();	// a new collection of PrimImplikants
			vector<string>* variables = new vector<string>();					// a collection with the variable names

			fInput.clear();
			fInput.seekg(0, fInput.beg);										// rewind fInput
			CParser* parser = new CParser(fInput, fError, fList);				// init our parser
			int parseFailure = parser->yyparse(globalPIC, variables);			// parse the specified file, write data into globalPIC and variables
			delete parser;														// we do not need it anymore
			parser = NULL;

			if (parseFailure != 0)												// something went wrong
			{
				fileChosen = false;												// let  the user select a new file next time
				string error = "Error while parsing the input (";				// create a string with the error
				char buf[5];
				_itoa_s(parseFailure, buf, 10);
				error += buf;
				error += ")";
				perror(error.c_str());
				fError << error << endl;
				continue;														// start over again
			}
	

			CellCollection* allCells = new CellCollection(globalPIC);			// initialize our Cells collection


			fWt.seekp(0, fWt.beg);												// rewind fWt
			// print Wertetabelle and KV of imported data
			Wertetabelle* wt = new Wertetabelle(allCells, variables, fWt);		// init Wertetabelle
			wt->Print();														// print Wertetabelle to console and fWt

			kv = new KV(globalPIC, allCells, 30,variables);						// init KV
			kv->Print(30);														// print KV diagram at offset 30,30


			allCells->findHazards();											// find and solve Hazards
																				// this is the actual hazard detection and resolving algorithm


			if (allCells->hazardsFound)
				wt->Print();													// print Wertetabelle of corrected data

			kv->Print(30 + kv->width() + 30, 30);								// print KV of corrected data
																				// this KV is next to previous KV

			
										// if we would not recalculate everything we could save this stuff:
			delete wt;					// but as it is now we do not need it anymore. Let's delete it so it won't take any memory
			wt = NULL;
			
			globalPIC->Dispose();		// delete all PrimImplikanten in globalPIC (= all PrimImplikanten)
			delete globalPIC;			// Dispose() could not be moved to ~destructor since we are using this class at several other points where it get's destroyed again. And we want to keep our PrimImplikanten
			globalPIC = NULL;
			
			allCells->Dispose();		// it's the same with our Cells
			delete allCells;
			allCells = NULL;
			delete variables;			// also the variables can be deleted
			variables = NULL;
		
			kv->Buttons();				// Print the GDE buttons and wait for user input
			}
		}

		if (kv->StopProcess())			// user want's to stop us
		{
			if (kv != NULL)				// delete KV class here, we did need it for the buttons
				delete kv;
			kv = NULL;
			fInput.close();
			fList.close();
			fError.close();
			fWt.close();
			fileChosen = false;
			break;
		}

		if (kv != NULL)					// delete KV class here, we did need it for the buttons
				delete kv;
		kv = NULL;
	}
}