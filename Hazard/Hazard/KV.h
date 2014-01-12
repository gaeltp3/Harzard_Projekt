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
private:
	PrimImplikantCollection* globalPic;	// Globale PrimImplikantCollection
	CellCollection* allCells;			// Alle Zellen
	vector<string>* variables;			// Variablennamen
	

	uint offsetX;						// Der freie Platz links vom KV-Diagramm in Pixeln
	uint offsetY;						// Der freie Platz oben  vom KV-Diagramm in Pixeln

	const uint edgeLength;				// Die Kantenlänge der einzelnen Felder

	const uint numVarX;					// Wieviele Variablen in X-Richtung gezeichnet werden
	const uint numVarY;					// Wieviele Variablen in Y-Richtung gezeichnet werden
	const uint numFieldX;				// Wieviele Felder in X-Richtung gezeichnet werden = pow(2, numVarX)
	const uint numFieldY;				// Wieviele Felder in Y-Richtung gezeichnet werden = pow(2, numVarY)
	uint widthPx;						// Breite des KV-Diagramms in Pixeln
	uint heightPx;						// Höhe   des KV-Diagramms in Pixeln
	uint VarX_Length;					// Höhe   der Variablenzeile (oben)   in Pixeln
	uint VarY_Length;					// Breite der Variablenspalte (links) in Pixeln
	string string_VarX;					// Variablen String oben
	string string_VarY;					// Variablen String links

	void Setstring_Var();				// Initialisieren von VarX/Y_Length und string_VarX/Y
	void PrintRaster();					// Erstellt die Felder/das Raster
	void PrintVariables();				// Erstellt die Werte der Variablen in der ersten Zeile und der ersten Spalte
	void PrintCellValues();				// Erstellt die Werte in den jeweiligen Zellen
	void PrintPrimImplikanten();		// Generiert die einzelnen PrimImplikanten-Kuller (Gruppen)
	void PrintPrimImplikantenGroup(KV_PiGroup* &group, char random, uint &color);	// Druckt die einzelnen PrimImplikanten-Kuller
	void PrintString_Var();				// Erstellt den horizontalen & vertikalen Text mit Variablennamen
	
	
	
	void Clear();						// Löscht die GDE

	void Line(uint x1, uint y1, uint x2, uint y2, int color);						// Zeichnet eine Linie mit Offset
	void Text(uint x, uint y, uint size, int color, int bkcolor, int angle, char* theText);	// Zeichnet einen Text mit Offset
	void KV::TextBox(uint x1, uint y1, uint x2, uint y2, uint size, int ctext, int cframe, int cfill, int flags, char* theText);	// Zeichnet eine TextBox mit Offset
	void KV::TextBoxBold(uint x1, uint y1, uint x2, uint y2, uint size, int ctext, int cframe, int cfill, int flags, char* theText);	// Zeichnet eine TextBox mit Offset und fetter Schrift
	void KV::Rectangle(uint x1, uint y1, uint x2, uint y2, int cframe, int cfill);	// Zeichnet ein Rechteck mit Offset

public:
	void Print(uint offset);							// Ausgabe-Methode, KV-Diagramm an der Position [offset  | offset]
	void Print(uint offsetX, uint offsetY);				// Ausgabe-Methode, KV-Diagramm an der Position [offsetX | offsetY]
	uint width();										// Gibt die Breite eines KV-Diagramms zurück (widthPx)
	uint height();										// Gibt die Höhe   eines KV-Diagramms zurück (heightPx)

	void Buttons();										// Zeichnet Buttons und wartet auf user input
	bool StopProcess();									// Prüft das stop flag der GDE

	/// <summary>
	/// Konstruktor von KV
	/// </summary>
	/// <param name="globalPic">Globale PrimImplikantCollection</param>
	/// <param name="allCells">Alle Zellen (CellCollection)</param>
	/// <param name="size">Die Kantenlänge eines Feldes (Rastergröße)</param>
	/// <param name="variables">Variablennamen</param>
	KV(PrimImplikantCollection* globalPic, CellCollection* allCells, uint size, vector<string>* &variables)
		: edgeLength(size),	// Kantenlänge festlegen
		numVarX(((uint)floor(dimension / 2.0f))),	// Anzahl der Variablen in X- und Y-Richtung festlegen
		numVarY(((uint) ceil(dimension / 2.0f))),	
		numFieldX((uint)pow(2, (float)numVarX)),	// Anzahl der Felder in X- und Y-Richtung festlegen
		numFieldY((uint)pow(2, (float)numVarY))		// = 2 ^ numVar
	{
		this->globalPic = globalPic;
		this->allCells = allCells;
		this->variables = variables;
		this->Setstring_Var();						// Initialisiert VarY_Length und VarX_Length
		this->widthPx = numFieldX * (this->edgeLength + 1) + this->VarY_Length;	// Breite eines KV-Diagramms
		this->heightPx = numFieldY * (this->edgeLength + 1) + this->VarX_Length;// Höhe   eines KV-Diagramms

		this->Clear();								// GDE löschen
	}

};

#ifndef CENTER
#define CENTER SINGLE_LINE|CENTER_ALIGN|VCENTER_ALIGN
#endif