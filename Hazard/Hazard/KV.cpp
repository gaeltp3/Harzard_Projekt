#include "stdafx.h"
#include <vector>
#include "Cell.h"
#include "PrimImplikantCollection.h"
#include "..\..\GDE_3_2008\graphics\graphicfunctions.h"
#include "Tools.h"
#include "KV.h"

extern uint dimension;			// number of variables
extern uint numElements;		// number of elements/fields
extern bool KNF;				// KNF/DNF
extern bool fileChosen;			// set false to open a new input file

using namespace std;

/// <summary>
/// Clears the GDE screen and adjusts the drawing area
/// </summary>
void KV::Clear()
{
	int ww, hh;
	get_windowsize(&ww,&hh);
	set_drawarea(ww,hh);
	clrscr();
}

/// <summary>
/// Prints a KV diagram at position [offset | offset]
/// </summary>
/// <param name="">The X and Y offset in px </param>
void KV::Print(uint offset)
{
	this->Print(offset, offset);
}
/// <summary>
/// Prints a KV diagram at position [offsetX | offsetY]
/// </summary>
/// <param name="offsetX">Free space to the left  side in Pixels</param>
/// <param name="offsetY">Free space to the upper side in Pixels</param>
void KV::Print(uint offsetX, uint offsetY)
{
	if (this->numVarX == 0 || this->numVarY == 0)	// Import failed
		return;

	this->offsetX = offsetX;
	this->offsetY = offsetY;

	this->PrintRaster();
	this->PrintString_Var();
	this->PrintVariables();
	this->PrintCellValues();
	this->PrintPrimImplikanten();
	
	updatescr();
}

/// <summary>
/// Returns the width of a KV diagram
/// </summary>
uint KV::width()
{
	return this->widthPx;
}
/// <summary>
/// Returns the height of a KV diagram
/// </summary>
uint KV::height()
{
	return this->heightPx;
}

/// <summary>
/// <para>Sets the variables VarXY_Length and string_VarXY</para>
/// <para>The variable names are separated by X/Y position. Then the size of the first X row and first Y column is calculated</para>
/// </summary>
void KV::Setstring_Var()
{
	this->string_VarX = "";
	this->string_VarY = "";

	for (uint i = 0; i < this->variables->size(); i++)								// für alle Variablen
	{
		if (i >= this->numVarY)														// wenn X-Zeile
			this->string_VarX += this->variables->at(i) + " ";
		else																		// wenn Y-Spalte
			this->string_VarY += this->variables->at(i) + " ";
	}
	this->string_VarX = this->string_VarX.substr(0, this->string_VarX.size()-1);	// letztes Leerzeichen löschen
	this->string_VarY = this->string_VarY.substr(0, this->string_VarY.size()-1);	// letztes Leerzeichen löschen

	this->VarX_Length = max(this->edgeLength+1, this->string_VarX.size() * 9);		// berechnen der Größe. Pro Buchstabe werden 9 Pixel geschätzt.
	this->VarY_Length = max(this->edgeLength+1, this->string_VarY.size() * 9);
}

/// <summary>
/// Generates the skeleton of a KV diagram:
/// ▯▯▯
/// ▯▯▯
/// ▯▯▯
/// </summary>
void KV::PrintRaster()
{
	this->Line(0, this->VarX_Length, 0, this->heightPx, BLACK);					// first  vertical line, one edge shorter
	for (uint w = 0; w <= this->numFieldX ; w++)								// vertical lines. Periodic with (edgeLength + 1)
	{
		uint X = w * (this->edgeLength + 1) + VarY_Length;						// X position of the line
		this->Line(X, 0, X, this->heightPx, BLACK);
	}


	this->Line(this->VarY_Length, 0, this->widthPx, 0, BLACK);					// first horizontal line, one edge shorter
	for (uint h = 0; h <= this->numFieldY ; h++)								// horizontal lines. Periodic with (edgeLength + 1)
	{
		uint Y = h * (this->edgeLength + 1) + this->VarX_Length;				// Y position of the line
		this->Line(0, Y, this->widthPx, Y, BLACK);
	}
}

/// <summary>
/// Generates the variable names in the first cell
/// █ ▯▯
/// ▯▯▯
/// ▯▯▯
/// </summary>
void KV::PrintString_Var()
{
	uint x_valueX = this->VarY_Length-16;					// coordinante of variables in first row (X)
	uint y_valueX = this->VarX_Length-12;

	uint x_valueY = 2;										// coordinante of variables in first column (Y)
	uint y_valueY = this->VarX_Length-16;

	this->Text(x_valueX, y_valueX, 10, BLACK, WHITE, 90, (char*)this->string_VarX.c_str());	// 90°, Black
	this->Text(x_valueY, y_valueY, 10, BLACK, WHITE, 00, (char*)this->string_VarY.c_str());	//  0°, Black
}

