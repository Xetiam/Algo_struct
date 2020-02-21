//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 05/02/2020///
//////////////////////////////////////////////////////////////

#include "fonctions.h"

int main(int av, char* argv[]){
    /* Définitions des variables */
    char* chaineLigne = (char*) malloc(TAILLE_MAX);
    char** tab = (char**) malloc(TAILLE_MAX);
    int nbrMot;
    int compteur = 0;
    int compteurTemp =0;

   FILE* fichier = ffopen(argv[2], "r");

   while(fgets(chaineLigne, TAILLE_MAX, fichier) != NULL){
       tab = decoupe(chaineLigne, &nbrMot);
       compteurTemp = 0;
       for(int i = 0 ; i < nbrMot; i++){
           if(strcmp(tab[i],argv[1])==0){
               compteurTemp++;
                printf("Voici le nombre d'occurence de %s : %d\n",argv[1],compteurTemp);
            }

       }
        compteur = compteurTemp+compteur;
    }
    printf("Voici donc le nombre d'occurence total de %s : %d\n",argv[1],compteur);
    return 0;
}