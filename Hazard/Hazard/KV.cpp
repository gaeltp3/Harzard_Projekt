#include "stdafx.h"
#include <vector>
#include "Cell.h"
#include "PrimImplikantCollection.h"
#include "..\..\GDE_3_2008\graphics\graphicfunctions.h"
#include "KV.h"

extern uint dimension;
extern uint numElements;
extern bool KNF;


void KV::Clear()
{
	int ww, hh;
	get_windowsize(&ww,&hh);
	set_drawarea(ww,hh);				// Setzen des Zeichenbereiches
	clrscr();							// Clear screen
}

void KV::Print(uint offset)
{
	this->Print(offset, offset);
}
void KV::Print(uint offsetX, uint offsetY)
{
	this->offsetX = offsetX;
	this->offsetY = offsetY;

	this->PrintRaster();
	this->PrintVariables();
	this->PrintCellValues();
	this->PrintPrimImplikanten();
	
	updatescr();						// make this f****** GDE update, does not work everytime :/
}

uint KV::width()
{
	return this->widthPx;
}
uint KV::height()
{
	return this->heightPx;
}



void KV::PrintRaster()	// Erstellt die Felder:	▯▯▯
{						//						▯▯▯
						//						▯▯▯
	this->Line(0, this->edgeLength, 0, heightPx, BLACK);			// first vertical line, one edge shorter
	for (uint w = 1; w <= this->numFieldX + 1; w++)					// vertical lines. Periodic with (edgeLength + 1)
	{
		uint X = w * (this->edgeLength + 1);						// X position of the line
		this->Line(X, 0, X, this->heightPx, BLACK);
	}


	this->Line(this->edgeLength, 0, widthPx, 0, BLACK);				// first horizontal line, one edge shorter
	for (uint h = 1; h <= this->numFieldY + 1; h++)					// horizontal lines. Periodic with (edgeLength + 1)
	{
		uint Y = h * (this->edgeLength + 1);						// Y position of the line
		this->Line(0, Y, this->widthPx, Y, BLACK);
	}
}

void KV::PrintVariables()	// Erstellt die Werte der Variablen in der ersten X- und Y-Spalte:	 ▯ 0 1
{							//																	 0 ▯▯
							//																	 1 ▯▯
	for (uint w = 0; w < this->numFieldX; w++)					// vertical variable text
	{
		uint XL = (w + 1) * (this->edgeLength + 1);
		uint XR = XL + this->edgeLength;
		char* value = this->Binary(w^(w/2), this->numVarX);		// in Gray und String umwandeln
		this->TextBoxBold(XL, 0, XR, this->edgeLength, 10, BLACK, TRANSPARENT, TRANSPARENT, CENTER, value);
		delete value;
	}


	for (uint h = 0; h < this->numFieldY; h++)					// horizontal variable text
	{
		uint YT = (h + 1) * (this->edgeLength + 1);
		uint YB = YT + this->edgeLength;
		char* value = this->Binary(h^(h/2), this->numVarY);		// in Gray und String umwandeln
		this->TextBoxBold(0, YT, this->edgeLength, YB, 10, BLACK, TRANSPARENT, TRANSPARENT, CENTER, value);
		delete value;
	}
}

void KV::PrintCellValues()	// Erstellt die Werte der jeweiligen Zellen: ▯▯▯
{							//											 ▯ x x
							//											 ▯ x x
	for (uint h = 0; h < this->numFieldY; h++)					// jede Spalte durchgehen
	{
		uint YT = (h + 1) * (this->edgeLength + 1);				// Y Positionen berechnen
		uint YB = YT + this->edgeLength;	

		for (uint w = 0; w < this->numFieldX; w++)				// jede Zeile durchgehen
		{
			uint XL = (w + 1) * (this->edgeLength + 1);			// X Positionen berechnen
			uint XR = XL + this->edgeLength;

			uint i = ((h^h/2) * this->numFieldX) | (w^w/2);		// w und h müssen getrennt in Gray umgewandelt werden (weil sie so aufgetragen wurden, siehe )
																// zusammengesetzt ergeben sie dann unsere aktuelle Position

			// Dies sind die Zellnummern:
			/*
			char* I = new char[(int)(ceil(log10((float)numElements)))+1];
			itoa(i, I, 10);
			this->TextBox(XL, YT, XR, YB, 10, BLACK, TRANSPARENT, TRANSPARENT, CENTER, I);
			*/

			// Dies sind die Zellwerte:
			char* I = new char[2];
			itoa(this->allCells[i]->value, I, 10);
			this->TextBox(XL, YT, XR, YB, 10, BLACK, TRANSPARENT, TRANSPARENT, CENTER, I);
			delete I;
		}
	}
}

void KV::PrintPrimImplikanten()
{
	for (uint i = 0; i < this->globalPic->size(); i++)
	{
	}
}





void KV::Line(uint x1, uint y1, uint x2, uint y2, int color)
{
	line(x1 + this->offsetX, y1 + this->offsetY, x2 + this->offsetX, y2 + this->offsetY, color);
}

void KV::Text(uint x, uint y, uint size, int color, int bkcolor, int angle, int align, char* theText)
{
	text(x + this->offsetX, y + this->offsetY, size, color, bkcolor, angle, align, theText);
}

void KV::TextBox(uint x1, uint y1, uint x2, uint y2, uint size, int ctext, int cframe, int cfill, int flags, char* theText)
{
	textbox(x1 + this->offsetX + 1, y1 + this->offsetY, x2 + this->offsetX + 1, y2 + this->offsetY, size, ctext, cframe, cfill, flags, theText);
}

void KV::TextBoxBold(uint x1, uint y1, uint x2, uint y2, uint size, int ctext, int cframe, int cfill, int flags, char* theText)
{
	textbox(x1 + this->offsetX + 1, y1 + this->offsetY, x2 + this->offsetX + 1, y2 + this->offsetY, size, ctext, cframe, cfill, flags, theText);
	textbox(x1 + this->offsetX + 2, y1 + this->offsetY, x2 + this->offsetX + 2, y2 + this->offsetY, size, ctext, TRANSPARENT, TRANSPARENT, flags, theText);		// write twice to simulate bold font
}



char* KV::Binary(uint x, char length)
{
    // warning: this breaks for numbers with more than 64 bits
    char* buffer = new char[length+1];
    char* p = buffer + length;

	*p-- = 0;
    do
    {
        *p-- = '0' + (x & 1);
		x >>= 1;
    } while (--length);

    return buffer;
}