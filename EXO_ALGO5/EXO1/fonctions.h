//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 31/01/2020///
//////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Fonction qui cherche la premiere occurence de deux_mot dans prem_mot  */
char* cherchocc(const char* prem_mot, char* deux_mot, int rang);

/* Fonction qui compte le nombre d'occurence de deux_mot dans prem_mot */
int my_strstrs(const char* prem_mot, const char* deux_mot);

/* Fonction pour ouvrir un fichier */
FILE* ffopen(char* arg, char* mode);


/* Utiliser uniquement dans la V2 */
/* Fonction qui concatène deux chaîne de caractère */
char* chainTemp(char* st1, int rang, int rangPrec, char* temp);