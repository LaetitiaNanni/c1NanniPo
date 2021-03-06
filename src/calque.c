#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//Appel de la structure de l'image
#include "image.h"
//Appel de la structure du calque
#include "calque.h"
#include "lut.h"

/************* Création d'une nouvelle liste de calque *************/
LCalque* new_LCalque(void) {
	
	//Alloue de la mémoire 
	LCalque *p_lcalque = malloc(sizeof(LCalque));
	if (p_lcalque != NULL) {
		p_lcalque->length = 0;
		p_lcalque->p_head = NULL;
		p_lcalque->p_tail = NULL;
	}
	return p_lcalque;
}

/************* Ajouter un calque à la liste  avec une image *************/
int addCalqueImg(LCalque* p_lcalque, float opacity, int mix, char* nameImg) {

	// On vérifie si notre liste a été allouée
	if (p_lcalque != NULL) {
		//Création d'un nouveau calque
		Calque* new_calque = malloc(sizeof(Calque)); 

		// On vérifie si le malloc n'a pas échoué
		if (new_calque != NULL) {

			//Création de la nouvelle image
			Image* new_img = malloc(sizeof(Image));
		
			//On vérifie si le malloc pour l'image n'a pas échoué
			if (new_img != NULL) {

				if(openImg(new_img, nameImg) == 1) {

					new_calque->opacity = opacity; 
					new_calque->mix = mix; 
					new_calque->image_src = new_img;

					//Création de la liste de lut
					LLut* new_llut = malloc(sizeof(LLut));

					// On vérifie si le malloc n'a pas échoué
					if(new_llut != NULL) {
				
						//Initialisation de la liste de lut
						new_llut = new_LLut(new_llut);
						new_calque->p_llut = new_llut;

						returnImage(new_img);

						new_calque->p_next = NULL; 

						// Cas où notre liste est vide (pointeur vers fin de liste à  NULL) et id = 0
						if (p_lcalque->p_tail == NULL) {
							new_calque->id = 0;

							new_calque->p_prev = NULL; 
							 // Pointe la tête de la liste sur le nouveau calque
							p_lcalque->p_head = new_calque;
							// Pointe la fin de la liste sur le nouveau calque
							p_lcalque->p_tail = new_calque;
							//Pointer vers le calque suivant à NULL car on rajoute à la fin de la liste	
							new_calque->p_next = NULL;
						}
						// Cas où des éléments sont déjà présents dans la  liste
						else {
							new_calque->id = (p_lcalque->p_tail->id) + 1;
				
							// Relie le dernier calque de la liste au nouveau calque
							p_lcalque->p_tail->p_next = new_calque; 
							// Pointe p_prev du nouveau calque sur le dernier calque de la liste
							new_calque->p_prev = p_lcalque->p_tail; 
							// Pointe la fin de la liste sur le nouveau calque
							p_lcalque->p_tail = new_calque; 
							//Pointer vers le calque suivant à NULL car on rajoute à la fin de la liste	
							new_calque->p_next = NULL;
						}
						// On augmente de 1 la taille de la liste
						p_lcalque->length++; 
					}
					else  {
						printf("Probleme avec la liste de lut\n");
						return 0;
					}
				}
				else {
					printf("Problème avec l'ouverture d'image\n");
					return 0;
				}
			}
			else {
				printf("probleme d'image\n");
				return 0;
			}
		}
		else {
			printf("Probleme avec le nouveau calque\n");
			return 0;
		}
	}
	else {
		printf("Cette liste de calque n'existe pas\n");
		return 0;
	}

	return 1; 
}

