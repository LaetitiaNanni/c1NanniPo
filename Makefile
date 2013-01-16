# $(BIN) est la nom du binaire genere
BIN = ./bin/imagimp
# FLAG
CFLAGS = -Wall -g
LDFLAGS= -Llib/libglimagimp.so -lglimagimp -lglut -lGL -lGLU -lm
#-Llib/libglimagimp.so
# INCLUDES
INC = ./lib/include/
# INCLUDES
LIBDIR = ./lib
# Compilateur
CC = gcc
# SRC
DIR_SRC = src
POINTC = $(wildcard *.c)
SRC = $(wildcard $(DIR_SRC)/*.c)
# OBJET
DIR_OBJ = obj
#OBJ= $(SRC:$(DIR_SRC)/.c=$(DIR_OBJ)/.o)
OBJ = $(DIR_OBJ)/calque.o $(DIR_OBJ)/image.o $(DIR_OBJ)/historique.o $(DIR_OBJ)/histogramme.o $(DIR_OBJ)/ihm.o $(DIR_OBJ)/main.o
OBJ_MAIN = $(DIR_SRC)/main.c lib/include/interface.h lib/include/outils.h $(OBJ)
OBJ_IHM = $(DIR_SRC)/ihm.c lib/include/interface.h lib/include/outils.h


all: $(BIN)

$(BIN):$(OBJ)
	@$(CC) -I$(INC) -o $@ $^ -fPIC -L$(LIBDIR) $(LDFLAGS) 
	@echo "Compilation OK"
	@echo "\n\nPour executer le programme taper: $(BIN)$  images/votre_images.ppm\n\n"

$(DIR_OBJ)/main.o: $(OBJ_MAIN)
	@echo "**** main.o ****"
	$(CC) -I$(INC) $(CFLAGS) -c $< -o $@ -L$(LIBDIR) $(LDFLAGS)
	@echo "Creation $@ OK"
	@echo "****************"

$(DIR_OBJ)/ihm.o: $(OBJ_IHM)
	@echo "**** ihm.o ****"
	$(CC) -I$(INC) $(CFLAGS) -c $< -o $@ -L$(LIBDIR) $(LDFLAGS)
	@echo "Creation $@ OK"
	@echo "****************"

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	@echo "**** $@ ****"
	$(CC) -I$(INC) -o $@ -c $< $(CFLAGS)
	@echo "Creation $@ OK"
	@echo "****************"

clean:
	rm -rf $(DIR_OBJ)/*.o
	@echo "File .o are all removed" 	

mrproper: clean
	rm -rf $(BIN)
	@echo "File .o and .exe are all removed"
	
