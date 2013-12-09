#include "stdafx.h"
#include <vector>
#include <string>
#include "Cell.h"
#include "CellCollection.h"
#include "PrimImplikantCollection.h"

extern uint dimension;
extern uint numElements;
extern bool KNF;


#ifndef _KV_H
#define _KV_H

class KV
{
public:
	void Print(uint offset);							// Ausgabe-Methode, KV-Diagramm an der Position [offset  | offset]
	void Print(uint offsetX, uint offsetY);				// Ausgabe-Methode, KV-Diagramm an der Position [offsetX | offsetY]
	uint width();										// Gibt die Breite eines KV-Diagramms zurück (widthPx)
	uint height();										// Gibt die Höhe   eines KV-Diagramms zurück (heightPx)

	// Konstruktor
	KV(PrimImplikantCollection* globalPic, CellCollection* allCells, uint size) 
	  :	edgeLength(size),
		numVarX(((uint)floor(dimension/2.0f))), numVarY(((uint)ceil(dimension/2.0f))),
		numFieldX((uint)pow(2,(float)numVarX)), numFieldY((uint)pow(2,(float)numVarY)),
		widthPx((numFieldX + 1) * (this->edgeLength + 1)), heightPx((numFieldY + 1) * (this->edgeLength + 1))
	{
		this->globalPic = globalPic;
		this->allCells = allCells;
		this->Clear();
	}

private:
	PrimImplikantCollection* globalPic;
	CellCollection* allCells;

	uint offsetX;						// Der freie Platz nach links in Pixeln
	uint offsetY;						// Der freie Platz nach rechts in Pixeln
	const uint edgeLength;				// Die Kantenlänge der einzelnen Felder

	const uint numVarX;					// Wieviele Variablen in X-Richtung gezeichnet werden
	const uint numVarY;					// Wieviele Variablen in Y-Richtung gezeichnet werden
	const uint numFieldX;				// Wieviele Felder in X-Richtung gezeichnet werden = pow(2, numVarX)
	const uint numFieldY;				// Wieviele Felder in Y-Richtung gezeichnet werden = pow(2, numVarY)
	const uint widthPx;					// Breite des KV-Diagramms in Pixeln
	const uint heightPx;				// Höhe   des KV-Diagramms in Pixeln

	void PrintRaster();					// Erstellt die Felder
	void PrintVariables();				// Erstellt die Werte der Variablen in der ersten X- und Y-Spalte
	void PrintCellValues();				// Erstellt die Werte der jeweiligen Zellen
	void PrintPrimImplikanten();		// Erstellt die einzelnen Primimplikanten
	
	void Clear();
	void Line(uint x1, uint y1, uint x2, uint y2, int color);																			// Zeichnet eine Linie mit Offset
	void Text(uint x, uint y, uint size, int color, int bkcolor, int angle, int align, char* theText);									// Zeichnet einen Text mit Offset
	void KV::TextBox(uint x1, uint y1, uint x2, uint y2, uint size, int ctext, int cframe, int cfill, int flags, char* theText);		// Zeichnet eine TextBox mit Offset
	void KV::TextBoxBold(uint x1, uint y1, uint x2, uint y2, uint size, int ctext, int cframe, int cfill, int flags, char* theText);		// Zeichnet eine TextBox mit Offset und fetter Schrift
	void KV::Rechteck(uint x1, uint y1, uint x2, uint y2, int cframe, int cfill);		// Zeichnet ein Rechteck mit Offset und fetter Schrift

	char* Binary(uint x, char length);	// Wie itoa(x, char[], 2), allerdings mit fester Breite
};


#define CENTER SINGLE_LINE|CENTER_ALIGN|VCENTER_ALIGN
#endif