/************* Ajouter un calque vide *************/
int addCalque(LCalque* p_lcalque, float opacity, int mix) {

	int i;

	// On vérifie si notre liste a été allouée
	if (p_lcalque != NULL) {
		//Création d'un nouveau calque
		Calque* new_calque = malloc(sizeof(Calque)); 
		//Création de la nouvelle image
		Image* new_img = malloc(sizeof(Image));
		
		//On vérifie si le malloc pour l'image n'a pas échoué
		if (new_img != NULL) {
		
			//Propriété de l'image
			new_img->magicNumber[0] = 'P';
			new_img->magicNumber[1] = '6';
			new_img->heightImg = p_lcalque->p_head->image_src->heightImg;
			new_img->widthImg = p_lcalque->p_head->image_src->widthImg;
			new_img->maxValue = p_lcalque->p_head->image_src->maxValue;
			
			//Alloue de la mémoire
			new_img->tabPixel = (unsigned char*)malloc( ((new_img->heightImg)*(new_img->widthImg)*3) * sizeof(unsigned char));

			//Remplie le tableau par des pixels blancs (225)
			for(i=0; i< (new_img->heightImg)*(new_img->widthImg)*3; i++) {
				new_img->tabPixel[i]=255;
			}


			// On vérifie si le malloc n'a pas échoué
			if (new_calque != NULL) {

				//Création de la liste de lut
				LLut* new_llut = malloc(sizeof(LLut));

				// On vérifie si le malloc n'a pas échoué
				if(new_llut != NULL) {
				
					//Initialisation de la liste de lut
					new_llut = new_LLut(new_llut);
					new_calque->p_llut = new_llut;

					new_calque->opacity = opacity; 
					new_calque->mix = mix; 

					//Pointer vers le calque suivant à NULL car on rajoute à la fin de la liste	
					new_calque->p_next = NULL; 

					returnImage(new_img);
					new_calque->image_src = new_img;

					new_calque->id = (p_lcalque->p_tail->id) + 1;

					// Relie le dernier calque de la liste au nouveau calque
					p_lcalque->p_tail->p_next = new_calque; 
					// Pointe p_prev du nouveau calque sur le dernier calque de la liste
					new_calque->p_prev = p_lcalque->p_tail; 
					// Pointe la fin de la liste sur le nouveau calque
					p_lcalque->p_tail = new_calque; 

					// On augmente de 1 la taille de la liste
					p_lcalque->length++; 
				}
				else {
					printf("Probleme avec la liste de lut\n");
					return 0;
				}
			}
			else {
				printf("Problème dans la creation du nouveau calque\n");
				return 0;
			}
		}
		else {
			printf("Problème dans la creation de la nouvealle image\n");
			return 0;
		}
	}
	else {
		printf("Cette liste de calque n'existe pas\n");
		return 0;
	}

	return 1; 
}

