#include <string>
#include <vector>
#include<map>
#include "stdafx.h"

#include "Cparser.h"

using namespace std;

#define Getc(s) getc(s)
#define Ungetc(c) ungetc(c,IP_Input)

/* Lexical analyser states. */

enum lexstate{L_START,L_INT,L_IDENT};


int Cparser::yylex(){
	int c;
	lexstate s;

	for(s=L_START, yytext="";1;){
		c= Getc(IP_Input);
		yytext=yytext+(char)c;
		switch (s){

		case L_START:
			if(isdigit(c)){
				if((char)c!='x'){
					s=L_INT;
				}else{ 
					Ungetc(c);
					yytext=yytext.substr(0,yytext.size()-1);
					yytext1+='1';
					yytext+='0';// ab hier gut überlegen falls x auftritte


					break;
				}
			}else if (isspace(c)||isalpha(c)){
				s=L_IDENT;
			}else if(c==EOF){
				return 0;
			}else if (c=='\n'){ LineNumber+=1;
			}else { return 0;
			}
			break;

		case L_INT:
			if(isdigit(c)){ break;
			}else {
				Ungetc(c);
				yylval.s=yytext.substr(0,yytext.size()-1);
			}
		
			break;
		case L_IDENT:
			if(isalpha(c)){
				yylval.s=yytext.substr(0,yytext.size()-1);
				yylval.i=atoi(yylval.s.c_str());
				yytext="";
			}
			break;

		default: 
			printf("*** Fatal Error!!!!!*** Wrong case label in yylex\n");



		}

	}
}




