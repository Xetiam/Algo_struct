//////////////////////////////////////////////////////////////
/// Auteur : Lepiller Charly //////////// Date : 28/02/2020///
//////////////////////////////////////////////////////////////
#include "charlyTrad.h"
static void viderBuffer(void);

int main(int argc, string argv[]){
	//Initialisation des variables
	char motUser[100];
	int choixUser = 0;
	string dicoTab;
	while(choixUser != 3){
		//Interface utilisateur (basique)
		printf("Veuillez choisir le sens de traduction :\n\t 1. Français vers Italien\n\t 2. Italien vers Français\n\t\t3.Exit\n\t");
		scanf("%d",&choixUser);
		if(choixUser == 1){
			dicoTab = "./tabDico/francais-italien_snp.tab";
		}
		else if(choixUser == 2){
			dicoTab = "./tabDico/italien-francais_snp.tab";
		}
		if(choixUser == 1 || choixUser == 2){
			entry dicoEntry = formatageDico(dicoTab);

				//Récupération du mot que l'utilisateur souhaite traduire
			printf("Veuillez entrer le mot ou l'expression à traduire : \n");
			viderBuffer();
			fgets(motUser, sizeof(motUser), stdin);
			//Retrait du retour à la ligne pour pouvoir effectuer la comparaison
			strtok(motUser,"\n");

			entry entryUser = searchEntry(dicoEntry,motUser);
			if(entryUser != NULL)
				affichEntry(entryUser);
		}
	}


	return 0;
}

/* Fonction pour vider le buffer stdin */
static void viderBuffer(void){
     int c;
     while ( ( c=getchar() ) != '\n' && c != EOF );
}