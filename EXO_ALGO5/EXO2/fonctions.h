//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 31/01/2020///
//////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define TAILLE_MAX 1000
#define TAILLE_MAX2 30

/* Fonction qui cherche la premiere occurence de deux_mot dans prem_mot  */
char* cherchocc(const char* prem_mot, char* deux_mot, int rang);

/* Fonction qui compte le nombre d'occurence de deux_mot dans prem_mot */
int my_strstrs(const char* prem_mot, const char* deux_mot);

/* Fonction pour ouvrir un fichier */
FILE* ffopen(char* arg, char* mode);


/* Fonction qui concatène deux chaîne de caractère */
char* chainTemp(char* st1, int rang, int rangPrec, char* temp);

/* Fonction qui découpe chaque mot d'une chaine et les stock dans un tableau */
char** decoupe(char* st1, int* nbrMot);