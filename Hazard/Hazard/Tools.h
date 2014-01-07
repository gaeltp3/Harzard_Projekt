#pragma once

class Tools
{
public:
	static char* Tools::BinaryToChars(uint x, char length);

	static uint GrayToBinary(uint x);
private:
	static void InitGrayToBinaryTable();
	static uint* GrayToBinaryTable;
	static uint Tools::CalcGrayToBinary(uint x);
};