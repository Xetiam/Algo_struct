//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 16/12/2020///
//////////////////////////////////////////////////////////////

#include <stdio.h>
#define LONG_MAX 10

int main(){
    /* Définition de variables et des chaîne de caractère à comparé */
    char* prem_mot = "bcde" ;
    char* deux_mot = "abcde" ;
    int result = 0;
    /* Comparaison des deux chaîne */
    for(int i = 0; i< LONG_MAX ; i++){
        if ((int)prem_mot[i] == (int)deux_mot[i]){//si les caractères sont égaux : enregistrement de 0
            result = 0;
        }
        
        else if ((int)prem_mot[i] < (int)deux_mot[i]){
            result = -1;
            printf("Résultat : %d\n", result);
            return result;
        }
        
        else if ((int)prem_mot[i] > (int)deux_mot[i]){
            result = 1;
            printf("Résultat : %d\n", result);
            return result;
        }
        
        else if ((int)prem_mot[i] == 0 || (int)deux_mot[i] == 0){
            if((int)prem_mot[i] == 0){
                result = -1;
            }
            else{
                result = 1;
            }
            printf("Résultat : %d\n", result);
            return result;
        }
    }
    printf("Résultat : %d\n", result);
    return result;
}