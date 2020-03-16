//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 31/01/2020///
//////////////////////////////////////////////////////////////
#include "dicoManage.h"

void getTraduction(string const ligne,base* trad);
void getOriginal(string const ligne,string* mot, string* cat);
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

/*Fonction qui affiche le mot original et toutes ses traductions */
void affichEntry(entry entry){
	printf("%s %s :",entry->original.mot,entry->original.cat);
	while(entry->traductions->traductions->mot != NULL){
		printf("\t%s %s",entry->traductions->traductions->mot,entry->traductions->traductions->cat);
		entry->traductions = entry->traductions->cdr;
	}
	return;
}//fonctionne pas (doute sur les accès de trads)

/* Fonction de construction part Traductions d'une entry et qui fait pointer cdr sur la trad suivante si elle existe */
void getTraduction(string const ligne,base* trad){
	//printf("l'appel à fonctionné\n");
	//Initialisation des variables
	trad =(base*) malloc(2*sizeof(string));
	int cur = 0;
	int curCat = 0;

	// Copie de ligne car constante
	string templigne = malloc(sizeof(ligne));
	strcpy(templigne,ligne);

	//Parcour de la ligne pour trouver le début de la partie traduction 
	//ainsi que le début de la catégorie de la trad
	for(int i = 0 ; i < strlen(templigne) ; i++){
		if(templigne[i] == '-'){
			cur = i+2;
		}
		if(templigne[i] == '['){
			curCat = i;
		}
	}

	//Déplacement du pointeur sur la ligne pour la copie des caractères de mot
	templigne = templigne + cur;
	trad->mot = strndup(templigne,(size_t)(curCat-(cur+1)));
	//printf("tempLigne : %s\n",templigne);

	//Déplacement du pointeur sur la ligne pour la copie des caractères de cat
	templigne = ligne +cur + strlen(trad->mot) +1;
	trad->cat = strndup(templigne,(size_t)strlen(templigne)-1);
	//printf("mot(getTrad) : %s|\ncat(getTrad) : %s|\n",trad->mot,trad->cat);
	return;
}//Fonctionne

void getOriginal(string const ligne, string* mot, string* cat){
	//Initialisation des variables
	int cur = 0;
	int curCat = 0;

	// Copie de ligne car constante
	string templigne = malloc(sizeof(ligne));
	strcpy(templigne,ligne);

	//Parcour de la ligne pour trouver le début de la partie traduction 
	//ainsi que le début de la catégorie de la trad
	for(int i = 0 ; i < strlen(templigne) ; i++){
		if(templigne[i] == '\t'){
			curCat = i;
		}
		if(templigne[i] == '-' && curCat != 0){
			cur = i;
		}
	}

	//Déplacement du pointeur sur la ligne pour la copie des caractères de mot
	*mot = strndup(templigne,(size_t)(curCat));

	//Déplacement du pointeur sur la ligne pour la copie des caractères de cat
	templigne = ligne + strlen(*mot) + 1;
	//printf("tempLigne : %s\n",templigne);
	*cat = strndup(templigne, (cur - curCat)-2);
	//printf("mot(getOri) : %s|\ncat(getOri) : %s|\n",*mot,*cat);
	return;
}//Fonctionne

/* Fonction pour formater un .tab dans une liste chainée */
entry formatageDico(string tabDico){
	/* Initialisation des variables */
	FILE* dico = ffopen(tabDico,"r");
	entry tempDicoEntry = NULL;
	traductions tempTrad = NULL;

	// Création de la première entrée (Conservation de l'origine de liste car si perdu, je n'ai plus accès à celle ci)
	entry const origDicoEntry = (struct Entry*) malloc(sizeof(struct Entry*));
	string ligne = (string) malloc(TAILLE_MAX*sizeof(string));
	string tempLigne = NULL;

	//Acquisition de la première ligne du dictionnaire
	fgets(ligne, TAILLE_MAX, dico);

	// Création de l'originale (Pour pouvoir la faire pointer l'entrée temporaire sur la première entré  )
	getOriginal(ligne, &origDicoEntry->original.mot, &origDicoEntry->original.cat);
	// Création de la première traduction
	origDicoEntry->traductions = (struct Traductions*) malloc(sizeof(struct Traductions*));
	getTraduction(ligne,origDicoEntry->traductions->traductions);
	tempTrad = (traductions) malloc(sizeof(traductions));
	tempTrad = origDicoEntry->traductions;
	tempDicoEntry = origDicoEntry;


	int i =0;
	//printf("Je rentre dans boucle\n");


	while(fgets(ligne, TAILLE_MAX, dico) != NULL){
		//Copie de la ligne dans une chaîne temporaire pour effectuer le test pour savoir si la nouvelle ligne concerne 
		//une traduction du même mot que précédemment
		printf("%d\n", i++);
		tempLigne = (string) malloc(sizeof(ligne));
		strcpy(tempLigne,ligne);

		//Création du nouvel élmt et déplacement du pointeur sur le suivant à condition que le mot ne soit pas déjà stocker
		if(strcmp(tempDicoEntry->original.mot, strtok(tempLigne,"\t")) != 0){
			//Déplacement du pointeur sur trad sur la première trad
			tempDicoEntry->traductions = tempTrad;
			tempTrad = NULL;

			//Déplacement du pointeur pour passer à l'entrée du dico suivante
			tempDicoEntry->cdr = (struct Entry*) malloc(sizeof(struct Entry*));
			tempDicoEntry = tempDicoEntry->cdr;
			getOriginal(ligne, &tempDicoEntry->original.mot, &tempDicoEntry->original.cat);
			

			//Enregistrement de l'adresse de la première traduction.
			tempDicoEntry->traductions = (struct Traductions*) malloc(sizeof(struct Traductions*));
			getTraduction(ligne, tempDicoEntry->traductions->traductions);
			tempTrad = (traductions) malloc(sizeof(traductions));
			tempTrad = tempDicoEntry->traductions;
		}

		else{
			tempDicoEntry->traductions->cdr = (struct Traductions*) malloc(sizeof(struct Traductions*));
			tempDicoEntry->traductions = tempDicoEntry->traductions->cdr;
			getTraduction(ligne, tempDicoEntry->traductions->traductions);
		}
	}
	return origDicoEntry;
}//segfault au bout d'un moment (effet de bord de getTrad?)



