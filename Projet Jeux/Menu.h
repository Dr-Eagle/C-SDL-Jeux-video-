#ifndef _MENU_H_
#define _MENU_H_
#include "Player.h"
#include "Multiplayer.h"



void choisir_voiture_multi(SDL_Surface *ecran,Mix_Music *musique,Mix_Chunk *son,int *k,Player player[]);
void image_mission(SDL_Surface *ecran,char *chemin_fichier);
void charger_image(SDL_Surface *intro[],SDL_Surface *ecran);
void histoire(SDL_Surface *ecran,SDL_Surface *intro[]);
int verifier_player(char *chemin,char *pseudo);
void ajouter_player(char *chemin,Player j);
void choisir_voiture(SDL_Surface *ecran,Mix_Music *musique,Mix_Chunk *son,int *k,Player *player,char *chemin,SDL_Surface *intro[]);
void saisi(SDL_Event event,char ch[],int *continuer);
void saisi_info(SDL_Surface *ecran,Mix_Music *musique,Mix_Chunk *son,int *k,Player *player,char *chemin);
void new_game(SDL_Surface *ecran,Mix_Music *musique,Mix_Chunk *son,int *k,Player *player,char *chemin,SDL_Surface *intro[]);
void jouer_son(Mix_Music *musique,Mix_Chunk *son,int k);
void intr(SDL_Surface *ecran);
void load(SDL_Surface *ecran,Mix_Music *musique,Mix_Chunk *son,int *k,Player *player);
void multiplayers(SDL_Surface *ecran,Mix_Music *musique,Mix_Chunk *son,int k);
void setting(SDL_Surface *ecran,Mix_Music *musique,Mix_Chunk *son,int *k);
void exit_game(SDL_Surface *ecran,Mix_Music *musique,Mix_Chunk *son,int *k,int *continuer);

#endif
