#pragma once

#include "stdafx.h"
#include <vector>
#include <string>
#include "Cell.h"
#include "CellCollection.h"
#include "KV_PiGroup.h"
#include "PrimImplikantCollection.h"

extern uint dimension;
extern uint numElements;
extern bool KNF;

class KV
{
public:
	void Print(uint offset);							// Ausgabe-Methode, KV-Diagramm an der Position [offset  | offset]
	void Print(uint offsetX, uint offsetY);				// Ausgabe-Methode, KV-Diagramm an der Position [offsetX | offsetY]
	uint width();										// Gibt die Breite eines KV-Diagramms zurück (widthPx)
	uint height();										// Gibt die Höhe   eines KV-Diagramms zurück (heightPx)

	void Buttons();
	bool StopProcess();

	// Konstruktor
	KV(PrimImplikantCollection* globalPic, CellCollection* allCells, uint size, vector<string>* &variables)
		: edgeLength(size),
		numVarX(((uint)floor(dimension / 2.0f))), numVarY(((uint)ceil(dimension / 2.0f))),
		numFieldX((uint)pow(2, (float)numVarX)), numFieldY((uint)pow(2, (float)numVarY))
	{
		this->globalPic = globalPic;
		this->allCells = allCells;
		this->variables = variables;
		Setstring_Var();
		this->widthPx = numFieldX * (this->edgeLength + 1) + this->VarY_Length;
		this->heightPx = numFieldY * (this->edgeLength + 1) + this->VarX_Length;

		this->Clear();
	}

private:
	PrimImplikantCollection* globalPic;
	CellCollection* allCells;
	vector<string>* variables;
	

	uint offsetX;						// Der freie Platz nach links in Pixeln
	uint offsetY;						// Der freie Platz nach rechts in Pixeln

	const uint edgeLength;				// Die Kantenlänge der einzelnen Felder

	const uint numVarX;					// Wieviele Variablen in X-Richtung gezeichnet werden
	const uint numVarY;					// Wieviele Variablen in Y-Richtung gezeichnet werden
	const uint numFieldX;				// Wieviele Felder in X-Richtung gezeichnet werden = pow(2, numVarX)
	const uint numFieldY;				// Wieviele Felder in Y-Richtung gezeichnet werden = pow(2, numVarY)
	uint widthPx;						// Breite des KV-Diagramms in Pixeln
	uint heightPx;						// Höhe   des KV-Diagramms in Pixeln
	uint VarX_Length;					// Höhe der Variablen in X-Richtung in Pixeln
	uint VarY_Length;					// Breite der Variablen in Y-Richtung in Pixeln
	string string_VarX;					// Variables_String in X-Richtung
	string string_VarY;					// Variables_String in Y-Richtung	 

	void Setstring_Var();				// Einfuegen von String_Varx & String_VarY mit Variables.
	void PrintRaster();					// Erstellt die Felder
	void PrintVariables();				// Erstellt die Werte der Variablen in der ersten X- und Y-Spalte
	void PrintCellValues();				// Erstellt die Werte der jeweiligen Zellen
	void PrintPrimImplikanten();		// Generiert die einzelnen PrimImplikanten-Kuller (Gruppen)
	void PrintPrimImplikantenGroup(KV_PiGroup* &group, char random, uint &color);	// Erstellt die einzelnen PrimImplikanten-Kuller
	void PrintString_Var();				// Erstellt den horizontalen TextVariable & vertikalen Textvariable
	
	
	
	void Clear();

	void Line(uint x1, uint y1, uint x2, uint y2, int color);																			// Zeichnet eine Linie mit Offset
	void Text(uint x, uint y, uint size, int color, int bkcolor, int angle, int align, char* theText);									// Zeichnet einen Text mit Offset
	void KV::TextBox(uint x1, uint y1, uint x2, uint y2, uint size, int ctext, int cframe, int cfill, int flags, char* theText);		// Zeichnet eine TextBox mit Offset
	void KV::TextBoxBold(uint x1, uint y1, uint x2, uint y2, uint size, int ctext, int cframe, int cfill, int flags, char* theText);		// Zeichnet eine TextBox mit Offset und fetter Schrift
	void KV::Rechteck(uint x1, uint y1, uint x2, uint y2, int cframe, int cfill);		// Zeichnet ein Rechteck mit Offset und fetter Schrift

	char* Binary(uint x, char length);	// Wie itoa(x, char[], 2), allerdings mit fester Breite
};


#define CENTER SINGLE_LINE|CENTER_ALIGN|VCENTER_ALIGN