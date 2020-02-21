//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 22/11/2019///
//////////////////////////////////////////////////////////////

#include <stdio.h>

int main()
{
    /* Déclaration des variable */
    char chaine [] = "Testmod";
    char* ptr = chaine;

    /* Modification de la chaine de caractère */
    *(ptr+1) = 'f';
    //chaine[1] = 'f';

    /* Affichage des deux adresses */
    printf("L'adresse du tableau de char est : %d \nEt l'adresse du pointeur sur cette même chaîne est : %d\n", &chaine , &ptr);
    
    /* Affichage de la chaîne modifiée */
    printf("%s\n%s\n",chaine,ptr);
    return 0;
}