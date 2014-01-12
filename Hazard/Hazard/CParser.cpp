#include "stdafx.h"
#pragma warning(disable:4786)
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "PrimImplikantCollection.h"
#include "CParser.h"
using namespace std;

#define	Getc(s)			getc(s)
#define	Ungetc(c)		{ungetc(c,IP_Input); ugetflag=1;}

extern unsigned int dimension;
extern unsigned int numElements;
extern bool KNF;

// Adds a character to the string value
void CParser::PushString(char c)
{
	yylval.s += c;
}
//------------------------------------------------------------------------
void CParser::Load_tokenentry(string str,int index)
{
	IP_Token_table[str]=index;
	IP_revToken_table[index]=str;
}
void CParser::IP_init_token_table()
{
	Load_tokenentry("STRING1",STRING1);
	Load_tokenentry("IDENTIFIER",IDENTIFIER);
	Load_tokenentry("INTEGER1",INTEGER1);

	Load_tokenentry("Variables",VARIABLES);
	Load_tokenentry("Terms",TERMS);
}
//------------------------------------------------------------------------

void CParser::pr_tokentable()
{
	
	typedef map<string,int>::const_iterator CI;
	const char* buf;

	printf( "Symbol Table ---------------------------------------------\n");

	for(CI p=IP_Token_table.begin(); p!=IP_Token_table.end(); ++p){
		buf = p->first.c_str();
		printf(" key:%s", buf);
		printf(" val:%d\n", p->second);;
	}
}
//------------------------------------------------------------------------

int CParser::yyparse(PrimImplikantCollection* &pic, vector<string>* &variables)
{
	bool KNFset = false;
	int tok;
	if(prflag) *IP_List << setw(5) << setfill('0') << IP_LineNumber;

	/*
	*	Go parse things!
	*/
	parsestate pState = P_START;
	

	while ((tok=yylex())!=0){
		switch (pState)
		{
		case P_START:
			switch (tok)
			{
			case VARIABLES:
				pState = P_VARIABLES;
				break;
			case TERMS:
				pState = P_TERMS_KEY;
				break;
			}
			break;
		case P_VARIABLES:
			switch(tok)
			{
			case IDENTIFIER:
				*IP_List << "Variable " << yylval.s << endl;
				variables->push_back(yylval.s.c_str());						// Add variable name to vector
				break;
			case TERMS:
				*IP_List << endl;
				pState = P_TERMS_KEY;
				break;
			}
			break;
		case P_TERMS_KEY:
			switch(tok)
			{
			case STRING1:
				*IP_List << "Term Key " << yylval.s << endl;
				pic->add(yylval.s.c_str());									// Add PrimImplikant with string
				break;
			case INTEGER1:
				*IP_List << "Term Key " << (unsigned int)yylval.i << endl;	// Add PrimImplikant with int
				pic->add(yylval.i);
				break;
			case (int)'>':
				pState = P_TERMS_VALUE;
				break;
			case VARIABLES:
				pState = P_VARIABLES;
				break;
			}
			break;
		case P_TERMS_VALUE:
			if (tok == INTEGER1)				// Check whether KNF was already set and then check consitency
			{
				if (!KNFset)
				{
					KNF = (yylval.i == 0);
					KNFset = true;
				}
				else if ((yylval.i == 0) != KNF)
				{
					*IP_Error << "*** FATAL ERROR *** You can only define either KNF or DNF!" << endl;
					*IP_Error << "In line " << setw(3) << setfill('0') << IP_LineNumber << ": " << pic->back()->name << '>' << yylval.i << endl;
					*IP_Error << "In line " << setw(3) << setfill('0') << IP_LineNumber << ": Defined was: " << (KNF ? "KNF" : "DNF") << " but now shall be changed to " << (KNF ? "DNF" : "KNF") << endl << endl;
					cout << "*** FATAL ERROR *** You can only define either KNF or DNF!" << endl;
					return 1;
				}

				*IP_List << "Term Value " << yylval.i << endl << endl;
				pState = P_TERMS_KEY;
			}
			break;
		}
	}

	dimension = variables->size();							// set global variable dimension
	numElements = (unsigned int)pow(2.0f, (int)dimension);	// set global variabl numElements
	return 0;

}
//------------------------------------------------------------------------

/*
 *	Parse Initfile:
 *
 *	  This builds the context tree and then calls the real parser.
 *	It is passed two file streams, the first is where the input comes
 *	from; the second is where error messages get printed.
 */
void CParser::InitParse(ifstream &inp, ofstream &err, ofstream &lst)

{

	/*
	*	Set up the file state to something useful.
	*/
	IP_Input = &inp;
	IP_Error = &err;
	IP_List  = &lst;

	IP_LineNumber = 1;
	ugetflag=0;
	/*
	*	Define both the enabled token and keyword strings.
	*/
	IP_init_token_table();
}
//------------------------------------------------------------------------

