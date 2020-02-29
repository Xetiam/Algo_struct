############################################################
### Auteur: Charly Lepiller / replace / Date: 28/02/2020 ###
############################################################

#Variables
CC=gcc
CCFLAG = -g -Wall

EXEC = charlyTrad
SRC=$(wildcard *.c)
OBJ= $(SRC:.c=.o)

All: $(EXEC)

#Génération d'executables
charlyTrad: $(OBJ)
	@$(CC) -o $@ $^ $(CCFLAG) 
	@echo $@ "generated"

charlyTrad.o : charlyTrad.h
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