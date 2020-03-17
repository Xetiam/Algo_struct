//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 31/01/2020///
//////////////////////////////////////////////////////////////
#include "dicoManage.h"
/* Prototypes : */
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
		printf("\t%s %s\n",entry->traductions->traductions->mot,entry->traductions->traductions->cat);
		entry->traductions = entry->traductions->cdr;
	}while(entry->traductions != NULL);
	return;
}//Fonctionne

/* Fonction de construction part Traductions d'une entry */
void getTraduction(string const ligne, string* mot, string* cat){
	//Initialisation des variables
	int cur = 0;
	int curCat = 0;
	//Parcour de la ligne pour trouver le début de la partie traduction 
	//ainsi que le début de la catégorie de la trad
	for(int i = 0 ; i < strlen(ligne) ; i++){
		if(ligne[i] == '['){
			curCat = i;
		}
		if(ligne[i] == '-' && ligne[i-1] ==' ' && ligne[i+1] == ' '){
			cur = i;
		}
	}
	//Récupération de mot et cat :
		//mot
	size_t sizeMot = curCat - cur - 3;
	*mot = strndup(ligne+cur+2,sizeMot);
		//cat
	size_t sizeCat = strlen(ligne) - curCat -1;
	*cat = strndup(ligne+curCat,sizeCat);
	
	//DEBUG
	//printf("mot : |%s| cat : |%s|\n",*mot,*cat);


	return;
}//Fonctionne



void getOriginal(string const ligne, string* mot, string* cat){
	//Initialisation des variables
	int cur = 0;
	int curCat = 0;

	//Parcour de la ligne pour trouver le début de la partie traduction 
	//ainsi que le début de la catégorie de la trad
	for(int i = 0 ; i < strlen(ligne) ; i++){
		if(ligne[i] == '\t'){
			curCat = i;
		}
		if(ligne[i] == '-' && ligne[i-1] ==' ' && ligne[i+1] == ' '){
			cur = i;
		}
	}

	//Récupération de mot et cat :
		//mot
	size_t sizeMot = curCat;
	*mot = strndup(ligne,sizeMot);
		//cat
	size_t sizeCat = cur- curCat -2;
	*cat = strndup(ligne+curCat+1,sizeCat);
	
	//DEBUG
	//printf("mot : |%s| cat : |%s|\n",*mot,*cat);
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
	startDicoEntry->traductions->traductions = (struct Base*) malloc(sizeof(struct Base*));
	getTraduction(ligne, &startDicoEntry->traductions->traductions->mot, &startDicoEntry->traductions->traductions->cat);
	startTrad = startDicoEntry->traductions;

	//DEBUG
	//printf("Tentative d'affichage de la première entrée :\n");
	//affichEntry(startDicoEntry);


	//Copie du start dans le cur pour commencer la fabrication de la liste dans une boucle
	curDicoEntry = startDicoEntry;
	
	//DEBUG
	int i =0;

	//Boucle de fabrication de la liste
	while(fgets(ligne,TAILLE_MAX,dico)!=NULL){
		tempLigne = strdup(ligne);
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
			curDicoEntry->traductions->traductions = (struct Base*) malloc(sizeof(struct Base*));

				//Instanciation de l'original et de la première traduction

			getOriginal(ligne, &curDicoEntry->original.mot, &curDicoEntry->original.cat);//SEGFAULT (à cause du malloc. 
						//sachant que c'est le fr qui pose problème donc getTrad si dans l'autre sens)(ou peut être manque de place mémoire?)
			getTraduction(ligne, &curDicoEntry->traductions->traductions->mot, &curDicoEntry->traductions->traductions->cat);

				//Enregistrement de l'adresse de la première traduction de l'entrée
			startTrad = curDicoEntry->traductions;
		}
		else{
			//Création d'une nouvelle traduction pour l'entré
				//Allocation de la mémoire pour une nouvelle traduction
			curDicoEntry->traductions->cdr = (struct Traductions*) malloc(sizeof(struct Traductions*));
				//Déplacement du pointeur cur->traductions sur une traduction suivante
			curDicoEntry->traductions = curDicoEntry->traductions->cdr;
			curDicoEntry->traductions->traductions = (struct Base*) malloc(sizeof(struct Base*));

				//Enregistrement de la traduction suivante
			getTraduction(ligne,&curDicoEntry->traductions->traductions->mot, &curDicoEntry->traductions->traductions->cat);
		}

		//DEBUG
		printf("%d\n",i);
		i++;
		
	}
	//Création d'un entrée NULL pour finir le dictionnaire
	curDicoEntry->cdr = NULL;
	return startDicoEntry;
}//Segfault avec les dictionnaire complet (particularité des entrées : elles sont en français.)
