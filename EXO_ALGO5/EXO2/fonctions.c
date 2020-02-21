//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 31/01/2020///
//////////////////////////////////////////////////////////////
#include "fonctions.h"

/* chercher la premiere occurence de deux_mot dans prem_mot  */
char* cherchocc(const char* prem_mot, char* deux_mot, int rang){
    /* Définition de variables */
    char* result = malloc(sizeof(prem_mot));
    int tailChainPrem = strlen(prem_mot);
    int tailChainDeux = strlen(deux_mot); 
    int cur =0;

    /* Double boucle de recherche */
    for(int i = rang ; i<tailChainDeux ; i++){
        for(int j = 0 ; j < tailChainPrem ; j++){
            if (prem_mot[j] == deux_mot[i+j]){
                result = &(deux_mot[i]);
                cur++;
                if(cur == tailChainPrem){//Condition de première occurence trouvé
                    
                    return result;
                }
            }
            else{
                cur = 0;
            }
        }
    }
    
    //Aucune occurence trouvé
        return NULL;
    }

/* Fonction qui compte le nombre d'occurence de deux_mot dans prem_mot */
int my_strstrs(const char* prem_mot, const char* deux_mot){
    /* Définition de variables */
    int tailChainPrem = strlen(prem_mot);
    int tailChainDeux = strlen(deux_mot); 
    int cur =0;
    int compteur =0;

    /* Double boucle de recherche */
    for(int i = 0 ; i<tailChainDeux ; i++){
        for(int j = 0 ; j < tailChainPrem ; j++){
            if (prem_mot[j] == deux_mot[i+j]){
                cur++;
                if(cur == tailChainPrem){//Condition d'occurence trouvé
                    compteur++;
                }
            }
            else{
                cur = 0;
            }
        }
    }
        return compteur;
    }





/* Fonction pour ouvrir un fichier */
FILE* ffopen(char* arg, char* mode){
    FILE* fichier = fopen(arg, mode);
    if(fichier == NULL){
        printf("Fichier %s introuvable\n",arg);
        return 0;
    }
    return fichier;
    }

/* Fonction qui concatène deux chaîne de caractère */
char* chainTemp(char* st1, int rang, int rangPrec, char* temp){
    for(int i = rangPrec ; i < rang ; i++){
        temp[i - rangPrec] = st1[i];
    }
    return temp;
}

/* Fonction qui découpe chaque mot d'une chaine et les stock dans un tableau */
char** decoupe(char* st1, int* nbrMot){
    *nbrMot = my_strstrs(" ",st1)+1;
    int cur = 0;
    int curPrec = 0;
    int curTab = 0;
    char** tab = malloc(*nbrMot * sizeof(char*));
    printf("%s\n",st1);
    do{
        if(st1[cur] == ' '){
            char* mot = malloc(TAILLE_MAX2 * sizeof(char));
            for(int i = curPrec ; i < cur ; i++){
                if(st1[i] != ','){
                    mot[i-curPrec] = st1[i];
                }
            }
            tab[curTab] = mot;
            mot = "\0";
            curTab++;
            
            curPrec = cur+1;
        }
        cur++;
        if(st1[cur] == '\0'){
            char* mot = malloc(TAILLE_MAX2 * sizeof(char));
            for(int i = curPrec ; i < cur-1 ; i++){
                if(st1[i] != '.'){
                    mot[i-curPrec] = st1[i];
                }
            }
            tab[curTab] = mot;
            mot = "\0";
            break;
        }
    }while(st1[cur]!='\0');
    for (int k= 0;k<*nbrMot;k++){
        printf("%s\n",tab[k]);
    }
    return tab;
}
