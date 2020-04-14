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
#include <time.h>


void ecrire_nombreFichier(char *nom,int indice)
{
    FILE *fi=NULL;
    fi=fopen(nom,"w");
    fprintf(fi,"%d",indice);
    printf("%d\n",indice );
    fclose(fi);
}

void lire_nombreFichier(char *nom,int *indice)
{
    int i;
    FILE *fi=NULL;
    fi=fopen(nom,"r");
    fscanf(fi,"%d",&i);
    fclose(fi);
    *indice=i;
}

void ajouter_position(char *nom,SDL_Rect position_joueur,SDL_Rect position_camera,int direction,int turbo)
{
    FILE *fi=NULL;
    fi=fopen(nom,"a");
    fprintf(fi,"%d %d %d %d\n",position_joueur.x+position_camera.x,position_joueur.y+position_camera.y,direction,turbo);
    fclose(fi);
}
void lire_position(FILE *fi,char *nom,Entite *boss)
{
    int x,y,i,turbo;
    fscanf(fi,"%d %d %d %d\n",&x,&y,&i,&turbo);
    boss->position.x=x;
    boss->position.y=y;
    boss->indice_voiture=i;
    boss->turbo=turbo;
}
void ouvrir_fichier(FILE **fi,char *nom )
{
    *fi=fopen(nom,"r");
}

void fermer_fichier(FILE **fi,char *nom)
{
    fclose(*fi);
}
void initialiser_boss(Entite *e)
{
    char nom[50];
    int max;

    for (int i = 1; i <= 16; ++i)
    {
        sprintf(nom,"Image/voiture_boss/%d",i);
        strcat(nom,".png");
        e->deplacement[i-1]=IMG_Load(nom);
    }
    for (int i = 1; i <= 16; ++i)
    {
        sprintf(nom,"Image/turbo/voiture_boss_turbo/%d",i);
        strcat(nom,".png");
        e->deplacement_turbo[i-1]=IMG_Load(nom);
    }
    e->indice_voiture=e->direction;
    e->turbo=0;
    e->pv=100;

    lire_nombreFichier("indice.txt",&max);

    max=4;

    srand(time(NULL));
    e->indice=rand()%(max+1);

    printf("boss initialise\n");

}

void afficher_boss(Entite e,SDL_Surface *ecran,SDL_Rect position_camera)
{
    SDL_Rect position;
    position.x=e.position.x- position_camera.x;
    position.y=e.position.y- position_camera.y;

    if(e.turbo==0)
    {
        SDL_BlitSurface(e.deplacement[e.indice_voiture],NULL,ecran,&position);
    }
    else
    {
        SDL_BlitSurface(e.deplacement_turbo[e.indice_voiture],NULL,ecran,&position);
    }

}

void deplacement_boss(Entite *boss,int indice,FILE *fi)
{
    char nomfich[20];
    sprintf(nomfich,"%d.txt",indice);
    lire_position(fi,nomfich,boss);
}

void animation_boss(Entite *boss)
{
    boss->indice_voiture++;

    if(boss->indice_voiture>(boss->direction+3))
    {
        boss->indice_voiture=boss->direction;
    }
}
