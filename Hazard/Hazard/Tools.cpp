#include "stdafx.h"
#include "Tools.h"

using namespace std;

extern uint numElements;

uint* Tools::GrayToBinaryTable = NULL;
uint Tools::GrayToBinaryTableSize = 0;

// convert the binary representation of x to a string with the specified length
char* Tools::BinaryToChars(uint x, char length)
{
	// warning: this breaks for numbers with more than 64 bits (= variables)
	char* c = new char[length+1];
	c += length;					// last char

	*c = 0;
	do
	{
		*--c = '0' + (x & 1);		// 0 or 1 at the specified position
		x >>= 1;
	} while (--length);

	return c;
}

uint Tools::GrayToBinary(uint x)
{
	if (Tools::GrayToBinaryTableSize < numElements && Tools::GrayToBinaryTable != NULL)
	{
		delete[] Tools::GrayToBinaryTable;
		Tools::InitGrayToBinaryTable();
	}
	else if (Tools::GrayToBinaryTable == NULL)
		Tools::InitGrayToBinaryTable();

	return Tools::GrayToBinaryTable[x];
}

void Tools::InitGrayToBinaryTable()
{
	Tools::GrayToBinaryTable = new uint[numElements];
	Tools::GrayToBinaryTableSize = numElements;
	for (uint i = 0; i < numElements; i++)
		Tools::GrayToBinaryTable[i] = Tools::CalcGrayToBinary(i);
}

// converts a gray number to its binary representation
uint Tools::CalcGrayToBinary(uint x)
{
	uint x1 = x;
	char r = 0;						// r = ceil(ld(x))
	do
		r++;
	while (x1 >>= 1);

	if ((r & (r-1)) != 0)			// keine Potenz von 2
	{
		char r1 = 0;				// r1 = ceil(ld(r))
		do
			r1++;
		while (r >>= 1);

		r = 1 << r1;				// aufrunden auf Zweierpotenz
	}

	for (char i = 1; i < r; i++)	// Umwandeln von Gray in Binary
		x ^= x / 2;

	return x;
}