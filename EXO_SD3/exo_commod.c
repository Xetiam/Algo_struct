//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 29/11/2019///
//////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

/* Définition de la structure (liste chaînée de void*) */
typedef struct Doublet {
    void* car;
    struct Doublet* cdr;
} *list;



/* prototypes */
list consVoid(void* elt, const list L);
list consInt(int elt, const list L);
void suppr(list L);
void* car(list L);
struct Doublet* cdr(list L);
void* caar(list L);
list cadr(list L);
void carSet(void* ptr);
void cdrSet(list L);

/* Implémentation de car cdr caar cadr en fonction (getter)*/
void* car(list L){
    return L->car;
}

struct Doublet* cdr(list L){
    return L->cdr;
}

/* void* caar(list L){
    return (L->car)->car;
} */

list cadr(list L){
    return (L->cdr)->car;
}

/* Implémentation de getter pour afficher les valeurs */
int carValInt(list L){
    return *(int*)(car(L));
}
int cadrValInt(list L){
    return *(int*)(cadr(L));
}

/* Permet la création de la liste chaînée d'élément de type int */
list consInt(int elt, const list L){
    int* ptr = malloc(sizeof(int));
    *ptr = elt;
    list cons = consVoid((void*)ptr, L);
    
    return cons;
}

/* Fonction permettant de push un doublet sur une liste chaînée */
list consVoid(void* elt, const list L){
    list Cons = malloc(sizeof(struct Doublet));
    Cons->car = elt;
    Cons->cdr = L;

    return Cons;
}

void suppr(list L){
    free(cadr(cdr(L)));
    free(cadr(L));
    free(cdr(L));
    free(L);
}

int main()
{
    /* Création de liste par création succéssive de doublet */
    list L = consInt(4, L);
    L = consInt(18, L);
    L = consInt(12, L);
    L = consInt(25, L);
    

    /* Affichage de la liste */
    printf("%d\n", carValInt(L));
    printf("%d\n", cadrValInt(L));
    printf("%d\n", cadrValInt(cdr(L)));
    printf("%d\n", cadrValInt(cdr(cdr(L))));
    /* printf("%p\n", caar(L)); */ //Je ne comprend pas quoi afficher

    suppr(L);
    return 0;
}