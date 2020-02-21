//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 08/11/2019///
//////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAILLE_MAX 100
#define nbr_adresse 3


/* Définition de la structure */
struct adresse{
int num;
char voie[10];
char nomvoie[20];
char ville[15];
int cdpost;
};

int main()
{
    /* Définition des variables */
    struct adresse adresse[nbr_adresse];
    char lignecurs [TAILLE_MAX];

    /* ouverture du fichier en mode lecture seule */
    FILE* fichier = fopen("adresses.txt", "r");
    
    /* Test de la bonne ouverture du fichier */
    if (fichier != NULL)
    {
        /* boucle de lecture et de récupération des données */
        for(int i = 0 ; i<=nbr_adresse-1 ; i++)
        {
        /* Récupération des différents élément de l'adresse */
            fgets(lignecurs, TAILLE_MAX,fichier);
            adresse[i].num = atoi(lignecurs);

            fgets(lignecurs, TAILLE_MAX,fichier);
            strcpy(adresse[i].voie,lignecurs);
            adresse[i].voie[strlen(adresse[i].voie)-2] = '\0' ;

            fgets(lignecurs, TAILLE_MAX,fichier);
            strcpy(adresse[i].nomvoie,lignecurs);
            adresse[i].nomvoie[strlen(adresse[i].nomvoie)-2] = '\0' ;

            fgets(lignecurs, TAILLE_MAX,fichier);
            strcpy(adresse[i].ville,lignecurs);
            adresse[i].ville[strlen(adresse[i].ville)-2] = '\0' ;

            fgets(lignecurs, TAILLE_MAX,fichier);
            adresse[i].cdpost = atoi(lignecurs);
        }
        fclose(fichier); 
    }
    else
    {
        printf("Impossible d'ouvrir le fichier test.txt\n");
    }
    for(int j = 0 ; j < nbr_adresse ; j++)
    {
        printf("%d %s %s, %s %d \n",adresse[j].num,adresse[j].voie,adresse[j].nomvoie,adresse[j].ville,adresse[j].cdpost);
    }
    return 0;
}