//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 27/02/2020///
//////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define TAILLE_MAX 1000
#define TAILLE_MAXD 7000
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
	traductions traductions;//faire une fonction getTraductions
	struct Entry* cdr;
}*entry;



/* Fonction pour formater le dictionnaire dans une structure permettant une accessibilité facile */
entry formatageDico(string tabDico);

/*Fonction qui affiche le mot original et toutes ses traductions */
void affichEntry(entry entry);