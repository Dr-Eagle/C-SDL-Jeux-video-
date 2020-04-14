#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "EntiteSecondo.h"
#include "Jouer.h"
#include "Collision.h"


void initialiser_entite(Entite e)
{
	e.voiture=IMG_Load("Image/entite1.png");
	e.position.x=10;
	e.position.y=10;
	e.deplacement[0]=IMG_Load("Image/entite1.png");
	e.deplacement[1]=IMG_Load("Image/entite2.png");
	e.deplacement[2]=IMG_Load("Image/entite2.png");
	e.deplacement[3]=IMG_Load("Image/entite2.png");

	printf("entite secondaire initialisee\n");

}
void initialiser_boss(Entite *e)
{
	e->voiture=IMG_Load("Image/voiture4/1.png");
	e->position.x=5224+150;
	e->position.y=150;
	e->vitesse=1;
	e->direction=0;
	
	/*e->deplacement[0]=IMG_Load("voiture-boss.png");
	e->deplacement[1]=IMG_Load("voiture-boss.png");
	e->deplacement[2]=IMG_Load("voiture-boss.png");
	e->deplacement[3]=IMG_Load("voiture-boss.png");*/

	printf("boss initialise\n");
	
}
void afficher_entite(Entite e[],SDL_Surface *ecran)
{
	SDL_BlitSurface(e[0].voiture,NULL,ecran,&e[0].position);
	SDL_BlitSurface(e[1].voiture,NULL,ecran,&e[1].position);
	printf("entite affichee\n");
}
void afficher_boss(Entite e,SDL_Surface *ecran,SDL_Rect position_camera)
{
	SDL_Rect position;
	position.x=e.position.x-(294/2);
	position.y=e.position.y- (211/2);

	SDL_BlitSurface(e.voiture,NULL,ecran,&position);
	printf("boss affiche\n");
}
void deplacement_entite(Entite *e,SDL_Surface *fond_collision)
{

	e->position.y=(-0.591)*e->position.y+3645;

	e->position.x-=5;

}
void deplacement_boss(Entite boss);
