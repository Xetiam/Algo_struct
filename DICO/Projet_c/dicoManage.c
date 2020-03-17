//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 31/01/2020///
//////////////////////////////////////////////////////////////
#include "dicoManage.h"

void getTraduction(string const ligne, string* mot, string* cat);
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

/* Fonction pour chercher et renvoyé l'entrée correspondant à la demande utilisateur */
entry searchEntry(entry dico,string motUser){
	while(strcmp(dico->original.mot,motUser) != 0 ){
		dico = dico->cdr;
	}
	if(strcmp(dico->original.mot,motUser) == 0){
		return dico;
	}
	else{
		printf("Le mot entré n'a pas de traduction disponible dans ce dictionnaire.\n");
		return NULL;
	}
}//Fonctionne

/*Fonction qui affiche le mot original et toutes ses traductions */
void affichEntry(entry entry){
	printf("%s %s :\n",entry->original.mot,entry->original.cat);
	do{
		printf("\t%s %s\n",entry->traductions->traductions.mot,entry->traductions->traductions.cat);
		entry->traductions = entry->traductions->cdr;
	}while(entry->traductions != NULL);
	return;
}//Fonctionne

/* Fonction de construction part Traductions d'une entry et qui fait pointer cdr sur la trad suivante si elle existe */
void getTraduction(string const ligne, string* mot, string* cat){
	//Initialisation des variables
	int cur = 0;
	int curCat = 0;

	// Copie de ligne car constante
	string templigne = malloc(sizeof(ligne));
	strcpy(templigne,ligne);

	//Parcour de la ligne pour trouver le début de la partie traduction 
	//ainsi que le début de la catégorie de la trad
	for(int i = 0 ; i < strlen(templigne) ; i++){
		if(templigne[i] == '['){
			curCat = i;
		}
		if(templigne[i] == '-' && templigne[i-1] ==' ' && templigne[i+1] == ' '){
			cur = i;
		}
	}

	//Déplacement du pointeur sur la ligne pour la copie des caractères de mot
	templigne = ligne + cur + 2;
	//printf("templigne : %s\n",templigne);
	size_t sizeMot =(size_t)(curCat-cur-3);
	*mot = strndup(templigne,sizeMot);

	//Déplacement du pointeur sur la ligne pour la copie des caractères de cat
	templigne = ligne + curCat;
	size_t sizeCat =(size_t)(strlen(templigne)-1);
	*cat = strndup(templigne, sizeCat);
	//printf("mot(getTrad) : %s|\ncat(getTrad) : %s|\n",*mot,*cat);
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
		if(templigne[i] == '-' && templigne[i-1] ==' ' && templigne[i+1] == ' '){
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
	//Initialisation des variables
	FILE* dico = ffopen(tabDico,"r");
	string ligne =(string) malloc(TAILLE_MAX*sizeof(string));
		//Start est const pour conserver le début de la liste chaîné
	entry const startDicoEntry = (struct Entry*) malloc(sizeof(struct Entry*));
	entry curDicoEntry = NULL;
		//Conservation de la première traduction
	traductions startTrad = NULL;

	//Instanciation de Start : original et traductions
		//Récupération de la première ligne du .tab
	fgets(ligne,TAILLE_MAX,dico);
		//original
	getOriginal(ligne, &startDicoEntry->original.mot, &startDicoEntry->original.cat);
		//Traduction
	startDicoEntry->traductions = (struct Traductions*) malloc(sizeof(struct Traductions*));
	getTraduction(ligne, &startDicoEntry->traductions->traductions.mot, &startDicoEntry->traductions->traductions.cat);
	startTrad = startDicoEntry->traductions;
	//Copie du start dans le cur pour commencer la fabrication de la liste dans une boucle
	curDicoEntry = startDicoEntry;

	//DEBUG
	//printf("Debug mot de trad :%s\n",startDicoEntry->traductions->traductions.mot);
	//int i =0;

	//Boucle de fabrication de la liste
	while(fgets(ligne,TAILLE_MAX,dico)!=NULL){
		if(strncmp(ligne,curDicoEntry->original.mot,(size_t)(strlen(curDicoEntry->original.mot)*sizeof(char))) != 0){
			//Avancement du curseur
				//Création d'une traduction NULL pour finir la liste de traduction
			curDicoEntry->traductions->cdr = NULL;

				//Remettre le pointeur sur traduction à l'origine des traduction
			curDicoEntry->traductions = startTrad;

				//Déplacement du pointeur cur sur l'entrée suivante
			curDicoEntry->cdr = (struct Entry*) malloc(sizeof(struct Entry*));
			curDicoEntry = curDicoEntry->cdr;

				//Allocation de la mémoire pour stocker la ou les traductions
			curDicoEntry->traductions = (struct Traductions*) malloc(sizeof(struct Traductions*));

				//Instaciation de l'original et de la première traduction
			getOriginal(ligne, &curDicoEntry->original.mot, &curDicoEntry->original.cat);//SEGFAULT à l'itération 600 et 335 passage dans le if
			//printf("%d\n", i++);
			getTraduction(ligne, &curDicoEntry->traductions->traductions.mot, &curDicoEntry->traductions->traductions.cat);

				//Enregistrement de l'adresse de la première traduction de l'entrée
			startTrad = curDicoEntry->traductions;
		}
		else{
			//Création d'une nouvelle traduction pour l'entré
				//Allocation de la mémoire pour une nouvelle traduction
			curDicoEntry->traductions->cdr = (struct Traductions*) malloc(sizeof(struct Traductions*));
				//Déplacement du pointeur cur->traductions->cdr sur une traduction suivante
			curDicoEntry->traductions = curDicoEntry->traductions->cdr;

				//Enregistrement de la traduction suivante
			getTraduction(ligne,&curDicoEntry->traductions->traductions.mot, &curDicoEntry->traductions->traductions.cat);
		}
	}
	//Création d'un entrée NULL pour finir le dictionnaire
	curDicoEntry->cdr = NULL;
	return startDicoEntry;
}







/* entry formatageDico(string tabDico){
	// Initialisation des variables
	FILE* dico = ffopen(tabDico,"r");
	entry tempDicoEntry = NULL;
	traductions tempTrad = NULL;

	// Création de la première entrée (Conservation de l'origine de liste car si perdu, je n'ai plus accès à celle ci)
	entry const origDicoEntry = (struct Entry*) malloc(sizeof(struct Entry*));

	//Acquisition de la première ligne du dictionnaire
	string ligne = (string) malloc(TAILLE_MAX*sizeof(string));
	string tempLigne = NULL;
	fgets(ligne, TAILLE_MAX, dico);

	// Création de l'originale (Pour pouvoir la faire pointer l'entrée temporaire sur la première entré  )
	getOriginal(ligne, &origDicoEntry->original.mot, &origDicoEntry->original.cat);

	// Création de la première traduction
	origDicoEntry->traductions = (struct Traductions*) malloc(sizeof(struct Traductions*));
	getTraduction(ligne, &origDicoEntry->traductions->traductions.mot, &origDicoEntry->traductions->traductions.cat);
	tempTrad = origDicoEntry->traductions;
	tempDicoEntry = origDicoEntry;

	while(fgets(ligne, TAILLE_MAX, dico) != NULL){
		//Copie de la ligne dans une chaîne temporaire pour effectuer le test pour savoir si la nouvelle ligne concerne 
		//une traduction du même mot que précédemment
		tempLigne = (string) malloc(sizeof(ligne));
		strcpy(tempLigne,ligne);

		//Création du nouvel élmt et déplacement du pointeur sur le suivant à condition que le mot ne soit pas déjà stocker
		if(strcmp(tempDicoEntry->original.mot, strtok(tempLigne,"\t")) != 0){
			//Déplacement du pointeur sur trad sur la première trad
			tempDicoEntry->traductions = tempTrad;

			//Déplacement du pointeur pour passer à l'entrée du dico suivante
			tempDicoEntry->cdr = (struct Entry*) malloc(sizeof(struct Entry*));
			tempDicoEntry = tempDicoEntry->cdr;
			tempDicoEntry->traductions =(struct Traductions*) malloc(sizeof(struct Traductions*));
			getOriginal(ligne, &tempDicoEntry->original.mot, &tempDicoEntry->original.cat);
			getTraduction(ligne, &tempDicoEntry->traductions->traductions.mot, &tempDicoEntry->traductions->traductions.cat);
			//Enregistrement de l'adresse de la première traduction.
			tempTrad = tempDicoEntry->traductions;
		}

		else{
			tempDicoEntry->traductions->cdr = (struct Traductions*) malloc(sizeof(struct Traductions*));
			tempDicoEntry->traductions = tempDicoEntry->traductions->cdr;
			tempDicoEntry->traductions =(struct Traductions*) malloc(sizeof(struct Traductions*));
			getTraduction(ligne, &tempDicoEntry->traductions->traductions.mot, &tempDicoEntry->traductions->traductions.cat);
		}
	}
	return origDicoEntry;
}//Stockage des trads pas encore fait(getTrad fonctionne pas) */



