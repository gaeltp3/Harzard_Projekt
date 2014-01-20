#pragma once

/// <summary>
/// This is a static class that provides some methods that could be used anywhere
/// </summary>
class Tools
{
public:
	static char* Tools::BinaryToChars(uint x, char length);	// convert a number to a string in its binary representation

	static uint GrayToBinary(uint x);						// convert a gray number back to binary using a lookup table
	static bool compareAsGray(uint a, uint b);				// compary two gray numbers (convert it first)
private:
	static uint* GrayToBinaryTable;							// gray to binary lookup table
	static uint GrayToBinaryTableSize;						// size of GrayToBinaryTable

	static void InitGrayToBinaryTable();					// init GrayToBinaryTable
	static uint Tools::ConvertGrayToBinary(uint x);			// convert a gray number back to binary
};