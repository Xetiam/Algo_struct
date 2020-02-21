//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 16/01/2020///
//////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

/* fonction qui retourne la taille d'une chaîne de caractère */
int len(char* s) {
  int i;
  i=0;
  while(s[i]!='\0')
    i++;
  return i;
}

int my_strstrs(const char* prem_mot, const char* deux_mot){
/* Définition de variables */
    char* result = malloc(sizeof(prem_mot));
    int tailChainPrem = len(prem_mot);
    int tailChainDeux = len(deux_mot); 
    int cur =0;
    int compteur =0;

    /* Double boucle de recherche */
    for(int i = 0 ; i<tailChainDeux ; i++){
        for(int j = 0 ; j < tailChainPrem ; j++){
            if (prem_mot[j] == deux_mot[i+j]){
                result[j] = deux_mot[i+j];
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
        free(result);
        return compteur;
    }
