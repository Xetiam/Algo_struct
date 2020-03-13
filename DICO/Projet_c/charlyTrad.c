//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 28/02/2020///
//////////////////////////////////////////////////////////////
#include "charlyTrad.h"


int main(int argc, string argv[]){
	entry const dicoEntry = formatageDico("./tabDico/francais-italien_snp.tab");
	entry tempDicoEntry = dicoEntry;
	for(int i = 0 ; i < 72 ; i++){
		affichEntry(tempDicoEntry);
		tempDicoEntry = cdr(tempDicoEntry);
	}
	return 0;
}