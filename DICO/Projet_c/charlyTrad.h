//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 27/02/2020///
//////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define TAILLE_MAX 1000
#define cdr(x) (x)->cdr
#define original(x) (x)->original
#define traductions(x) (x)->traductions
#define mot(x) (x)->mot
#define cat(x) (x)->cat



typedef char* string;
typedef struct Base{
  string mot;
  string cat;
} base;

typedef struct Traductions{
  base* traductions;
  struct Traductions* cdr;
}*traductions;

typedef struct Entry{
  base original;
  traductions traductions;
  struct Entry* cdr;
}* entry;


/* Fonction pour ouvrir un fichier */
FILE* ffopen(char* arg, char* mode);


/* Fonction qui découpe chaque mot d'une chaine et les stock dans un tableau en fonction du séparateur choisis */
int decoupe(char* ligne, char* separ, char* mot[], int maxmot);

void formatageDico();