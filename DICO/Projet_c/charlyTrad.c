//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 28/02/2020///
//////////////////////////////////////////////////////////////
#include "charlyTrad.h"


int main(int argc, string argv[]){
	entry dicoEntry = formatageDico("./tabDico/échantillon.tab");

	//Récupération du mot que l'utilisateur souhaite traduire
	printf("Veuillez entré le mot ou l'expression à traduire : \n");
	char motUser[100];
	fgets(motUser, sizeof(motUser), stdin);

	//Retrait du retour à la ligne pour pouvoir effectuer la comparaison
	strtok(motUser,"\n");

	entry entryUser = searchEntry(dicoEntry,motUser);
	if(entryUser != NULL)
		affichEntry(entryUser);


	return 0;
}