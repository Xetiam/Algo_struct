//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 20/01/2020///
//////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

char* my_strchr(char recherche, const char* chaine){
    /* Définition des variables */
    char* position = NULL;
    int i = 0;

    /* Boucle de recherche d'occurence */
    while(chaine[i] != '\0'){
        if(chaine[i] != recherche){
            position = NULL;
        }
        else{
            position = &chaine[i];
            return position;
        }
        ++i;
    }
    /* Pas d'occurence trouvée */
    return position;

}