/// <summary>
/// Generates the variable values in the first row (X) and column (Y)
/// ▯ 0 1
/// 0 ▯▯
/// 1 ▯▯
/// </summary>
void KV::PrintVariables()
{
	for (uint w = 0; w < this->numFieldX; w++)								// horizontal variable text (X)
	{
		uint XL = w * (this->edgeLength + 1) + this->VarY_Length;			// left side = position of cell (see PrintRaster)
		uint XR = XL + this->edgeLength;									// right side = left side + cell size
		uint YT = 0;														// upper side = 0 (first row)
		uint YB = this->VarX_Length;										// lower side = height of first row
		char* value = Tools::BinaryToChars(w ^ w/2, this->numVarX);			// convert w in Gray and in String
		this->TextBoxBold(XL, YT, XR, YB, 10, BLACK, TRANS, TRANS, SINGLE_LINE|CENTER_ALIGN|BOTTOM_ALIGN, value);
		delete value;
	}


	for (uint h = 0; h < this->numFieldY; h++)								// vertical variable text (Y)
	{
		uint XL = 0;														// left side = 0 (first column)
		uint XR = this->VarY_Length-5;										// right side = width of column - offset to border
		uint YT = h * (this->edgeLength + 1) + this->VarX_Length + 1;		// upper side = position of cell (see PrintRaster)
		uint YB = YT + this->edgeLength;									// lower side = upper side + cell size
		char* value = Tools::BinaryToChars(h ^ (h / 2), this->numVarY);		// convert w in Gray and in String
		this->TextBoxBold(XL, YT, XR, YB, 10, BLACK, TRANS, TRANS, SINGLE_LINE|RIGHT_ALIGN|VCENTER_ALIGN, value);
		delete value;
	}
}

/// <summary>
/// Generates the values of the inner cells
/// ▯▯▯
/// ▯ x x
/// ▯ x x
/// </summary>
void KV::PrintCellValues()
{
	for (uint h = 0; h < this->numFieldY; h++)							// für jede Spalte
	{
		uint YT = h * (this->edgeLength + 1)+ this->VarX_Length;		// Y-Positionen berechnen
		uint YB = YT + this->edgeLength;

		for (uint w = 0; w < this->numFieldX; w++)						// für jede Zeile
		{
			uint XL = w * (this->edgeLength + 1) + this->VarY_Length;	// X-Positionen berechnen
			uint XR = XL + this->edgeLength;

			uint i = ((h ^ h/2) << this->numVarX) | (w ^ w/2);			// nun muss noch die aktuelle Position berechnet werden
			// hierbei werden Y und X getrennt in Gray umgewandelt und dann kombiniert

			// Dies sind die Zellnummern:
			/*
			char* I = new char[(int)(ceil(log10((float)numElements)))+1];
			itoa(i, I, 10);														// aktuelle Position zu String
			this->TextBox(XL, YT, XR, YB, 10, BLACK, TRANS, TRANS, CENTER, I);	// schreiben
			*/

			// Dies sind die Zellwerte:
			///*
			char* I = new char[2];												// nur ein Charakter
			_itoa_s(this->allCells->at(i)->value ^ KNF, I, 2, 10);				// value der Zelle XOR KNF in String
			this->TextBox(XL, YT, XR, YB, 10, BLACK, TRANS, TRANS, CENTER, I);	// schreiben
			delete I;
			//*/
		}
	}
}

