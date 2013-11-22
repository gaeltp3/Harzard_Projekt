#include <string>
#include <vector>
#include "PrimImplikantCollection.h"
#include <iostream>

using namespace std;

unsigned int numElements ;
bool KNF ;

#ifndef WERTETABELLE
#define WERTETABELLE


class Wertetabelle{


public:
	
	int print(PrimImplikantCollection* &PIC){

		cout << "KNF=" << KNF << endl;
		cout << "Dezimalwerte\t|\tAusgangWerte(y)" << endl;
		for (unsigned int i = 0; i < numElements; i++){
			cout << "\t" << i << "\t\t|\t" << PIC->valueAt(i) << endl;
		}
	}


	Wertetabelle(PrimImplikantCollection* &PIC){  // Konstruktor
		print(PIC);
	}

};







#endif