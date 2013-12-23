#include "stdafx.h"
#include <vector>
#include "Cell.h"
#include "PrimImplikantCollection.h"
#include "..\..\GDE_3_2008\graphics\graphicfunctions.h"
#include "KV.h"

extern uint dimension;
extern uint numElements;
extern bool KNF;

using namespace std;


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
	this->PrintString_Var();
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

void KV::Setstring_Var()
{
	this->string_VarY = "";
	this->string_VarX = "";

	for (uint i = 0; i < this->variables->size(); i++)
	{
		if (i >= this->numVarY)
			this->string_VarX += this->variables->at(i) + " ";
		else
			this->string_VarY += this->variables->at(i) + " ";
	}
	this->string_VarX = this->string_VarX.substr(0, this->string_VarX.size()-1);
	this->string_VarY = this->string_VarY.substr(0, this->string_VarY.size()-1);

	// Weitere Initialisierung der restlichen privaten Klassenelemente.
	
	this->VarX_Length = max(this->edgeLength+1, this->string_VarX.size() * 9);
	this->VarY_Length = max(this->edgeLength+1, this->string_VarY.size() * 9);
}

void KV::PrintRaster()	// Erstellt die Felder:	▯▯▯
{						//						▯▯▯
						//						▯▯▯

	this->Line(this->VarY_Length, 0, this->VarY_Length, this->heightPx, BLACK); // first  vertical line, one edge shorter
	this->Line(0, this->VarX_Length, 0, this->heightPx, BLACK);					// second vertical line
	for (uint w = 1; w <= this->numFieldX ; w++)								// vertical lines. Periodic with (edgeLength + 1)
	{
		uint X = w * (this->edgeLength + 1) + VarY_Length;						// X position of the line
		this->Line(X, 0, X, this->heightPx, BLACK);
	}


	this->Line(this->VarY_Length, 0, this->widthPx, 0, BLACK);					// first horizontal line, one edge shorter
	this->Line(0, this->VarX_Length, this->widthPx, this->VarX_Length, BLACK);	// +10 to avoid the strings collision
																				// second horizontal line
	for (uint h = 1; h <= this->numFieldY ; h++)								// horizontal lines. Periodic with (edgeLength + 1)
	{
		uint Y = h * (this->edgeLength + 1) + this->VarX_Length;				// Y position of the line
		this->Line(0, Y, this->widthPx, Y, BLACK);
	}
}

void KV::PrintString_Var()
{
	char* valueY = (char*)this->string_VarY.c_str();
	char* valueX= (char*)this->string_VarX.c_str();
	uint x1_valueY = 2;															// coordinante of ValueY
	uint y1_valueY = this->VarX_Length-16;

	uint x1_valueX = this->VarY_Length-16;										// coordinante of ValueX
	uint y1_valueX = this->VarX_Length-12;

	this->Text(x1_valueX, y1_valueX, 10, BLACK, WHITE, 90, 0, valueX);
	this->Text(x1_valueY, y1_valueY, 10, BLACK, WHITE, 00, 0, valueY);
}

void KV::PrintVariables()	// Erstellt die Werte der Variablen in der ersten X- und Y-Spalte:	 ▯ 0 1
{							//																	 0 ▯▯
							//																	 1 ▯▯
	for (uint w = 0; w < this->numFieldX; w++)						// horizontal variable text
	{
		uint XL = w * (this->edgeLength + 1) + this->VarY_Length;
		uint XR = XL + this->edgeLength;
		char* value = this->Binary(w ^ (w / 2), this->numVarX);		// in Gray und String umwandeln
		this->TextBoxBold(XL, 0, XR, this->VarX_Length, 10, BLACK, TRANS, TRANS, SINGLE_LINE|CENTER_ALIGN|BOTTOM_ALIGN, value);
		delete value;
	}


	for (uint h = 0; h < this->numFieldY; h++)						// vertical variable text
	{
		uint YT = h * (this->edgeLength + 1) + this->VarX_Length + 1;
		uint YB = YT + this->edgeLength;
		char* value = this->Binary(h ^ (h / 2), this->numVarY);		// in Gray und String umwandeln
		this->TextBoxBold(0, YT, this->VarY_Length-5, YB, 10, BLACK, TRANS, TRANS, SINGLE_LINE|RIGHT_ALIGN|VCENTER_ALIGN, value);
		delete value;
	}
}

//---------------------------------------------------------------
void KV::PrintCellValues()	// Erstellt die Werte der jeweiligen Zellen: ▯▯▯
{							//											 ▯ x x
						   //											 ▯ x x
	for (uint h = 0; h < this->numFieldY; h++)							// jede Spalte durchgehen
	{
		uint YT = h * (this->edgeLength + 1)+ this->VarX_Length;		// Y Positionen berechnen
		uint YB = YT + this->edgeLength;

		for (uint w = 0; w < this->numFieldX; w++)						// jede Zeile durchgehen
		{
			uint XL = w * (this->edgeLength + 1) + this->VarY_Length;	// X Positionen berechnen
			uint XR = XL + this->edgeLength;

			uint i = ((h^h / 2) << this->numVarX) | (w^w / 2);			// w und h müssen getrennt in Gray umgewandelt werden (weil sie so aufgetragen wurden)
			// zusammengesetzt ergeben sie dann unsere aktuelle Position

			// Dies sind die Zellnummern:
			/*
			char* I = new char[(int)(ceil(log10((float)numElements)))+1];
			itoa(i, I, 10);
			this->TextBox(XL, YT, XR, YB, 10, BLACK, TRANSPARENT, TRANSPARENT, CENTER, I);
			*/

			// Dies sind die Zellwerte:
			char* I = new char[2];
			_itoa_s(this->allCells->at(i)->value, I, 2, 10);
			this->TextBox(XL, YT, XR, YB, 10, BLACK, TRANS, TRANS, CENTER, I);
			delete I;
		}
	}
}