/// <summary>
/// <para>Generates KV_PiGroups for every PrimImplikant and lets PrintPrimImplikantenGroup() print it</para>
/// <para>We have to use these Groups because we can only draw (and see) 2D images but we need more dimensions to display the Cells next to all their neighbors. Due to this limitation not cells may not be next to all of their neighbors which results in several groups that represent a PrimImplikant</para>
/// </summary>
void KV::PrintPrimImplikanten()
{
	srand((uint)time(NULL) ^ rand());										// give us some randomity =)
	vector<KV_PiGroup*> piGroups;											// our vector with groups

	for (uint i = 0; i < this->globalPic->size(); i++)						// for each PrimImplikant, main loop
	{
		PrimImplikant* currentPI = this->globalPic->at(i);

		uint color;															// define a color for this PrimImplikant
		char random;
		if (currentPI->name.find("|") != string::npos)						// this PrimImplikant solves a hazard
		{
			random = -1;													// save this fact in random
			uint r  = rand() % 128 + 128;
			uint gb = rand() % 100;
			color = RGB(r, gb, gb);											// some red color (r > gb, g == b)
		}
		else
		{
			random = rand() % 10;											// get some random number [0;9]
			uint r, g, b;
			do
			{
				r = rand() % 256;											// get some random colors
				g = rand() % 256;
				b = rand() % 256;
			}
			while (
						(r + g + b) / 3 > 200 ||							// but avoid too light colors
						r > g + b && (int)abs((int)g - (int)b) < 50);						// and also avoid red colors

			color = RGB(r, g, b);											// these rules are not professional
		}


		vector<KV_PiEleLoc*>* locations = currentPI->locations();			// get XY values for each element in currentPI
		for (uint j = 0; j < locations->size(); j++)						// for each of these
		{
			KV_PiEleLoc* currentEl = locations->at(j);

			bool foundGroup = false;
			for (uint k = 0; k < piGroups.size(); k++)						// for each existing Group (Kuller) of this PrimImplikant
			{
				KV_PiGroup* currentGroup = piGroups[k];
				if (currentGroup->LiesNextTo(currentEl))					// if this element lies next to the Group
				{
					currentGroup->Add(currentEl);							// sort Element into group
					foundGroup = true;										// we have found an appropriate group
					break;
				}
			}	// for each Group

			if (foundGroup == false)										// element was not added to a group
			{
				KV_PiGroup* newGroup = new KV_PiGroup();					// we have to create a new group for this el
				newGroup->Add(currentEl);
				piGroups.push_back(newGroup);
			}
		}	// for each Element in PrimImplikant

		// now we have created all groups for this PrimImplikant

		for (uint k = 0; k < piGroups.size(); k++)							// for each Group/Kuller of this PrimImplikant
		{
			this->PrintPrimImplikantenGroup(piGroups[k], random, color);	// draw it

			delete piGroups[k];												// and then let's delete it
			piGroups[k] = NULL;
		}

		piGroups.clear();													// clear the group vector
	}	// for each PrimImplikant
}


/// <summary>
/// Prints the KV_PiGroups that PrintPrimImplikanten generated
/// </summary>
/// <param name="group">A pointer to the group that shall be printed</param>
/// <param name="random">Some random number for the rectangle size, or -1 if the PI solves a hazard</param>
/// <param name="color">Some random color for the rectangles</param>
void KV::PrintPrimImplikantenGroup(KV_PiGroup* &group, char random, uint &color)
{
	uint X1, Y1, X2, Y2;		// coordinates for the rectangle of this group
	group->MakeCoords(this->edgeLength, this->VarX_Length, this->VarY_Length, &X1, &Y1, &X2, &Y2);	// makes X1, X2, Y1, Y2

	if (random == -1)			// make hazard groups as small as possible, but add a little ransom
	{
		random = rand() % 2;	// [0;1]
		X1 += 12 - random;
		X2 -= 12 - random;
		random = rand() % 2;	// [0;1]
		Y1 += 9 - random;
		Y2 -= 9 - random;
	}
	else						// make size random, so the groups won't overlap
	{
		X1 += random;			// lower upper  bound --> smaller
		X2 -= random;			// higher lower bound --> smaller
		Y1 += random;			// higher left  bound --> smaller
		Y2 -= random;			// lower right  bound --> smaller
	}

	this->Rectangle(X1, Y1, X2, Y2, color, TRANS);
}




/// <summary>
/// Generates the Buttons to restart and to open a new file and then waits for a mouse click on one of those
/// </summary>
void KV::Buttons()
{
	int b, h, x, y;

	get_drawarea(&b, &h);

	textbox(b-120, h-40, b-5,   h-5, 12, BLACK, GREY, RGB(50,50,50), SINGLE_LINE|VCENTER_ALIGN|CENTER_ALIGN, "Restart");
	textbox(b-240, h-40, b-125, h-5, 12, BLACK, GREY, RGB(50,50,50), SINGLE_LINE|VCENTER_ALIGN|CENTER_ALIGN, "Other file");
	updatescr();

	while (
		!(mouseclick(&x,&y) == 1 &&				// wait for mouse click
		  (y > h-40 && y < h-5) && (			// if y fits into button
			(x > b-120 && x < b-5)   ||			// if x fits into button "Restart"
			(x > b-240 && x < b-125)			// or x fits into button "Other file"
		 )))									// then end this loop and resume operation
	{
		printf(".");
		if(stopProcess())break;					// if stop was pressed the loop will also be quit
	};

	if ((x > b-240 && x < b-125) && (y > h-40 && y < h-5))	// if button "Other file" was clicked: tell the main loop
		fileChosen = false;
}

