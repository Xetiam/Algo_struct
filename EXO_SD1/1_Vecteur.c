//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 05/11/2019///
//////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAILLE_MAX 100
#define nbr_ligne 6

int main ()
{

    /* Déclaration des variables */
    char tabchar[nbr_ligne][TAILLE_MAX];
    float tabfloat[TAILLE_MAX];
    int tabint[TAILLE_MAX];
    long int tablong[TAILLE_MAX];
    char tabdonnees[TAILLE_MAX];
    
    /* ouverture du fichier en mode lecture seule */
    FILE* fichier = fopen("test.txt", "r");
    
    /* Test de la bonne ouverture du fichier */
    if (fichier != NULL)
    {
        /* boucle de lecture et de récupération des données */
        for(int i = 0 ; i<=nbr_ligne-1 ; i++)
        {
            fgets(tabdonnees, TAILLE_MAX,fichier);
            strcpy(tabchar[i],tabdonnees);
            tabfloat[i] = atof(tabdonnees);
            tabint[i] = atoi(tabdonnees);
            tablong[i] = atol(tabdonnees);
        }
        fclose(fichier); 
    }
    else
    {
        printf("Impossible d'ouvrir le fichier test.txt\n");
    }
    
    /* Affichage des données stockées */
    printf("Tableau de char :\n");
    for(int i = 0 ; i <= nbr_ligne-1 ; i++)
    {
        printf("%d. %s",i+1, tabchar[i]);
    }

    printf("\n\nTableau de float :\n");
    for(int i = 0 ; i <= nbr_ligne-1 ; i++)
    {
        printf("%d. %f \n",i+1, tabfloat[i]);
    }

    printf("\nTableau de int :\n");
    for(int i = 0 ; i <= nbr_ligne-1 ; i++)
    {
        printf("%d. %d \n",i+1, tabint[i]);
    }

    printf("\nTableau de long int :\n");
    for(int i = 0 ; i <= nbr_ligne-1 ; i++)
    {
        printf("%d. %ld \n",i+1, tablong[i]);
    }
    return 0;
}