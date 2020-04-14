#ifndef _JOUER_H_
#define _JOUER_H_
#include "Jouer.h"
#include "BgCam.h"
#include "Collision.h"
#include "Enigme.h"
#include "EntiteSecondo.h"
#include "Input.h"
#include "Player.h"
#include "Menu.h"


typedef struct Update
{
	Background bg;
	Camera cam;
	collision col;
	Enigme enig;
	Entite enti[2];
	Entite boss;
	input inp;
	Player p;

}Update;

void initialiser(Update *update);
void mise_jour(Update *update,int tab[],int *Collision,SDL_Event touch,SDL_Surface *ecran,int *indice,int *continuer_stage,int *continuer_jeux,temps *t,int *k,int dt);
void display(SDL_Surface *ecran,Update *update,int *jouer,int indice_enigme,temps *t,int *continuer_jeux,int *continuer_stage);
void liberer(Update *Update);
void jouer(SDL_Surface *ecran,int *k,Player p);

#endif
