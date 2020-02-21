//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 29/01/2019///
//////////////////////////////////////////////////////////////

#include "fonctions.h"
#define TAILLE_MAX 1000


int main(int argc, char* argv[]){
    /* Définition des variables */
    char chaineComp[TAILLE_MAX];
    char *Occur, *OccurPrec;
    int rang, rangPrec, nbrOccur, indice = 0;

    /* Ouverture du fichier d'entrée */
    FILE* fichierEnt = ffopen(argv[3], "r");
    /* Ouverture du fichier de sortie */
    FILE* fichierSor = ffopen(argv[4], "w");

    /* Boucle de recherche et de réécriture */
    while(fgets(chaineComp, TAILLE_MAX, fichierEnt) != NULL){
        char* temp = (char*) malloc(TAILLE_MAX);
        rangPrec = 0;
        Occur = cherchocc(argv[1], chaineComp, 0);//adresse de la première occurence
        nbrOccur = my_strstrs(argv[1], chaineComp);//nombre d'occurence
        rang =  Occur - chaineComp;//rang de la première occurence


        /* Boucle de recherche et de remplacement d'occurence */
        for(int n = 0 ; n <= nbrOccur ; n++){
            if(nbrOccur == 0){
                fputs(chaineComp,fichierSor);
                break;
            }
            indice = n*(strlen(argv[2])-strlen(argv[1]));
            char* temp2 = (char*) malloc(TAILLE_MAX);


            if(Occur != NULL){
                if(rang != 0 && n == 0){
                    temp2 = chainTemp(chaineComp, rang, rangPrec-indice, temp2);
                    strcat(temp, temp2);
                    temp2 = NULL;
                }
                if(rang != 0 && n!=0){
                    temp2 = chainTemp(chaineComp, rang, rangPrec-indice/n, temp2);
                    strcat(temp, temp2);
                    temp2 = NULL;
                }

                strcat(temp, argv[2]);
                rangPrec = rang + strlen(argv[2]);
                OccurPrec = Occur;
            }


            if(Occur == NULL){//Pas de nouvelle occurence : on écrit tout ce qu'il reste après la dernière occurence.


                rang = OccurPrec - chaineComp + strlen(argv[2]);
                temp2= chainTemp(chaineComp, strlen(chaineComp),rang-indice/n,temp2);
                strcat(temp,temp2);
                temp2 = NULL;
                break;
            }


            Occur = cherchocc(argv[1], chaineComp, rangPrec);//chercher les occurences potentiels suivante
            rang = Occur-chaineComp;
            if(rangPrec == strlen(chaineComp)){
                break;
            }
        }
        printf("%s\n", temp);
        fputs(temp, fichierSor);
        temp = NULL;
    }
    /* Fermeture des fichier et libération de la mémoire. */
    fclose(fichierEnt);
    fclose(fichierSor);

    return 0;
}