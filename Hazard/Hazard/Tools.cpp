#include "stdafx.h"
#include "Tools.h"

using namespace std;

extern uint numElements;					// 2 ^ dimesion

uint* Tools::GrayToBinaryTable = NULL;
uint Tools::GrayToBinaryTableSize = 0;

/// <summary>
/// <para>Converts the binary representation of x to a string with the specified length</para>
/// <para>The difference to itoa() is the fixed length</para>
/// <summary>
/// <param name="x">The number that shall be converted</param>
/// <param name="length">The length of the char[] (= number of variables)</param>
/// <returns>A pointer to a new char[]</returns>
char* Tools::BinaryToChars(uint x, char length)
{
	char* c = new char[length+1];	// allocate memory
	c += length;					// point to last char (at length + 1 - 1)

	*c = 0;							// '\0'
	do
	{
		*--c = '0' + (x & 1);		// 0 or 1 at the specified position, convert to char
		x >>= 1;					// next position
	} while (--length);

	return c;						// return char[] now pointing to the beginning again
}

/// <summary>
/// <para>Converts the specified number x from gray back to binary</para>
/// <para>To boost the performance it inits a lookup table on first run. When the number of variables changes (different input file) it changes the size of the lookup table, too. This could be done a little more efficient.
/// </summary>
uint Tools::GrayToBinary(uint x)
{
	if (Tools::GrayToBinaryTableSize < numElements && Tools::GrayToBinaryTable != NULL)	// number of variables was increased
	{
		delete[] Tools::GrayToBinaryTable;			// delete old table
		Tools::InitGrayToBinaryTable();				// make new table. It would be better to increase the allocated amount of memory
	}
	else if (Tools::GrayToBinaryTable == NULL)		// no table existed
		Tools::InitGrayToBinaryTable();				// make new table

	return Tools::GrayToBinaryTable[x];				// do the lookup
}

/// <summary>
/// Allocates memory for the GrayToBinaryTable and sets its values
/// </summary>
void Tools::InitGrayToBinaryTable()
{
	Tools::GrayToBinaryTable = new uint[numElements];				// make uint[]
	Tools::GrayToBinaryTableSize = numElements;						// save size to detect changes
	for (uint i = 0; i < numElements; i++)							// for all possible numbers
		Tools::GrayToBinaryTable[i] = Tools::ConvertGrayToBinary(i);	// convert gray to binary
}


/// <summary>
/// <para>Converts a gray number to its binary representation by converting to gray a special number of times.</para>
/// <para>31 is the maximum number of loops because uint only has 32 bits and works for every x. Calculation of r on the base of x is more efficient).
/// </summary>
/// <returns>The binary number that is associated with the gray x</returns>
uint Tools::ConvertGrayToBinary(uint x)
{
	uint x1 = x;

	char r = 0;						// r shall contain the position of the first positive bit + 1 in x
	do								// do while --> ceil.	while do --> floor.
		r++;
	while (x1 >>= 1);				// r = ceil(ld(x))
	//	r = 0 | x = 3		r = 0 | x = 5
	//		1 | 011				1 | 101
	//		2 | 001				2 | 010
	//		3 | 000				3 | 001
	//							4 | 000
		
	if ((r & (r-1)) != 0)			// if r is no multiple of 2 <-- 100 & 011 = 000 == 0     101 & 100 = 100 != 0
	{								// we need to round r up to the next multiple of 2. Let's use same algorithm as above.
		char r1 = 0;				// r1 shall contain the position of the first positive bit + 1 in r
		do
			r1++;
		while (r >>= 1);			// r1 = ceil(ld(r))

		r = 1 << r1;				// r = 2^(ceil(ld(r))) > 2^(ld(r)) (== r)
	}

	for (char i = 1; i < r; i++)	// do gray conversion r times --> binary. Do gray conversion r+1 times --> gray again
		x ^= x / 2;

	return x;
}


/// <summary>
/// Compare to gray numbers. Since computers can only compare binary numbers we have to convert them first
/// </summary>
/// <param name="a">Number that InsertionSort is processing (and that may be repositioned)</param>
/// <param name="b">Number that a is compared to (precendants of a)</param>
/// <returns>True: a should be positioned in front of b</returns>
bool Tools::compareAsGray(uint a, uint b)
{
	return Tools::GrayToBinary(a) < Tools::GrayToBinary(b);
}