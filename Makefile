#Création des variables
PROG=BlackJack
CC=gcc -Wall
RM= rm -f 
DSRC=src
DBIN=bin
DDOC=doc
DSAVE=save
SRC =$(wildcard $(DSRC)/*.c)
HEAD=$(wildcard $(DSRC)/*.h)
OBJ=$(SRC:$(DSRC)/%.c=$(DBIN)/%.o)


all : $(PROG) clean 

$(PROG) : $(OBJ) #Crée le fichier exécutable
	@$(CC) $^ -o $(DBIN)/$(PROG) -lm

$(OBJ): $(DBIN)/%.o :$(DSRC)/%.c #Crée les fichier.o
	@$(CC) -c $< -o $@

#Permet de supprimer les fichier.o
.PHONY:clean
clean : 
	@$(RM) $(OBJ)

#Permet de créer la documentation Doxygen
.PHONY: doc
doc :
ifneq ("","$(wildcard Doxyfile)")
	@sed -i 's/INPUT                  =/INPUT                  = . src/g' Doxyfile 
	@doxygen Doxyfile
	@mv html $(DDOC)/
	@mv latex $(DDOC)/
else
	@doxygen -g
	@sed -i 's/INPUT                  =/INPUT                  = . src/g' Doxyfile 
	@doxygen Doxyfile
	@mv html $(DDOC)/
	@mv latex $(DDOC)/
endif

#Crée des sauvegardes des fichier.o et .h 
.PHONY: save
save : $(SRC) $(HEAD)
	@rm -f $(DSAVE)/*.c
	@rm -f $(DSAVE)/*.h
	@cp $^ $(DSAVE)


#restore les sauvegardes
restore: $(DSAVE)/*.c $(DSAVE)/*.h 
	@rm -f $(DSRC)/*.c
	@rm -f $(DSRC)/*.h
	@cp $^ $(DSRC)