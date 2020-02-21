//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 22/11/2019///
//////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#define TAILLE_MAX 100

int main ()
{
    /* Déclaration des variables */
    char ligne[TAILLE_MAX]="";

    /* ouverture du fichier en mode lecture seule */
    FILE* fichier = fopen("test", "r");

    if (fichier != NULL)
    {
        /* Récupération de la chaîne de caractères */
        fgets(ligne,TAILLE_MAX,fichier);
        char* ptr = ligne;

        /* Boucle de lecture, de cast et d'affichage des caractère en int */
        while(*ptr != '\0')//condition pas bonne.
        {
            int aff = (int)*(ptr);
            printf("%d ", aff);
            ptr++;
        }
        printf("\n");
        fclose(fichier); 
        return 0;
    }
    
    else
    {
        printf("Impossible d'ouvrir le fichier test.txt");
        return 0;
    }

}