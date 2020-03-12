//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 28/02/2020///
//////////////////////////////////////////////////////////////
#include "charlyTrad.h"


int main(int argc, string argv[]){
	entry dicoEntry = formatageDico(1);
	for(int i = 0 ; i < 12 ; i++){
		printf("%s %s : 0000\n",original(dicoEntry-i).mot, original(dicoEntry).cat);
	}
	
	return 0;
}