/// <summary>
/// Checks whether stopProcess() is true. This is a wrapper for all users of KV class
/// </summary>
bool KV::StopProcess()
{
	return stopProcess() == TRUE;
}


/// <summary>
/// Prints a line from [x1,y1] to [x2,y2] adding the global offset
/// </summary>
/// <param name="x1">Left starting point (X)</param>
/// <param name="y1">Upper starting point (Y)</param>
/// <param name="x2">Right ending point (X)</param>
/// <param name="y2">Lower ending point (Y)</param>
/// <param name="color">The color of the line</param>
void KV::Line(uint x1, uint y1, uint x2, uint y2, int color)
{
	line(x1 + this->offsetX, y1 + this->offsetY, x2 + this->offsetX, y2 + this->offsetY, color);
}

/// <summary>
/// Prints theText at the specified [x,y] position adding the global offset
/// </summary>
/// <param name="x">Left position where text starts (X)</param>
/// <param name="y">Upper position where text starts (Y)</param>
/// <param name="size">Text size</param>
/// <param name="color">The color of the text</param>
/// <param name="bkcolor">Background color of the text rectangle</param>
/// <param name="angle">Angle to rotate the text</param>
/// <param name="theText">String that shall be printed</param>
void KV::Text(uint x, uint y, uint size, int color, int bkcolor, int angle, char* theText)
{
	text(x + this->offsetX, y + this->offsetY, size, color, bkcolor, angle, NULL, theText);
}

/// <summary>
/// Prints a rectangle that containts text adding the global offset
/// </summary>
/// <param name="x1">Left starting point (X)</param>
/// <param name="y1">Upper starting point (Y)</param>
/// <param name="x2">Right ending point (X)</param>
/// <param name="y2">Lower ending point (Y)</param>
/// <param name="size">Text size</param>
/// <param name="ctext">Color of the text</param>
/// <param name="cframe">Color of the border of the textbox</param>
/// <param name="cfill">Background color of the rectangle that makes up the textbox</param>
/// <param name="flags">Some alignment flags</param>
/// <param name="theText">String that shall be printed</param>
void KV::TextBox(uint x1, uint y1, uint x2, uint y2, uint size, int ctext, int cframe, int cfill, int flags, char* theText)
{
	textbox(x1 + this->offsetX + 1, y1 + this->offsetY, x2 + this->offsetX + 1, y2 + this->offsetY, size, ctext, cframe, cfill, flags, theText);
}

/// <summary>
/// Prints a rectangle that containts bold text adding the global offset
/// </summary>
/// <param name="x1">Left starting point (X)</param>
/// <param name="y1">Upper starting point (Y)</param>
/// <param name="x2">Right ending point (X)</param>
/// <param name="y2">Lower ending point (Y)</param>
/// <param name="size">Text size</param>
/// <param name="ctext">Color of the text</param>
/// <param name="cframe">Color of the border of the textbox</param>
/// <param name="cfill">Background color of the rectangle that makes up the textbox</param>
/// <param name="flags">Some alignment flags</param>
/// <param name="theText">String that shall be printed</param>
void KV::TextBoxBold(uint x1, uint y1, uint x2, uint y2, uint size, int ctext, int cframe, int cfill, int flags, char* theText)
{
	textbox(x1 + this->offsetX + 1, y1 + this->offsetY, x2 + this->offsetX + 1, y2 + this->offsetY, size, ctext, cframe, cfill, flags, theText);
	textbox(x1 + this->offsetX + 2, y1 + this->offsetY, x2 + this->offsetX + 2, y2 + this->offsetY, size, ctext, TRANS, TRANSPARENT, flags, theText);		// write twice to simulate bold font
}

/// <summary>
/// Prints a rectangle at the specified position adding the global offset
/// </summary>
/// <param name="x1">Left starting point (X)</param>
/// <param name="y1">Upper starting point (Y)</param>
/// <param name="x2">Right ending point (X)</param>
/// <param name="y2">Lower ending point (Y)</param>
/// <param name="cframe">Border color</param>
/// <param name="cfill">Background color</param>
void KV::Rectangle(uint x1, uint y1, uint x2, uint y2, int cframe, int cfill)
{
	rectangle(x1 + this->offsetX + 1, y1 + this->offsetY + 1, x2 + this->offsetX + 1, y2 + this->offsetY + 1, cframe, cfill);
}