/************* Ajouter un calque avec une image n'importe ou dans la liste *************/
int addCalqueImgId(LCalque* p_lcalque, float opacity, int mix, Image* img, int id, LLut* p_llut) {

	// On vérifie si notre liste a été allouée
	if (p_lcalque != NULL) {
		//Création d'un nouveau calque
		Calque* new_calque = malloc(sizeof(Calque)); 

		// On vérifie si le malloc n'a pas échoué
		if (new_calque != NULL) {
			new_calque->opacity = opacity; 
			new_calque->mix = mix;

			//Création de la nouvelle image
			Image* new_img = malloc(sizeof(Image));
			if(copyImg(new_img, img) == 0) {
				printf("Probleme au moment de la copie de l'image\n");
				return 0;
			}

			returnImage(new_img);
			new_calque->image_src = new_img;

			//Création de la liste de lut
			LLut* new_llut = malloc(sizeof(LLut));

			// On vérifie si le malloc n'a pas échoué
			if(new_llut != NULL) {
				
				//Initialisation de la liste de lut
				new_llut = new_LLut(new_llut);
				new_llut = copyLLut(p_llut, new_llut);

				new_calque->p_llut = new_llut;

				new_calque->id = id;
				
				//Si c'est le premier calque de la liste
				if (id == 0) {
			
					//Création d'un calque temporaire pour parcourir la liste de calque
					Calque *p_temp = p_lcalque->p_head;
					int i = 0;

					// Parcours de la liste de calque, tant que i est inférieur à la position souhaitée
					while (p_temp != NULL) {
						p_temp->id = ++i;
						p_temp = p_temp->p_next;
					}
					//Libère espace mémoire
					free(p_temp);
					//Pointe le poiteur vers le calque suivant sur le calque en tête
					new_calque->p_next = p_lcalque->p_head; 
					//Pointe le pointeur du calque précédent le calque en tête de liste sur le nouveau calque
				 	p_lcalque->p_head->p_prev = new_calque;
					//Pointe le pointeur du calque en tête vers sur le nouveau calque 
					p_lcalque->p_head = new_calque;
					//Pointeur vers le calque précédent du nouveau calque est NULL
					new_calque->p_prev = NULL;
				
				}
				//Si c'est le dernier calque
				else if(id > p_lcalque->length - 1) {
					new_calque->id = (p_lcalque->p_tail->id) + 1;
				
					// Relie le dernier calque de la liste au nouveau calque
					p_lcalque->p_tail->p_next = new_calque; 
					// Pointe p_prev du nouveau calque sur le dernier calque de la liste
					new_calque->p_prev = p_lcalque->p_tail;
					// Pointe la fin de la liste sur le nouveau calque
					p_lcalque->p_tail = new_calque; 
					//Pointe le pointeur vers le calque suivant du nouveau calque NULL
					new_calque->p_next = NULL;
				}
				else {

					printf("Autre calque \n");
	
					//Création d'un calque temporaire pour parcourir la liste de calque
					Calque *p_tmp = p_lcalque->p_head;

					// Parcours de la liste de calque, tant que i est inférieur à la position souhaitée
					while (p_tmp != NULL) {
						//Des qu l'id correspon à l'id du calque précédent on arrete la boucle
						if(p_tmp->id == id - 1)
							break;
						p_tmp = p_tmp->p_next;
					}
			
					//Relie le nouveau calque au calque suivant (celui qui ce trouve après le calque tmp)
					new_calque->p_next = p_tmp->p_next;
					//Relie le pointeur sur le calque précédent au calque que l'on veut ajouter sur le calqe temporaire
					new_calque->p_prev = p_tmp;
					//Relie le calque suivant au calque précédent du calque que l'on veut ajouter 
					p_tmp->p_next->p_prev = new_calque;
					//Relie le calque précédent au calque suivant du calque que l'on veut ajouter 
					p_tmp->p_next = new_calque;
				

					//Création d'un calque temporaire pour parcourir la liste de calque à partir du calque suivant du calque que l'on veut supprime
					Calque *p_temp = new_calque->p_next;
					int i = new_calque->id;

					// Parcours de la liste de calque, tant que i est inférieur à la position souhaitée
					while (p_temp != NULL) {
						p_temp->id = ++i;
						p_temp = p_temp->p_next;
					}
					//Libère espace mémoire
					free(p_temp);
				}
				// On augmente de 1 la taille de la liste
				p_lcalque->length++; 
			}
			else {
				printf("Erreur avec la liste de lut");
				return 0;
			}
		}
		else {
			printf("Erreur : problème avec la création du nouveau calque\n");
			return 0;
		}
	}
	else {
		printf("Erreur cette liste n'exite pas\n");
		return 0;
	}

	return 1; 
}

/************* Modifier l'opacite d'un calque *************/
int modifOpacity (Calque* p_courant, float opacity){

	// On vérifie si notre calque a été allouée
	if (p_courant != NULL) {
					
		p_courant->opacity = opacity; 
				
	}	
	else {
		printf("Ce calque n'existe pas\n");
		return 0;
	}
	
	return 1;
}

