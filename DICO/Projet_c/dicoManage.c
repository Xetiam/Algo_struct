//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 31/01/2020///
//////////////////////////////////////////////////////////////
#include "dicoManage.h"

void getOriginal(string const ligne, string* mot, string* cat);
FILE* ffopen(char* arg, char* mode);
entry formatageDico(string tabDico);

/* Fonction pour ouvrir un fichier */
FILE* ffopen(char* arg, char* mode){
	FILE* fichier = fopen(arg, mode);
	if(fichier == NULL){
		printf("Fichier %s introuvable\n",arg);
		return 0;
	}
	return fichier;
	}


/* Fonction de construction part Traductions d'une entry */


void getOriginal(string const ligne, string* mot, string* cat){
	//Allocation de mémoire de la taille du mot original et copie de cette ligne
	//car ligne est constante
	//printf("ligne en entrée :%s",ligne);
	string tempLigne = malloc(sizeof(ligne));
	strcpy(tempLigne,ligne);
	*mot = malloc(sizeof(strtok(tempLigne,"\t")));

	//Copie du mot original
	strcpy(*mot, strtok(tempLigne,"\t"));
	//printf("mot(dans getOri) : %s\n",*mot);

	//Réinitialisation de tempLigne car modifier par strtok
	tempLigne = NULL;
	tempLigne = malloc(sizeof(ligne));
	strcpy(tempLigne,ligne);

	//Déplacement sur la ligne pour atteindre la cat
	tempLigne = tempLigne + strlen(*mot) + sizeof(char);
	//printf("Templigne(après copie et décalage) :%s",tempLigne);

	//Même procéder que pour mot
	*cat = malloc(sizeof(strtok(tempLigne,"-")));
	strcpy(*cat, strtok(tempLigne,"-"));
	//printf("cat (dans getOri) :%s \n", *cat);

	return;
}//Fonctionne

entry formatageDico(string tabDico){
	/* Initialisation des variables */
	entry tempDicoEntry = NULL;
	// Création de la première entrée (Conservation de l'origine de liste car si perdu, je n'ai plus accès à celle ci)
	entry const origDicoEntry = (struct Entry*) malloc(sizeof(struct Entry*));
	FILE* dico = ffopen(tabDico,"r");
	string ligne = (string) malloc(TAILLE_MAX*sizeof(string));
	string tempLigne = NULL;
	fgets(ligne, TAILLE_MAX, dico);

	// Création de l'originale (Pour pouvoir la faire pointer la première entré temporaire sur )
	getOriginal(ligne, &origDicoEntry->original.mot, &origDicoEntry->original.cat);

	tempDicoEntry = origDicoEntry;
	//printf("Je rentre dans boucle\n");
	while(fgets(ligne, TAILLE_MAX, dico) != NULL){

		//Copie de la ligne dans une chaîne temporaire pour effectuer le test pour savoir si la nouvelle ligne concerne 
		//une traduction du même mot que précédemment
		tempLigne = (string) malloc(sizeof(ligne));
		strcpy(tempLigne,ligne);

		//Création du nouvel élmt et déplacement du pointeur sur le suivant à condition que le mot ne soit pas déjà stocker
		if(strcmp(tempDicoEntry->original.mot, strtok(tempLigne,"\t")) != 0){
			tempDicoEntry->cdr = (struct Entry*) malloc(sizeof(struct Entry*));
			tempDicoEntry = tempDicoEntry->cdr;
			getOriginal(ligne, &tempDicoEntry->original.mot, &tempDicoEntry->original.cat);
		}
	}
	return origDicoEntry;
}



