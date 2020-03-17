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
	while(dico != NULL ){
		if(strcmp(dico->original.mot,motUser) == 0){
			return dico;
		}
		dico = dico->cdr;
	}
	printf("Le mot entré n'a pas de traduction disponible dans ce dictionnaire.\n");
	return NULL;
}//Fonctionne

/*Fonction qui affiche le mot original et toutes ses traductions */
void affichEntry(entry entry){
	printf("Le mot %s %s se dit :\n",entry->original.mot,entry->original.cat);
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
	string templigne = strdup(ligne);

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
	//Segfault à l'allocation
	string templigne = strdup(ligne);

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
	//DEBUG
	string tempLigne = NULL;
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
	int i =0;

	//Boucle de fabrication de la liste
	while(fgets(ligne,TAILLE_MAX,dico)!=NULL){
		tempLigne = (string) malloc(sizeof(ligne));
		strcpy(tempLigne,ligne);
		//Test pour savoir si la ligne en cours contient une traduction d'un nouveau original
		if(strcmp(strtok(tempLigne,"\t"),curDicoEntry->original.mot) != 0){
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

			//DEBUG
			printf("Je rentre dans getOrig, itération : %d\n",i);

			getOriginal(ligne, &curDicoEntry->original.mot, &curDicoEntry->original.cat);//SEGFAULT (à cause du malloc. 
			//sachant que c'est le fr qui pose problème donc getTrad si dans l'autre sens)
			
			printf("Je sors de getOri, itération : %d\n",i);

			//DEBUG
			printf("Je rentre dans getTrad, itération : %d\n",i);


			getTraduction(ligne, &curDicoEntry->traductions->traductions.mot, &curDicoEntry->traductions->traductions.cat);

			printf("Je sors de getTrad, itération : %d\n",i);

				//Enregistrement de l'adresse de la première traduction de l'entrée
			startTrad = curDicoEntry->traductions;
		}
		else{
			//Création d'une nouvelle traduction pour l'entré
				//Allocation de la mémoire pour une nouvelle traduction
			curDicoEntry->traductions->cdr = (struct Traductions*) malloc(sizeof(struct Traductions*));
				//Déplacement du pointeur cur->traductions sur une traduction suivante
			curDicoEntry->traductions = curDicoEntry->traductions->cdr;

				//Enregistrement de la traduction suivante
			getTraduction(ligne,&curDicoEntry->traductions->traductions.mot, &curDicoEntry->traductions->traductions.cat);
		}

		//DEBUG
		i++;
	}
	//Création d'un entrée NULL pour finir le dictionnaire
	curDicoEntry->cdr = NULL;
	return startDicoEntry;
}//Segfault avec les dictionnaire complet (particularité des entrées : elles sont en français.)
