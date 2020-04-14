#ifndef _MULTIPLAYER_H_
#define _MULTIPLAYER_H_
#include "Menu.h"
#include "BgCam.h"
#include "Collision.h"
#include "Enigme.h"
#include "EntiteSecondo.h"
#include "Input.h"
#include "Player.h"
#include "autre.h"

typedef struct Multi
{
	Background bg[2];
	Camera cam[2];
	collision col;
	input inp;
	Player p[2];

}Multi;

void ini_multi(Multi *multi);
void miser_jour_multi(Multi *multi,int tab[],int *continuer_jeux,int *recommencer);
void display_multi(SDL_Surface *ecran,Multi *multi,int *continuer_jeux,int *recommencer);
void liberer_multi(Multi *multi);
void jouer_multi(SDL_Surface *ecran,Player p[],int *k);


#endif