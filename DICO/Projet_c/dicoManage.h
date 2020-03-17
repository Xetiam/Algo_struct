//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 27/02/2020///
//////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define TAILLE_MAX 100




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

/* Fonction pour chercher et renvoyé l'entrée correspondant à la demande utilisateur */
entry searchEntry(entry dico,string motUser);

