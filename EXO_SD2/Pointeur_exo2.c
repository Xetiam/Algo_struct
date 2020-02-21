//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 20/11/2019///
//////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define VARIANTE1

#ifdef VARIANTE1
int main (int argc, char* argv[])
{
    /* Initiamisation de variable */
    int taille = strlen(argv[argc-1]);

    /* Boucle de lecture de la chaine de caractère en variante 1 */
    for(int i = 0 ; i < taille ; i++)
    {
        printf("%c", argv[argc-1][i]); 
    }    
    printf("\n");
    return 0;
}
#endif

#ifdef VARIANTE2 // rien de correcte
int main (int argc, char* argv[])
{
    /* Initiamisation de variable */
    int taille = strlen(argv[argc-1]);
    char* ptr = &(argv[argc-1][0]);

    /* Boucle de lecture de la chaine de caractère en variante 2 */
   for(int i = 0 ; i < taille ; i++)
   {
        printf("%c", *(ptr+i));
    }
    printf("\n");
    return 0;
}
#endif
