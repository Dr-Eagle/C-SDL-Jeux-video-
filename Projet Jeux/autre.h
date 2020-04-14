#ifndef _AUTRE_H_
#define _AUTRE_H_
#include "Jouer.h"

void message_fin_jeu_multi(Player p[],SDL_Surface *ecran,int *continuer_jeux,int *recommencer);

void afficher_parametre(SDL_Surface *ecran,int *k,int *continuer_jeux,int *continuer_stage,Player *p,temps *t);
void message_fin_jeu(Player *p,SDL_Surface *ecran,int *continuer_jeux,int *continuer_stage);
//void tuto(SDL_Surface *ecran,char *chemin_fichier);
void cine_fin(SDL_Surface *ecran);
#endif
