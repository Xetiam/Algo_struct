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
        


#Definition des variables
with open("fichierEnt.txt","r") as fichierEnt :
    fichierEntier = fichierEnt.read()
    lignes = fichierEntier.split("\n")
mot = input("Veuillez entrer le mot a compter le nombre doccurence entre guillemet :")
tabMot = []
compteur = 0

#Boucle pour compter les occurences de 
for ligne in lignes :
    tabMot = decoupe(ligne)
    for i in range(0, len(tabMot)) :
        if mot == tabMot[i] : 
            compteur+=1
print compteur