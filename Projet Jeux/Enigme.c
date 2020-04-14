#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include <string.h>
#include "Enigme.h"
#include "Arduino.h"
int s[4];
FILE *f;


void initialiser_enigmes(Enigme *e)
{
    char nom[40];
    int i;

    for (int i = 0; i < 18; ++i)
    {
        sprintf(nom,"Image/enigme/question %d",i);
        strcat(nom,".png");
        e->enigme[i]=IMG_Load(nom);
    }

    e->position.x=0;
    e->position.y=0;

    e->reponses[0]=1;
    e->reponses[1]=2;
    e->reponses[2]=2;
    e->reponses[3]=3;
    e->reponses[4]=1;
    e->reponses[5]=3;
    e->reponses[6]=1;
    e->reponses[7]=3;
    e->reponses[8]=2;
    e->reponses[9]=3;
    e->reponses[10]=1;
    e->reponses[11]=1;
    e->reponses[12]=1;
    e->reponses[13]=3;
    e->reponses[14]=2;
    e->reponses[15]=3;
    e->reponses[16]=1;
    e->reponses[17]=2;

    e->choix=0;


    printf("enigme initialise\n");
}

int generation_enigme()
{
    srand(time(NULL));
    int indice_enigme;
    indice_enigme=rand()%(17+1);

    printf("enigme generee %d\n",indice_enigme);

    return indice_enigme;
}

void afficher_enigme(Enigme e,SDL_Rect position,SDL_Surface *ecran,int indice_enigme)
{
    SDL_BlitSurface(e.enigme[indice_enigme],NULL,ecran,&e.position);
    printf("enigme affichee\n");
}

void saisir_reponse(SDL_Event touch,int *choix_user)
{
    if(f!=NULL)
    {
        arduinoReadDataEnigme(s);
        if (s[1]==1)
        {
            *choix_user= 1;
        }
        if (s[2]==1)
        {
            *choix_user=2;
        }
        if(s[3]==1)
        {
            *choix_user=3;
        }

    }

    switch(touch.type)
    {
    case SDL_KEYDOWN:
        switch(touch.key.keysym.sym)
        {
        case SDLK_KP1:
            *choix_user= 1;
            break;

        case SDLK_KP2:
            *choix_user=2;
            break;

        case SDLK_KP3:
            *choix_user=3;
            break;

        case SDLK_BACKSPACE:
            *choix_user=-1;
            break;

            //printf("saisie\n");

        }
        break;
    }

}

void afficher_reponse_saisie(SDL_Surface *ecran,int choix_user)
{
    char choix[10],vide[]="";
    SDL_Surface *texte=NULL;
    SDL_Rect position;
    sprintf(choix,"%d",choix_user);
    position.x=593;
    position.y=455;

    TTF_Font *police=NULL;
    police=TTF_OpenFont("Police/arial.ttf",20);
    SDL_Color couleur = {0,0,0};
    if(choix_user==-1)
    {
        texte=TTF_RenderText_Blended(police,vide,couleur);
    }
    else
    {
        texte=TTF_RenderText_Blended(police,choix,couleur);
    }


    SDL_BlitSurface(texte,NULL,ecran,&position);

    //printf("reponse affichee\n");
}

int verifier_enigme(Enigme e,int choix_user,int indice_enigme)
{

    if(choix_user==e.reponses[indice_enigme])
    {

        printf(" reponse vraie\n");
        return 1;
    }

    printf("reponse fausse\n");
    return 0;
}

void modifier_score(Enigme e,int *score,int choix_user,int indice_enigme)
{
    if(verifier_enigme(e,choix_user,indice_enigme))
    {
        *score+=250;
        printf("score augmente\n");
    }
    else
    {
        if(*score<100)
            (*score)=0;
        else
            (*score)-=100;
        printf("score diminue\n");
    }
}





















































