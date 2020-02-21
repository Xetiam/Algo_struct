##########################################################################################
##### Auteur : Lepiller Charly #################################### Date : 14/02/2020#####
##########################################################################################

#fonction qui decoupe une chaine en mot
def decoupe(st1) :
    mot = ""
    tab = []
    for i in range(0,len(st1)):
        if st1[i] != " " and st1[i] != "," and st1[i] != "." and st1[i] != "\n":
            mot += st1[i]
        if st1[i] == " " or st1[i] == "," or st1[i] == ".":
            tab.append(mot)
            mot = ""
    if st1[len(st1)-1] != "\r" :
        tab.append(mot)
    else :
        tab.append(mot[0:-1])
    
    return tab

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
        


#Definition des variables
with open("fichierEnt.txt","r") as fichierEnt :
    fichierEntier = fichierEnt.read()
    lignes = fichierEntier.split("\n")
fichierSor = open("fichierSor.txt","w")
tabMot = []
tabSor = []
nbrMot = 0

for ligne in lignes :
    tabMot = decoupe(ligne)
    nbrMot = my_strstrs(ligne, " ")+1
    for i in range(0,nbrMot-1):
        if tabMot[i][0].isupper() :
            tabSor.append(tabMot[i])



for maj in tabSor :
    maj += "\n"
    fichierSor.write(maj)
fichierSor.close()