/************* Modifier la fonction de mélange d'un calque *************/
int modifMix (Calque* p_courant, int mix){

	// On vérifie si notre calque a été allouée
	if (p_courant != NULL) {

		//Vérifie qu'il s'agit bien d'une addition ou d'une multiplication
		if(mix == 0 || mix == 1) {

			p_courant->mix = mix; 

		}
		else {
			printf("Erreur : ce n'est ni une addition, ni une multiplication : 0 = addition et 1 = multiplication\n");
			return 0;
		}
	}
	else {
		printf("Ce calque n'existe pas\n");
		return 0;
	}
	
	return 1;
}

/************* Naviguer entre les calques *************/
Calque* navCalque (LCalque* p_lcalque, Calque* p_courant, int id){

	//Création d'un calque temporaire pour parcourir la liste de calque et pointeur vers le calque courant
	Calque *p_tmp = p_lcalque->p_head;

	// On vérifie si notre liste a été allouée
	if (p_courant != NULL) {

		// Parcours de la liste de calque
		while (p_tmp != NULL) {

			if (id == (p_tmp->id)) {				
				break;
			}
			p_tmp = p_tmp->p_next;
		}

	}
	else {
		printf("Ce calque n'existe pas\n");
		return NULL;
	}

	return p_tmp;
}

/************ Remplir le calque d'une couleur uni *************/
int remplirCalque(Calque* p_courant, int red, int green, int blue) {
	
	int i;

	if(p_courant != NULL) {
		
		for(i=0; i< ((p_courant->image_src->heightImg) * (p_courant->image_src->widthImg) * 3); i+=3) {
			
			p_courant->image_src->tabPixel[i]=red;
			p_courant->image_src->tabPixel[i+1]=green;
			p_courant->image_src->tabPixel[i+2]=blue;

		}

	}
	else {
		printf("Ce calque n'existe pas");
		return 0;
	}

	return 1;

}

/************ Afficher la liste de calque ***************/
void afficheLCalque(LCalque* p_lcalque) {
	if (p_lcalque != NULL) {
		//Création du calque temporaire pour parcourrir la liste de calque
		Calque *p_temp = p_lcalque->p_head;

		printf("\n");
		//Parcourt la liste de calque
		while (p_temp != NULL) {
			printf("ID : %d\n", p_temp->id);
			printf("Opacite : %f\n", p_temp->opacity);
			printf("Mode d'operation : %d\n", p_temp->mix);
			printf("\n");
		    	p_temp = p_temp->p_next;
		}

		free(p_temp);
	}
}

/************ Calque courant *************/
int calqueCourant(Calque* p_courant, Image* courant_img) {

	int i;

	//Propriété de l'image
	courant_img->magicNumber[0] = 'P';
	courant_img->magicNumber[1] = '6';
	courant_img->heightImg = p_courant->image_src->heightImg;
	courant_img->widthImg = p_courant->image_src->widthImg;
	courant_img->maxValue = p_courant->image_src->maxValue;
	
	//Alloue de la mémoire
	courant_img->tabPixel = (unsigned char*) malloc((courant_img->widthImg)*(courant_img->heightImg)*3*sizeof(unsigned char));

	if(courant_img->tabPixel != NULL) {
		
		// On vérifie si notre calque a été allouée
		if (p_courant != NULL) {

			//Parcours le tableau de pixel et multiplie par son opacite : pour le premier calque
			for(i=0; i< ((p_courant->image_src->widthImg) * (p_courant->image_src->heightImg)* 3); i++) {

				courant_img->tabPixel[i] = (p_courant->image_src->tabPixel[i]) * (p_courant->opacity);

			}

			//Création d'une lut temporaire pour parcourrir la liste de lut
			Lut *lut_tmp = p_courant->p_llut->l_head;

			//Parcourt la liste de lut et application des lut
			while (lut_tmp != NULL) {
				applyLUT(courant_img, lut_tmp);
			    	lut_tmp = lut_tmp->l_next;
			}

		}
		else {
			printf("Ce calque n'existe pas\n");
			return 0;
		}
	}
	else {
		printf("Erreur d'image\n");
		return 0;
	}

	return 1;

}

