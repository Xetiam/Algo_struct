def my_strstrs(chaine1,chaine2):
    tailPrem = len(chaine1)
    tailDeux = len(chaine2)
    print(tailPrem)
    print(tailDeux)
    cur = 0
    compteur = 0
    for i in range(0,tailPrem - (tailDeux-1)):
        for j in range(0,tailDeux):
            if chaine2[j] == chaine1[i+j] :
                cur+=1
                if cur == tailDeux:
                    compteur+=1
                    print("Compteur =",compteur)
        cur = 0
    return compteur

chaine1 = "toto je suis ton pere toto toto too toto toto"
chaine2 = "toto"
nbrOccur = 0
nbrOccur = my_strstrs(chaine1,chaine2)
print("balafre" + chaine1[4:len(chaine1)])