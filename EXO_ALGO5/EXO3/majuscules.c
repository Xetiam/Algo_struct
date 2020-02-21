//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 12/02/2020///
//////////////////////////////////////////////////////////////
#include "fonctions.h"
#define TAILLE_MAX 1000


int main(int argc, char* argv[]){
    /* Définition des variables */
    char* chaineLigne = (char*) malloc(TAILLE_MAX);
    char** tab = (char**) malloc(TAILLE_MAX);
    int nbrMot;

    /* Ouverture du fichier d'entrée */
    FILE* fichierEnt = ffopen(argv[1], "r");
    /* Ouverture du fichier de sortie */
    FILE* fichierSor = ffopen(argv[2], "w");

    while(fgets(chaineLigne, TAILLE_MAX, fichierEnt) != NULL){
        tab = decoupe(chaineLigne, &nbrMot);
        for(int i = 0 ; i < nbrMot ; i++){
            if(tab[i][0]>= 65 && tab[i][0] <= 90){
                fputs(tab[i], fichierSor);
                fputs("\n",fichierSor);
            }
        }
    }
    return 0;
}