/*
 *	yyerror:
 *
 *	  Standard error reporter, it prints out the passed string
 *	preceeded by the current filename and line number.
 */
void CParser::yyerror(char *ers)
{
	*IP_Error << "In line " << setw(3) << setfill('0') << IP_LineNumber << ": " << ers << endl;
}
//------------------------------------------------------------------------

int CParser::IP_MatchToken(string &tok)
{
	int retval;
	if(	IP_Token_table.find(tok) != IP_Token_table.end()){
		retval = (IP_Token_table[tok]);
	}else{
		retval = (0);
	}
	return retval;
} 

//------------------------------------------------------------------------

/*
 *	yylex:
 *
 */
int CParser::yylex()
{
	//Locals
	int c;
	lexstate s = L_START;
	/*
	*	Keep on sucking up characters until we find something which
	*	explicitly forces us out of this function.
	*/
	yytext = "";
	yylval.s = "";
	yylval.i = 0;
	while(!IP_Input->eof())
	{
		c = (*IP_Input).get();
		yytext = yytext + (char)c;
		if(!ugetflag) { 
			if(c != EOF && prflag) *IP_List << c;
		}else ugetflag = 0;
		switch (s){
		  //Starting state, look for something resembling a token.
			case L_START:
				yytext = (char)c;
				if (isdigit(c)){
				  s = L_INT;
				}else if (isalpha(c) || c == '\\' ){
						s = L_IDENT;
				}else if (isspace(c)){
							if (c == '\n'){
								IP_LineNumber += 1;
								if(prflag)
									*IP_List << setw(3) << setfill('9') << IP_LineNumber;
								s = L_START;
								yytext = "";
							}
				}else if (c == '/'){
							yytext = "";
							s = L_COMMENT;
				}else if (c == '"'){
							s = L_STRING;
				}else if (c == EOF){
							return ('\0');
				}else{
							s = L_START;
							yytext = "";
							return (c);
				}
			break;

			case L_COMMENT:
				if (c == '/') 
					s = L_LINE_COMMENT;
				else	if(c == '*')
							s = L_TEXT_COMMENT;
						else{
								(*IP_Input).unget();
								return '/';		// its the division operator not a comment
							}
			break;
			case L_LINE_COMMENT:
				if ( c == '\n'){
					s = L_START;
					(*IP_Input).unget();
				}
				yytext = "";
			break;
			case L_TEXT_COMMENT:
				if ( c == '\n'){
					IP_LineNumber += 1;
				}else if (c == '*')
							s = L_END_TEXT_COMMENT;
				yytext = "";
			break;
			case L_END_TEXT_COMMENT:
				if (c == '/'){
					s = L_START;
				}else{
					s = L_TEXT_COMMENT;
				}
				yytext = "";
			break;

		  /*
		   *	Suck up the integer digits.
		   */
			case L_INT:
				if (isdigit(c)){
				  break;
				}else {
					(*IP_Input).unget();
					yylval.s = yytext.substr(0,yytext.size()-1);
					yylval.i = atoi(yylval.s.c_str());
					return (INTEGER1);
				}
			break;

		  /*
		   *	Grab an identifier, see if the current context enables
		   *	it with a specific token value.
		   */
			
			case L_IDENT:
			   if (isalpha(c) || isdigit(c) || c == '_')
				  break;
				(*IP_Input).unget();
				yytext = yytext.substr(0,yytext.size()-1);
				yylval.s = yytext;
				if (c = IP_MatchToken(yytext)){
					return (c);
				}else{
					return (IDENTIFIER);
				}

		   /*
		   *	Suck up string characters but once resolved they should
		   *	be deposited in the string bucket because they can be
		   *	arbitrarily long.
		   */
			case L_STRING2:
				s = L_STRING;
				if(c == '"'){
					PushString((char)c);
				}else{
					if(c == '\\'){
						PushString((char)c);
					}else{
						PushString((char)'\\');
						PushString((char)c);
					}
				}
			break;
			case L_STRING:
				if (c == '\n')
				  IP_LineNumber += 1;
				else if (c == '\r')
						;
					 else	if (c == '"' || c == EOF){
								return (STRING1);
							} else	if(c=='\\'){
										s = L_STRING2;
										//PushString((char)c);
									}else
										PushString((char)c);
			break;
			default:
				*IP_Error << "*** FATAL ERROR *** Wrong case label in yylex" << endl;
				*IP_Error << "In line " << setw(3) << setfill('0') << IP_LineNumber << ": state " << s << endl;
				cout << "***Fatal Error*** Wrong case label in yylex" << endl;
		}
	}
	return 0;
}