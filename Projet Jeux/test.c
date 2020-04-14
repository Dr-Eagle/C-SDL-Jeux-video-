#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <string.h>
#include "Jouer.h"
#include "BgCam.h"
#include "Collision.h"
#include "Enigme.h"
#include "EntiteSecondo.h"
#include "Input.h"
#include "Player.h"
#include "Multiplayer.h"
#include "Menu.h"


int main()
{

    SDL_Surface *ecran=NULL;

    Player p;
    Player m[2];
    m[0].v.couleur=3;
    m[1].v.couleur=4;
    p.stage=3;
    p.v.couleur=5;
    p.score=100000;
    strcpy(p.pseudo,"TOTO");
    strcpy(m[0].pseudo,"TOTO");
    strcpy(m[1].pseudo,"TOTO");

    int continuer = 1,hauteur_ecran=600,largeur_ecran=800,a=0,k=5;
    char *nom_fichier="save.txt";

    SDL_Rect position;

    SDL_Init(SDL_INIT_EVERYTHING);

    TTF_Init();

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
        printf("%s", Mix_GetError());
    }



    if(TTF_Init() == -1)

    {

        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());

        exit(EXIT_FAILURE);

    }

    ecran=SDL_SetVideoMode(largeur_ecran, hauteur_ecran, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);


    jouer(ecran,&k,p);

    //jouer_multi(ecran,m,&k);

    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