/************ Fusionner les calques *************/
Image* fusionCalque(LCalque* p_lcalque) {

	int i, res;

	//Création de la nouvelle image
	Image* final_img = malloc(sizeof(Image));
	
	//Propriété de l'image
	final_img->magicNumber[0] = 'P';
	final_img->magicNumber[1] = '6';
	final_img->heightImg = p_lcalque->p_head->image_src->heightImg;
	final_img->widthImg = p_lcalque->p_head->image_src->widthImg;
	final_img->maxValue = p_lcalque->p_head->image_src->maxValue;
	
	//Alloue de la mémoire
	final_img->tabPixel = (unsigned char*) malloc((final_img->widthImg)*(final_img->heightImg)*3*sizeof(unsigned char));

	if(final_img->tabPixel != NULL) {
	
		// On vérifie si notre liste a été allouée
		if (p_lcalque != NULL) {
		
			//Vérifie qu'il y a plus d'un calque
			if(p_lcalque->length > 1) {
			
				//Création d'un calque temporaire pour parcourir la liste de calque
				Calque *p_tmp = p_lcalque->p_head;

				// Parcours de la liste de calque
				while (p_tmp != NULL) {

					//Premier calque
					if(p_tmp->id == 0) {

						//Parcours le tableau de pixel et multiplie par son opacite : pour le premier calque
						for(i=0; i< ((p_lcalque->p_head->image_src->widthImg) * (p_lcalque->p_head->image_src->heightImg)* 3); i++) {

							final_img->tabPixel[i] = (p_tmp->image_src->tabPixel[i]) * (p_tmp->opacity);

						}

						//Création d'une lut temporaire pour parcourrir la liste de lut
						Lut *lut_tmp = p_tmp->p_llut->l_head;

						//Parcourt la liste de lut et application des lut
						while (lut_tmp != NULL) {

							applyLUT(final_img, lut_tmp);
						    	lut_tmp = lut_tmp->l_next;
						}

					}
					else {

						//Si le mode de fusion est une ADDITION
						if(p_tmp->mix == 0) {

							for(i=0; i< ((p_lcalque->p_head->image_src->widthImg) * (p_lcalque->p_head->image_src->heightImg)* 3); i++) {				
									res = final_img->tabPixel[i] + (p_tmp->opacity)* (p_tmp->image_src->tabPixel[i]);
									res= verifValue(res);
									final_img->tabPixel[i] = res;
							}
						}
						//Autre : le mode de fusion est une MULTIPLICATION
						else {
							
							for(i=0; i< ((p_lcalque->p_head->image_src->widthImg) * (p_lcalque->p_head->image_src->heightImg)* 3); i++) {
								final_img->tabPixel[i] = (1 - (p_tmp->opacity)) * (final_img->tabPixel[i]) + (p_tmp->image_src->tabPixel[i]) * (p_tmp->opacity);

							}

						}
						

						//Création d'une lut temporaire pour parcourrir la liste de lut
						Lut *lut_tmp = p_tmp->p_llut->l_head;

						//Parcourt la liste de lut et application des lut
						while (lut_tmp != NULL) {

							applyLUT(final_img, lut_tmp);
						    	lut_tmp = lut_tmp->l_next;
						}

					}

					p_tmp = p_tmp->p_next;
				}
				//Libère espace mémoire
				free(p_tmp);

			}
			//S'il y a qu'un seul calque
			else {
			
				//Parcours le tableau de pixel et multiplie par son opacite : pour le premier calque
				int h= (p_lcalque->p_head->image_src->widthImg) * (p_lcalque->p_head->image_src->heightImg)* 3;

				for(i=0; i< h; i++) {

					final_img->tabPixel[i] = (p_lcalque->p_head->image_src->tabPixel[i]) * (p_lcalque->p_head->opacity);

				}

				//Création d'une lut temporaire pour parcourrir la liste de lut
				Lut *lut_tmp = p_lcalque->p_head->p_llut->l_head->l_next;

				//Parcourt la liste de lut et application des lut
				while (lut_tmp != NULL) {
					
					applyLUT(final_img, lut_tmp);
				    	lut_tmp = lut_tmp->l_next;
				}
			}
		}
		else {
			printf("Cette liste de calque n'existe pas");
			return NULL;
		}
	}
	else {
		printf("Problème d'allocation memoire pour l'image");
		return NULL;
	}

	return final_img;
}

