#ifndef CPARSER
#define CPARSER

#include <string>
#include "PrimImplikanten.h"

using namespace std;


class Cparser{
private:

	PrimImplikant implikant;
	
public:
	string yytext;
	string yytext1;
	int LineNumber;

	struct tyylval{
		string s;
		int i; 
	}yylval;

	FILE* IP_Input;
	void pr_tokentable();
	void load_tokenentry(string s ,int x);
	int  yylex();
	

};

















#endif 
