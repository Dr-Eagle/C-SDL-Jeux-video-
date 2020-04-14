#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "Collision.h"

void initialiser_collision_multi(collision *c)
{
	c->bg_collision=IMG_Load("Image/multiplayer/mapcol.png");
	printf("bg collision multi initialise\n");
}

void initialiser_collision(collision *c,int stage)
{
	char nom[30];
	sprintf(nom,"Image/stage%dcol",stage+1);
    strcat(nom,".png");
	c->bg_collision=IMG_Load(nom);

	printf("collision initialise\n");
}

SDL_Color recuperer_couleur(SDL_Surface *fond_collision,SDL_Rect position)
{
	SDL_Color couleur;
	Uint32 coul =0;

	char* Pposition = fond_collision->pixels;

	Pposition+=fond_collision->pitch *position.y;
	Pposition+=fond_collision->format->BytesPerPixel *position.x;
	memcpy(&coul ,Pposition, fond_collision->format->BytesPerPixel);
	SDL_GetRGB(coul,fond_collision->format,&couleur.r,&couleur.g,&couleur.b);

	//printf("couleur recuperee\n");

	return couleur;
}

int verifier_collision(SDL_Surface *fond_collision,SDL_Rect position_camera,SDL_Rect position_voiture)
{
	SDL_Color couleur_col;
	SDL_Color couleur_recupere1;
	SDL_Color couleur_recupere2;
	SDL_Color couleur_recupere3;
	SDL_Color couleur_recupere4;

	SDL_Rect position1,position2,position3,position4,position;
	int largeur=294,hauteur=211,bord=100;

	position.x=position_camera.x+position_voiture.x;
	position.y=position_camera.y+position_voiture.y;

	position1.x=position.x+(largeur/2);
	position1.y=position.y+bord;
	position2.x=position.x+largeur-bord;
	position2.y=position.y+(hauteur/2);
	position3.x=position.x+(largeur/2);
	position3.y=position.y+hauteur-bord;
	position4.x=position.x+bord;
	position4.y=position.y+(hauteur/2);

	couleur_col.r=255;
	couleur_col.g=255;
	couleur_col.b=255;

	couleur_recupere1=recuperer_couleur(fond_collision,position1);
	couleur_recupere2=recuperer_couleur(fond_collision,position2);
	couleur_recupere3=recuperer_couleur(fond_collision,position3);
	couleur_recupere4=recuperer_couleur(fond_collision,position4);

	if(couleur_col.r==couleur_recupere1.r&&couleur_col.g==couleur_recupere1.g&&couleur_col.b==couleur_recupere1.b)
	{
		//printf("collision\n");
		return 1;
	}
	if(couleur_col.r==couleur_recupere2.r&&couleur_col.g==couleur_recupere2.g&&couleur_col.b==couleur_recupere2.b)
	{
		//printf("collision\n");
		return 1;
	}
	if(couleur_col.r==couleur_recupere3.r&&couleur_col.g==couleur_recupere3.g&&couleur_col.b==couleur_recupere3.b)
	{
		//printf("collision\n");
		return 1;
	}
	if(couleur_col.r==couleur_recupere4.r&&couleur_col.g==couleur_recupere4.g&&couleur_col.b==couleur_recupere4.b)
	{
		//printf("collision\n");
		return 1;
	}

	//printf("pas de collision\n");
	return 0;
}

int collision_tournant(SDL_Surface *fond_collision,SDL_Rect centre_voiture)
{
	SDL_Color couleur_recuperee,couleur1,couleur2,couleur3,couleur4;

	couleur_recuperee=recuperer_couleur(fond_collision,centre_voiture);

	couleur1.r=0; couleur1.g=0; couleur1.b=255;
	couleur2.r=255; couleur2.g=255; couleur2.b=0;
	couleur3.r=255; couleur3.g=0; couleur3.b=0;
	couleur4.r=0; couleur4.g=255; couleur4.b=0;

	//printf("%d %d %d\n",couleur_recuperee.r,couleur_recuperee.g,couleur_recuperee.b );

	if(couleur_recuperee.r== couleur1.r&& couleur_recuperee.g== couleur1.g&& couleur_recuperee.b == couleur1.b)
	{
		//printf("changement voiture 0\n");
		return 4;
	}

	else if(couleur_recuperee.r== couleur2.r&& couleur_recuperee.g== couleur2.g&& couleur_recuperee.b== couleur2.b)
	{
		//printf("changement voiture 1\n");
		return 8;
	}

	else if(couleur_recuperee.r== couleur3.r&& couleur_recuperee.g== couleur3.g&& couleur_recuperee.b== couleur3.b)
	{
		//printf("changement voiture 2\n");
		return 0;
	}

	else if(couleur_recuperee.r== couleur4.r&& couleur_recuperee.g== couleur4.g&& couleur_recuperee.b== couleur4.b)
	{
		//printf("changement voiture 3\n");
		return 12;
	}
	//printf("pas de chagemnt de voiture\n");
	return 20;
}

int collision_deplacement_entite(SDL_Surface *fond_collision,SDL_Rect position_voiture)
{
	SDL_Color couleur_col;
	SDL_Color couleur_recupere1;

	couleur_col.r=255;
	couleur_col.g=255;
	couleur_col.b=255;

	couleur_recupere1=recuperer_couleur(fond_collision,position_voiture);

	if(couleur_col.r==couleur_recupere1.r&&couleur_col.g==couleur_recupere1.g&&couleur_col.b==couleur_recupere1.b)
	{
		//printf("collision\n");
		return 1;
	}
	

	//printf("pas de collision\n");
	return 0;
}