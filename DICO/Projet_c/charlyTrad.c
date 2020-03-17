//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 28/02/2020///
//////////////////////////////////////////////////////////////
#include "charlyTrad.h"


int main(int argc, string argv[]){
	//Initialisation des variables
	char motUser[100];
	char choixUser[1];
	string dicoTab;

	//Interface utilisateur (basique)
	printf("Veuillez choisir le sense de traduction :\n\t 1. Français vers Italien\n\t 2. Italien vers Français\n");
	scanf("%s",choixUser);
	if(strcmp(choixUser,"1") == 0){
		dicoTab = "./tabDico/francais-italien_snp.tab";
	}
	else if(strcmp(choixUser,"2") == 0){
		dicoTab = "./tabDico/italien-francais_snp.tab";
	}
	entry dicoEntry = formatageDico(dicoTab);

		//Récupération du mot que l'utilisateur souhaite traduire
	printf("Veuillez entrer le mot ou l'expression à traduire : \n");
	//printf("DEBUG\n");
	fgets(motUser, sizeof(motUser), stdin);
	//Retrait du retour à la ligne pour pouvoir effectuer la comparaison
	strtok(motUser,"\n");

	entry entryUser = searchEntry(dicoEntry,motUser);
	if(entryUser != NULL)
		affichEntry(entryUser);


	return 0;
}