void KV::PrintPrimImplikanten()
{
	srand(time(NULL) + rand());
	for (uint i = 0; i < this->globalPic->size(); i++)
	{
		PrimImplikant* currentPI = this->globalPic->at(i);

		/*uint overflow = 0;													// at which sides the PrimImplikant overlaps
		for (uint j = 0; j < currentPI->implikanten.size(); j++)
		{
		uint currentI = currentPI->implikanten[j];
		uint w = (currentI & ((0x1 << (this->numVarX)) - 1));			// get all bits that make X (=w)
		w ^= w / 2;
		uint h = (currentI >> this->numVarX);							// get all bits that make Y (=h)
		h ^= h / 2;

		if (w == 0)
		overflow |= 0x1;											// left side
		else if (w == this->numFieldX - 1)
		overflow |= 0x2;											// right side
		else
		overflow |= 0x4;

		if (h == 0)
		overflow |= 0x10;											// upper side
		else if (h == this->numFieldY - 1)
		overflow |= 0x20;											// lower side
		else
		overflow |= 0x40;
		}

		switch (overflow)
		{
		case 0x33:															// all 4 edges
		break;
		case 0x30:															// overflows from top to bottom
		break;
		case 0x03:															// overflows from left to right
		break;
		default:

		*/

		// ab hier mache ich später weiter. Ich habe wieder Kopfschmerzen!!!



		// uint X1 = -1, X2 = 0, Y1 = -1, Y2 = 0;							// find coordinates for Rechteck


		for (uint j = 0; j < currentPI->PI_groupCollection.size(); j++)
		{
			 

			vector<Implikant_localisation*>* kullers = currentPI->PI_groupCollection[j]; 


			for (uint k = 0; k < kullers->size(); k++)
			{

				for (vector<Implikant_localisation*>::iterator it = kullers->begin(); it < kullers->end(); it++)
				{
					uint X1 = -1, X2 = 0, Y1 = -1, Y2 = 0;

					uint x1 = (*it)->w  * (this->edgeLength + 1) + this->VarY_Length;					// Upper coord
					uint x2 = x1 + this->edgeLength;							// Lower coord
					uint y1 = (*it)->h * (this->edgeLength + 1) + this->VarX_Length;					// Left  coord
					uint y2 = y1 + this->edgeLength;							// Right coo

					X1 = min(X1, x1);
					X2 = max(X2, x2);
					Y1 = min(Y1, y1);
					Y2 = max(Y2, y2);

					if (currentPI->name.find("|") != string::npos)
					{
						this->Rechteck(X1 + 12, Y1 + 9, X2 - 12, Y2 - 9, RED, TRANS);
					}
					else
					{
						uint random = rand() % 10;
						X1 += random;
						X2 -= random;
						Y1 += random;
						Y2 -= random;
						if (currentPI->implikanten.size() == 1)
							this->Rechteck(X1, Y1, X2, Y2, GREEN, TRANS);
						else
							this->Rechteck(X1, Y1, X2, Y2, BLUE, TRANS);
					}




				}
				



			}

		}
	}
}

				


/*


				uint w = currentPI->PI_groupCollection		// get all bits that make X (=w)
				w ^= w / 2;
				uint h = (currentI >> this->numVarX);						// get all bits that make Y (=h)
				h ^= h / 2;

				uint x1 = w  * (this->edgeLength + 1) + this->VarY_Length;					// Upper coord
				uint x2 = x1 + this->edgeLength;							// Lower coord
				uint y1 = h * (this->edgeLength + 1) + this->VarX_Length;					// Left  coord
				uint y2 = y1 + this->edgeLength;							// Right coo

				X1 = min(X1, x1);
				X2 = max(X2, x2);
				Y1 = min(Y1, y1);
				Y2 = max(Y2, y2);
			}

			if (currentPI->name.find("|") != string::npos)
			{
				this->Rechteck(X1 + 12, Y1 + 9, X2 - 12, Y2 - 9, RED, TRANS);
			}
			else
			{
				uint random = rand() % 10;
				X1 += random;
				X2 -= random;
				Y1 += random;
				Y2 -= random;
				if (currentPI->implikanten.size() == 1)
					this->Rechteck(X1, Y1, X2, Y2, GREEN, TRANS);
				else
					this->Rechteck(X1, Y1, X2, Y2, BLUE, TRANS);
			}
		}
	}
}

//------------------------------------------------------------------


*/


		



			
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
	textbox(x1 + this->offsetX + 2, y1 + this->offsetY, x2 + this->offsetX + 2, y2 + this->offsetY, size, ctext, TRANS, TRANSPARENT, flags, theText);		// write twice to simulate bold font
}

void KV::Rechteck(uint x1, uint y1, uint x2, uint y2, int cframe, int cfill)
{
	rectangle(x1 + this->offsetX + 1, y1 + this->offsetY + 1, x2 + this->offsetX + 1, y2 + this->offsetY + 1, cframe, cfill);
}



char* KV::Binary(uint x, char length)
{
	// warning: this breaks for numbers with more than 64 bits
	char* buffer = new char[length+1];
	char* p = buffer + length;

	*p = 0;
	do
	{
		*--p = '0' + (x & 1);
		x >>= 1;
	} while (--length);

	return buffer;
}