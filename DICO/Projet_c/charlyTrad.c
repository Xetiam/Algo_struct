//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 28/02/2020///
//////////////////////////////////////////////////////////////
#include "charlyTrad.h"


int main(int argc, string argv[]){
	entry dicoEntry = formatageDico("./tabDico/échantillon.tab");
	printf("Veuillez entré le mot ou l'expression à traduire : \n");
	string motUser;
	scanf("%s",motUser);
	entry entryUser = searchEntry(dicoEntry,motUser);
	affichEntry(entryUser);
	return 0;
}