int verifValue(int res) {

	//Si ça dépasse 255
	if(res>255)
		return 255;
	//Si c'est inférieur à 0
	else if(res<=0)
		return 0;
	else
		return res;
}

/************* Supprimer un calque selon sa position *************/
LCalque* removeCalque(LCalque* p_lcalque, Calque* p_courant) {

	// On vérifie si notre liste a été allouée
	if (p_lcalque != NULL) {

		if(p_courant != NULL) {

			//Vérifie s'il reste au moins un calque, si c'est le dernier calque alors ne le supprime pas
			if(p_lcalque->length > 1) {

				//Si c'est le dernier calque de la liste
				if (p_courant->p_next == NULL) {
					
					//Pointe la fin de la liste sur le calque précédent
					p_lcalque->p_tail = p_courant->p_prev;
					//Lien du dernier calque vers le calque suivant est NULL
					p_lcalque->p_tail->p_next = NULL;
						
				}
			
				//Si c'est le premier calque de la liste
				else if (p_courant->p_prev == NULL) {
					//Pointe la tête de la liste vers le calque suivant
					p_lcalque->p_head = p_courant->p_next;
					//Le lien vers du deuxième calque vers le calque précédent est NULL
			 		p_lcalque->p_head->p_prev = NULL;
					p_lcalque->p_head->id = 0;
						
					//Création d'un calque temporaire pour parcourir la liste de calque
					Calque *p_temp = p_lcalque->p_head->p_next;
					int i = 0;

					// Parcours de la liste de calque, tant que i est inférieur à la position souhaitée
					while (p_temp != NULL) {
						p_temp->id = ++i;
						p_temp = p_temp->p_next;
					}
					//Libère espace mémoire
					free(p_temp);
				}

				else {
					//Relie le calque suivant au calque précédent du calque que l'on veut supprmer 
					p_courant->p_next->p_prev = p_courant->p_prev;
					//Relie le calque précédent au calque suivant du calque que l'on veut supprmer 
					p_courant->p_prev->p_next = p_courant->p_next;

					//Création d'un calque temporaire pour parcourir la liste de calque à partir du calque suivant du calque que l'on veut supprimer
					Calque *p_temp = p_courant->p_next;
					int i = p_courant->p_prev->id;

					// Parcours de la liste de calque, tant que i est inférieur à la position souhaitée
					while (p_temp != NULL) {
						p_temp->id = ++i;
						p_temp = p_temp->p_next;
					}
					//Libère espace mémoire
					free(p_temp);

				}
				//Libère espace mémoire : supprime le calque
				free(p_courant);
				//Décrémente de un la taille de la liste
				p_lcalque->length--;

			}
			else
				printf("Erreur : impossible de supprimer le calque\n");
		}
		else
			printf("Ce calque n'existe pas");
	}
	else 
		printf("Cette liste de calque n'existe pas");

	// on retourne notre nouvelle liste
	return p_lcalque; 
}

/************** Déssallocation de la liste de calque **************/
void removeLCalque(LCalque* p_lcalque) {
	//Si la liste n'est pas vide
	if (p_lcalque->length != 0) {

		//Tant que la liste n'est pas vide
		while (p_lcalque->p_head != NULL) {

			Calque *p_temp = p_lcalque->p_head;
			freeTabImg(p_temp->image_src);
			removeLLut(p_temp->p_llut);
			p_lcalque->p_head = p_temp->p_next;
			free(p_temp);
		}
		
	}
	free(p_lcalque);
}
