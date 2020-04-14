#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "Input.h"
#include "Arduino.h"

FILE *f;
int m[3],multi[3];

void initialiser_input(input *touch)
{
    int i;

    for (int i = 0; i < 6; ++i)
    {
        touch->tab_clavier[i]=0;
    }
    printf("input initialise\n");
}

void recuperer_touch_multi(input *touch,SDL_Event press)
{
    Getf(f);

    switch(press.type)
    {
    case SDL_KEYDOWN:
        switch(press.key.keysym.sym)
        {
        case SDLK_LEFT:
            touch->tab_clavier[0]=1;
            break;

        case SDLK_RIGHT:
            touch->tab_clavier[1]=1;
            break;

        case SDLK_UP:
            touch->tab_clavier[2]=1;
            break;

        case SDLK_DOWN:
            touch->tab_clavier[3]=1;
            break;

        case SDLK_KP0:
            touch->tab_clavier[4]=1;
            break;
        case SDLK_ESCAPE:
            touch->tab_clavier[5]=1;
            break;
        case SDLK_q:
            touch->tab_clavier[6]=1;
            break;
        case SDLK_d:
            touch->tab_clavier[7]=1;
            break;
        case SDLK_z:
            touch->tab_clavier[8]=1;
            break;
        case SDLK_s:
            touch->tab_clavier[9]=1;
            break;
        case SDLK_SPACE:
            touch->tab_clavier[10]=1;
            break;

        }
        break;

    case SDL_KEYUP:
        switch(press.key.keysym.sym)
        {
        case SDLK_LEFT:
            touch->tab_clavier[0]=0;
            break;

        case SDLK_RIGHT:
            touch->tab_clavier[1]=0;
            break;

        case SDLK_UP:
            touch->tab_clavier[2]=0;
            break;

        case SDLK_DOWN:
            touch->tab_clavier[3]=0;
            break;

        case SDLK_KP0:
            touch->tab_clavier[4]=0;
            break;
        case SDLK_ESCAPE:
            touch->tab_clavier[5]=0;
            break;
        case SDLK_q:
            touch->tab_clavier[6]=0;
            break;
        case SDLK_d:
            touch->tab_clavier[7]=0;
            break;
        case SDLK_z:
            touch->tab_clavier[8]=0;
            break;
        case SDLK_s:
            touch->tab_clavier[9]=0;
            break;
        case SDLK_SPACE:
            touch->tab_clavier[10]=0;
            break;

        }
        break;

    }
    if(f!=NULL)
    {
        arduinoReadDataInput(multi);

        if (multi[0]==0)
        {
            touch->tab_clavier[0]=1;
        }

        if (multi[0]==2)
        {
            touch->tab_clavier[1]=1;
        }
        if(multi[0]==1)
        {
            touch->tab_clavier[0]=0;
            touch->tab_clavier[1]=0;
        }
        if(multi[1]==1)
        {
            touch->tab_clavier[3]=1;
        }
        else touch->tab_clavier[3]=0;

        if(multi[2]==1)
        {
            touch->tab_clavier[4]=1;
        }
        else touch->tab_clavier[4]=0;

        if(multi[3]==1)
        {
            touch->tab_clavier[2]=1;
        }
        else touch->tab_clavier[2]=0;
    }
    //printf("recuperee\n");
}

void initialiser_input_multi(input *touch)
{
    int i;
    for (int i = 0; i < 11; ++i)
    {
        touch->tab_clavier[i]=0;
    }
    printf("input multi initialise\n");
}

void recuperer_touch(input *touch,SDL_Event press)
{
    Getf(f);

    switch(press.type)
    {
    case SDL_KEYDOWN:
        switch(press.key.keysym.sym)
        {
        case SDLK_LEFT:
            touch->tab_claviersolo[0]=1;
            break;

        case SDLK_RIGHT:
            touch->tab_claviersolo[1]=1;
            break;

        case SDLK_UP:
            touch->tab_claviersolo[2]=1;
            break;

        case SDLK_DOWN:
            touch->tab_claviersolo[3]=1;
            break;

        case SDLK_LSHIFT:
            touch->tab_claviersolo[4]=1;
            break;
        case SDLK_ESCAPE:
            touch->tab_claviersolo[5]=1;
            break;

        }
        break;

    case SDL_KEYUP:
        switch(press.key.keysym.sym)
        {
        case SDLK_LEFT:
            touch->tab_claviersolo[0]=0;
            break;

        case SDLK_RIGHT:
            touch->tab_claviersolo[1]=0;
            break;

        case SDLK_UP:
            touch->tab_claviersolo[2]=0;
            break;

        case SDLK_DOWN:
            touch->tab_claviersolo[3]=0;
            break;

        case SDLK_LSHIFT:
            touch->tab_claviersolo[4]=0;
            break;
        case SDLK_ESCAPE:
            touch->tab_claviersolo[5]=0;
            break;

        }
        break;
    }
    if(f!=NULL)
    {
        arduinoReadDataInput(m);

        if (m[0]==0)
        {
            touch->tab_claviersolo[0]=1;
        }

        if (m[0]==2)
        {
            touch->tab_claviersolo[1]=1;
        }
        if(m[0]==1)
        {
            touch->tab_claviersolo[0]=0;
            touch->tab_claviersolo[1]=0;
        }
        if(m[1]==1)
        {
            touch->tab_claviersolo[3]=1;
        }
        else touch->tab_claviersolo[3]=0;

        if(m[2]==1)
        {
            touch->tab_claviersolo[4]=1;
        }
        else touch->tab_claviersolo[4]=0;

        if(m[3]==1)
        {
            touch->tab_claviersolo[2]=1;
        }
        else touch->tab_claviersolo[2]=0;
    }
    //printf("recuperee\n");*/
}
