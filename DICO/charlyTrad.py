##########################################################################################
##### Auteur : Lepiller Charly #################################### Date : 26/02/2020#####
##########################################################################################

#Maquette en python du traducteur

import sys

def formatageDico(m) :
	motPrec = ""
	if(m == 0):
		mode = "francais-italien_snp.tab"
	if(m == 1):
		mode = "italien-francais_snp.tab"
	with open(mode,"r") as fichierEnt :
			fichierEntier = fichierEnt.read()
			lignes = fichierEntier.split("\n")
	dicoTrad = [[],[]]
	for ligne in lignes :
		if ligne != "" :
			tabTmp = ligne.split(" - ")
			partFr = tabTmp[0].split("\t")
			partIt = []
			partIt = tabTmp[1].split(" ")
			dicoTrad[0].append(partFr)
			dicoTrad[1].append(partIt)
	return(dicoTrad)

def findTrad(mot,dicoTrad,m) :
	if m == 0 :
		tailleDico = 6901
	if m == 1 :
		tailleDico = 5925
	tabRang = []
	for i in range(0,tailleDico):
		if(mot == dicoTrad[0][i][0]) :
			tabRang.append(i)
			
	return tabRang

def afficheTrad(tabRang,dicoTrad) :
	print(dicoTrad[0][tabRang[0]][0]+ " " +dicoTrad[0][tabRang[0]][1] + " se dit : "),
	for i in range(0,len(tabRang)) :
		print(dicoTrad[0][tabRang[i]][1]),
		print(":"),
		for j in range(0, len(dicoTrad[1][tabRang[i]])-1):
			print(" "+dicoTrad[1][tabRang[i]][j]),
		print(dicoTrad[1][tabRang[i]][len(dicoTrad[1][tabRang[i]])-1])



print("Bonjour et bienvenu")
exit = False
wantexit = 0
#Boucle du processus pour traduire plusieurs mot
while(exit != True):
	choiceTrad = input("Veuillez choisir :\n\t1. Fr vers It\n\t2. It vers Fr\n\t")
	if choiceTrad == 1:# Fr vers It
		m = 0
		dicoTrad = formatageDico(m)
		mot = input("Fr vers It (entre guillemmet) :")
		tabRang = []
		tabRang = findTrad(mot,dicoTrad,m)
		if tabRang != []:
			afficheTrad(tabRang,dicoTrad)
			wantexit = input("Souhaitez vous traduire un autre mot\n1. Oui\t2. Non\n")
			if(wantexit == 2 ):
				exit =True
		else : print("Aucune traduction n'a ete trouvee dans la base de donnee")

	elif choiceTrad == 2:#It vers Fr
		m = 1
		dicoTrad = formatageDico(m)
		mot = input("It vers Fr (entre guillemmet) :")
		tabRang = []
		tabRang = findTrad(mot,dicoTrad,m)
		if tabRang != []:
			afficheTrad(tabRang,dicoTrad)
			wantexit = input("Souhaitez vous traduire un autre mot ou expression\n1. Oui\t2. Non\n")
			if(wantexit == 2 ):
				exit =True
		else : print("Aucune traduction n'a ete trouvee dans la base de donnee")

