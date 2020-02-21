//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 05/11/2019///
//////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAILLE_MAX 100
#define nbr_ligne 4


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
    struct adresse adresse1;
    char lignecurs [TAILLE_MAX];

    /* ouverture du fichier en mode lecture seule */
    FILE* fichier2 = fopen("adresse.txt", "r");
    
    /* Test de la bonne ouverture du fichier */
    if (fichier2 != NULL)
    {
        /* Récupération des différents élément de l'adresse */
        fgets(lignecurs, TAILLE_MAX,fichier2);
        adresse1.num = atoi(lignecurs);

        fgets(lignecurs, TAILLE_MAX,fichier2);
        strcpy(adresse1.voie,lignecurs);
        adresse1.voie[strlen(adresse1.voie)-2] = '\0' ;

        fgets(lignecurs, TAILLE_MAX,fichier2);
        strcpy(adresse1.nomvoie,lignecurs);
        adresse1.nomvoie[strlen(adresse1.nomvoie)-2] = '\0' ;

        fgets(lignecurs, TAILLE_MAX,fichier2);
        strcpy(adresse1.ville,lignecurs);
        adresse1.ville[strlen(adresse1.ville)-2] = '\0' ;

        fgets(lignecurs, TAILLE_MAX,fichier2);
        adresse1.cdpost = atoi(lignecurs);
        
        fclose(fichier2); 

    /* Affichage de l'adresse enregistrée */
        printf("%d %s %s, %s %d \n",adresse1.num,adresse1.voie,adresse1.nomvoie,adresse1.ville,adresse1.cdpost);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier adresse.txt\n");
    }
    
    return 0;
}