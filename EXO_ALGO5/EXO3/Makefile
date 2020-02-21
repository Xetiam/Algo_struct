############################################################
### Auteur: Charly Lepiller / replace / Date: 03/02/2020 ###
############################################################

#Variables
EXEC = majuscules
CC=gcc
CCFLAG=-Wall
SRC=$(wildcard *.c)
OBJ= $(SRC:.c=.o)

All: $(EXEC)

#Génération d'executables
majuscules: $(OBJ)
	@$(CC) -o $@ $^ $(CCFLAG) 
	@echo $@ "generated"

majuscules.o : fonctions.h
#Génération des .o
%.o: %.c
	@$(CC) -o $@ -c $< $(CCFLAG) 
	@echo $@ "generated"

#Clean and Cleanall
.PHONY: clean cleanall

clean: 
	@rm -rf *.o
	@echo ".o supprimer"

cleanall: clean
	@rm -rf $(EXEC)
	@echo "exec supprimer"