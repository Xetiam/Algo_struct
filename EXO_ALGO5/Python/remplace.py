##########################################################################################
##### Auteur : Lepiller Charly #################################### Date : 13/02/2020#####
##########################################################################################

# Fonction qui chercher la premiere occurence de chaine2 dans chaine1
def cherchOccur(chaine1,chaine2,rang) :
    result=0
    tailChainPrem = len(chaine1)
    tailChainDeux = len(chaine2)
    cur = 0


    for i in range (rang, tailChainPrem-(tailChainDeux-1)) :
        for j in range (0,tailChainDeux) :
            if chaine2[j] == chaine1[i+j]:
                result = i
                cur+=1
                if cur == tailChainDeux:
                    return result
            else :
                cur = 0
    return -1

# Fonction qui compte le nombre d'occurence de chaine2 dans chaine1
def my_strstrs(chaine1,chaine2):
    tailPrem = len(chaine1)
    tailDeux = len(chaine2)
    cur = 0
    compteur = 0
    for i in range(0,tailPrem - (tailDeux-1)):
        for j in range(0,tailDeux):
            if chaine2[j] == chaine1[i+j] :
                cur+=1
                if cur == tailDeux:
                    compteur+=1
        cur = 0
    return compteur


# Variable
rang = 0
rangPrec = 0
nbrOccur = 0
remp = input("Veuillez entrer le mot a remplacer entre guillemet :")
par = input("Veuillez entrer le mot qui va remplacer entre guillemet :")
newLigne = ""
fichierSor = open("fichierSor.txt","w")
with open("fichierEnt.txt","r") as fichierEnt :
    fichierEntier = fichierEnt.read()
    lignes = fichierEntier.split("\n")

# Boucle de recherche et de remplacement d'occurrence
for ligne in lignes :
    nbrOccur = my_strstrs(ligne, remp)
    if nbrOccur == 0 :
        fichierSor.write(ligne)
    elif nbrOccur > 0 :
        rang = cherchOccur(ligne,remp,rangPrec)
        for n in range(0,nbrOccur) : 


            if n+1 < nbrOccur :
                newLigne = newLigne + ligne[rangPrec : rang] + par
                rangPrec = rang + len(remp)


            elif n+1 == nbrOccur :
                if rang + len(remp) < len(ligne):
                    newLigne = newLigne + ligne[rangPrec : rang] + par + ligne[rang+len(remp) : len(ligne)]
                    break
                elif rang + len(remp) == len(ligne) :
                    newLigne = newLigne + ligne[ranPrec : rang] + par
                    break

            rang = cherchOccur(ligne, remp, rangPrec)

    newLigne = newLigne + "\n"
    fichierSor.write(newLigne)
    newLigne = ""
    rang = 0
    rangPrec = 0
fichierSor.close()
