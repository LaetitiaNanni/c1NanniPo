//ficher servant à déclarer les fonctions qui feront des opérations sur les images
//il faut aussi creer un .h 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//Appel de la structure de l'image
#include "image.h"

/************* Ouverture de l'image => Lecture de l'image ************/

int openImg(Image* img, char* nameImg){

	FILE* image = NULL;
	image = fopen(nameImg, "r");
	int test;	

	if(image == NULL){
		printf("Erreur : Impossible d'ouvrir l'image\n");
		return 0;
	}
	else{

		//Récupère le type d'image
		fscanf(image, "%c%c\n", &(img->magicNumber[0]),  &(img->magicNumber[1]));

		//Si ce n'est pas un ppm, arrete la fonction 
		if(img->magicNumber[0] != 'P' || img->magicNumber[1] != '6'){
			printf("L'image n'est pas au bon format\n");
			return 0;
		}
		else {
			
			//Vérifier s'il y a un commentaire
			do {
				//Récupère la hauteur et la largeur && test = 1 s'il trouve une variable sinon retourne 0
				test = fscanf(image, "%d %d\n", &(img->widthImg), &(img->heightImg));
				
				//Si c'est une ligne de commentaire
				if(test == 0) {
					char* letter;
					//Passe la ligne : parcours la ligne jusqu'à qu'il trouve '\n'
					do {
						fread(&letter,sizeof(char*),1,image);
					}while(*letter != '\n');
				}			
			}while(test<1);

			//Récupérer la résolution de la couleur
			fscanf(image, "%d\n", &(img->maxValue));			

			//Alloue de la mémoire
			img->tabPixel = (unsigned char*)malloc( ((img->heightImg)*(img->widthImg)*3) * sizeof(unsigned char));
			//Récupère les pixels et les stock dans un tableau de taille : hauteur * largeur * 3 car chaque pixel est composé de 3 couleurs
			fread(img->tabPixel, sizeof(unsigned char),(img->heightImg)*(img->widthImg)*3,image);
				
			// On ferme le vide le buffer et on ferme l'image
			fflush(image);
			fclose(image);

		}
	}
	return 1;
}

/*void main(void){
	Image image;
	Image* p = &image;
	char name[]="../images/image.ppm";
	openImg(p, name);
	printf("%c%c\n %d %d\n %d\n", p->magicNumber[0], p->magicNumber[1], p->heightImg, p->widthImg, p->maxValue);
	//printf("%s\n", p->tabPixel);
	printf("\n\n\n\n\n");

	unsigned char* tab =(unsigned char*) malloc((p->widthImg)*(p->heightImg)*3*sizeof(unsigned char));

	printf("apres fonction : ");
	printf("\n\n\n\n\n");
	returnImage(p, tab);

	int i, j, k=0;

	printf("%s\n", tab);
}*/


/************* Retourner l'image ************/

int returnImage(Image* img) {
	int i, j, k=0;

	unsigned char* tab =(unsigned char*) malloc((img->widthImg)*(img->heightImg)*3*sizeof(unsigned char));
	
	if (tab == NULL) {
		printf("Erreur d'allocation\n");
		return 0;
	}

	// On parcourt les lignes du tableau à l'envers
	for(i=(img->heightImg); i>0; i--) {

		// puis on parcourt les colonnes du tableau
		for(j=0; j<(img->widthImg); j++) {
			
			// On retourne le tableau de l'image de haut en bas
			tab[k++] = img->tabPixel[i*(img->widthImg)*3+j*3];
			tab[k++] = img->tabPixel[i*(img->widthImg)*3+j*3+1];
			tab[k++] = img->tabPixel[i*(img->widthImg)*3+j*3+2];
		}
	}

	img->tabPixel = tab;

	return 1;
}

/************ Creation d'une image à partir d'une autre image : copie ************/
int copyImg(Image* new_img, Image* img){

	int i;

	//Propriété de l'image
	new_img->magicNumber[0] = 'P';
	new_img->magicNumber[1] = '6';
	new_img->heightImg = img->heightImg;
	new_img->widthImg = img->widthImg;
	new_img->maxValue = img->maxValue;

	//Alloue de la mémoire
	new_img->tabPixel = (unsigned char*)malloc( ((new_img->heightImg)*(new_img->widthImg)*3) * sizeof(unsigned char));

	if(new_img->tabPixel != NULL) {

		//Remplie le tableau par des pixels blancs (225)
		for(i=0; i< (new_img->heightImg)*(new_img->widthImg)*3; i++) {
			new_img->tabPixel[i]= img->tabPixel[i];
		}
	}
	else {
		printf("Erreur d'allocation pour le tableau de pixel");
		return 0;
	}
	
	return 1;
}

/************ Sauvegrade de l'image finale **************/
int saveImg(Image* img, char* nameImg){
	FILE* image = NULL;
	image = fopen(nameImg, "w");

	if(image != NULL) {

		//Ecriture du numéro magique dans le fichier
		fprintf(image, "%c%c\n", (img->magicNumber[0]),  (img->magicNumber[1]));
		//Ecriture de la hauteur et de la laageur dans le fichier
		fprintf(image, "%d %d\n", (img->widthImg), (img->heightImg));
		//Ecriture de la résolution de la couleur dans le fichier
		fprintf(image, "%d\n", (img->maxValue));
		//Retourne le tableau de pixel pour que l'image soit à l'endroit
		returnImage(img);			

		//Ecriture du tableau de pixel dans le fichier
		fwrite(img->tabPixel, sizeof(unsigned char),(img->heightImg)*(img->widthImg)*3,image);

		//Fermeture du fichier
		fclose(image);
		
		return 1;

	}
	else {
		printf("Erreur : il y a un probleme avec l'image finale");
		return 0;
	}
}

/************* Libéré l'espace mémoire *************/
void freeTabImg(Image* img) {
	free(img->tabPixel);
	return;
}	
	
