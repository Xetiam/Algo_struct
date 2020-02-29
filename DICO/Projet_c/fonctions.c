//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 31/01/2020///
//////////////////////////////////////////////////////////////
#include "charlyTrad.h"

/* Fonction pour ouvrir un fichier */
FILE* ffopen(char* arg, char* mode){
	FILE* fichier = fopen(arg, mode);
	if(fichier == NULL){
		printf("Fichier %s introuvable\n",arg);
		return 0;
	}
	return fichier;
	}



/* Fonction qui découpe chaque mot d'une chaine et les stock dans un tableau */
int decoupe(char* ligne, char* separ, char* mot[], int maxmot){
	int i;
	mot[0] = strtok(ligne, separ);
	for(i = 1 ; mot[i-1] != 0 ; i++){
		if(i==maxmot){
			fprintf(stderr, "Erreur dans la fonction decoupe : trop de mot\n");
			mot[i-1] = 0;
			break;
		}
		mot[i] = strtok(NULL,separ);
	}
	return i;
}


void formatageDico(int mode){
	char* ligne = (char*) malloc(TAILLE_MAX*sizeof(char*));
	char** mot = (char**) malloc(TAILLE_MAX*sizeof(char**));
	FILE* dico = ffopen("francais-italien_snp.tab","r");
	entry* francais_italien = NULL;
	entry italien_francais = NULL;
	for(int i =0; fgets(ligne, TAILLE_MAX, dico); i++){
		decoupe(ligne," -\t", mot, TAILLE_MAX);
		if(mode == 1){
			cdr(francais_italien) = 
			original(francais_italien).mot = mot[0];
			original(francais_italien).cat = mot[1];
			printf("%s %s :\n",original(francais_italien).mot,original(francais_italien).cat);
		}
		else if(mode == 2){

		}
	}
	return;
}