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
		}
		else
			mot[i] = strtok(NULL,separ);
	}
	return i;
}

/* Fonction de construction part Original d'une entry */
base consEntryOr(string* eltOr){
	struct Base Cons;
	Cons.mot = eltOr[0];
	Cons.cat = eltOr[1];
	return Cons;
}

/* Fonction de construction part Traductions d'une entry */

/* Fonction de construction du cdr d'une entry */
struct Entry* consEntryCdr(entry entry){
	struct Entry* Cons = (struct Entry*) malloc(TAILLE_MAX*sizeof(struct Entry*));
	Cons = entry;
	return Cons;
}

/* Fonction pour formater le dictionnaire dans une structure permettant un accessibilité facile */
entry formatageDico(int mode){
	/* Initialisation des variables */
	FILE* dico = ffopen("échantillon.tab","r");
	string ligne = (string) malloc(TAILLE_MAX*sizeof(string));
	string* lignesepar = (string*) malloc(TAILLE_MAX*sizeof(string*));
	string* tabOr = NULL;
	string* tabTr = NULL;
	base temp;
	entry dicoEntry = (entry) malloc(TAILLE_MAXD*sizeof(entry));
	/* Boucle de découpage et de formatage du dictionnaire */
	for(int i = 0 ; fgets(ligne,TAILLE_MAX,dico); i++){
		tabOr = (string*) malloc(TAILLE_MAX*sizeof(string*));
		tabTr = (string*) malloc(TAILLE_MAX*sizeof(string*));
		/* Découpage de la ligne du dico*/
		decoupe(ligne,"-",lignesepar, TAILLE_MAX);
		decoupe(lignesepar[0],"\t",tabOr,TAILLE_MAX);
		decoupe(lignesepar[1]," ",tabTr,TAILLE_MAX);
		temp = consEntryOr(tabOr);
		original(dicoEntry) = temp;
		cdr(dicoEntry) = consEntryCdr(dicoEntry+i);
		//traiter les traductions suivantes si elles existent
		tabOr = NULL;
		tabTr = NULL;
	}
	fclose(dico);

	/* Libération de la mémoire et renvoie du dictionnaire formater */
	free(ligne);
	free(lignesepar);
	free(tabOr);
	free(tabTr);
	return dicoEntry;
}