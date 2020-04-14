#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <time.h>
#include "autre.h"
#include "Menu.h"
#include "Jouer.h"
#include "Arduino.h"

FILE *f;
int au[3],auprev=1,aupar[3],auparprev=1;

void afficher_parametre(SDL_Surface *ecran,int *k,int *continuer_jeux,int *continuer_stage,Player *p,temps *t)
{
    int continuer=1,choix=0,i;


    SDL_Surface *option_parametre[6]= {NULL};
    SDL_Rect position_para[6];


    position_para[0].x=162;
    position_para[0].y=180;
    position_para[1].x=162;
    position_para[1].y=256;
    position_para[2].x=162;
    position_para[2].y=332;
    position_para[3].x=162;
    position_para[3].y=410;
    position_para[4].x=162;
    position_para[4].y=485;
    position_para[5].x=0;
    position_para[5].y=0;
    Getf(f);
    /*position_para[0].x=218;
    position_para[0].y=422;
    position_para[0].x=541;
    position_para[0].y=422;*/

    option_parametre[0]=IMG_Load("Image/parametre/menu.png");
    option_parametre[1]=IMG_Load("Image/parametre/resume.png");
    option_parametre[2]=IMG_Load("Image/parametre/new.png");
    option_parametre[3]=IMG_Load("Image/parametre/sound.png");
    option_parametre[4]=IMG_Load("Image/parametre/exit.png");
    option_parametre[5]=IMG_Load("Image/parametre/setting.png");

    SDL_BlitSurface(option_parametre[5],NULL,ecran,&position_para[5]);
    SDL_BlitSurface(option_parametre[choix],NULL,ecran,&position_para[choix]);
    SDL_Flip(ecran);
    SDL_Event touch;
    while(continuer)
    {
        arduinoReadDataAutre(aupar);

        if(f!=NULL)
        {
            if(au[0]==0 && auprev!=0)
            {

                choix--;
            }
            if(aupar[0]==2 && auparprev!=2)
            {
                choix++;
            }
            if(aupar[1]==1)
            {
                if(choix==3)
                {
                    if(aupar[0]==0 && auparprev!=0)
                    {

                        (*k)--;
                    }
                    if(au[0]==2 && auparprev!=2)
                    {
                        (*k)++;
                    }
                }

                else if(choix==0)
                {
                    sauvegarder("profils.txt",*p);
                }
                else if(choix==1)
                {
                    continuer=0;
                }
                else if(choix==2)
                {
                    *continuer_jeux=0;
                }
                else if(choix==4)
                {
                    continuer=0;
                    *continuer_jeux=0;
                    *continuer_stage=0;
                }
            }
        }

        if(f==NULL)
        {
            SDL_WaitEvent(&touch);
        }
        switch(touch.type)
        {
        case SDL_QUIT:
            continuer=0;
            break;
        case SDL_KEYDOWN:
            switch(touch.key.keysym.sym)
            {
            case SDLK_RETURN:
                switch(choix)
                {

                case 0:
                    sauvegarder("profils.txt",*p);
                    break;
                case 1:
                    continuer=0;
                    break;
                case 2:
                    *continuer_jeux=0;
                    break;
                case 4:
                    continuer=0;
                    *continuer_jeux=0;
                    *continuer_stage=0;
                    break;

                }
                continuer=0;
                break;
            case SDLK_UP:
                choix--;
                break;

            case SDLK_DOWN:
                choix++;
                break;

                if(choix==3)
                {
                case SDLK_LEFT:
                    (*k)--;
                    break;
                case SDLK_RIGHT:
                    (*k)++;
                    break;
                }


                break;
            }
        }

        if(choix>4)
            choix=0;
        else if(choix<0)
            choix=4;

        if((*k)>10)
            (*k)=10;
        else if((*k)<1)
            (*k)=1;

        SDL_BlitSurface(option_parametre[5],NULL,ecran,&position_para[5]);
        SDL_BlitSurface(option_parametre[choix],NULL,ecran,&position_para[choix]);
        SDL_Flip(ecran);

    }

    for (int i = 0; i < 6; ++i)
    {
        SDL_FreeSurface(option_parametre[i]);
    }

}

void message_fin_jeu(Player *p,SDL_Surface *ecran,int *continuer_jeux,int *continuer_stage)
{

    int continuer=1,choix=0,i;
    SDL_Surface *message=NULL,*option_winnner[3]= {NULL},*option_loser[2]= {NULL};
    SDL_Rect position_message,position_winner[3],position_loser[2];
    SDL_Event touch;
    position_message.x=0;
    position_message.y=0;

    position_winner[0].x=262;
    position_winner[0].y=361;
    position_winner[1].x=382;
    position_winner[1].y=361;
    position_winner[2].x=501;
    position_winner[2].y=361;

    position_loser[0].x=358;
    position_loser[0].y=361;
    position_loser[1].x=427;
    position_loser[1].y=361;
    Getf(f);

    if(p->gagner==1&&p->stage==4)
    {
        cine_fin(ecran);
        *continuer_jeux=0;
        *continuer_stage=0;
    }
    
    if(p->gagner==1&&p->stage!=4)
    {
        message=IMG_Load("Image/parametre/win.png");

        option_winnner[0]=IMG_Load("Image/parametre/reload.png");
        option_winnner[1]=IMG_Load("Image/parametre/home.png");
        option_winnner[2]=IMG_Load("Image/parametre/next.png");


        SDL_BlitSurface(message,NULL,ecran,&position_message);
        SDL_Flip(ecran);

        while(continuer)
        {
            arduinoReadDataAutre(au);

            if(f!=NULL)
            {
                if(au[0]==0 && auprev!=0)
                {

                    choix--;
                }
                if(au[0]==2 && auprev!=2)
                {
                    choix++;
                }
                if(au[1]==1)
                {
                    continuer=0;
                    if(choix==0)
                    {
                        *continuer_jeux=0;
                    }
                    else if(choix==1)
                    {
                        *continuer_jeux=0;
                        *continuer_stage=0;
                    }
                    else if(choix==2)
                    {
                        *continuer_jeux=0;
                        p->stage++;
                    }
                    continuer=0;
                }

            }
            if(f==NULL)
            {
                SDL_WaitEvent(&touch);
            }
            switch(touch.type)
            {
            case SDL_KEYDOWN:
                switch(touch.key.keysym.sym)
                {
                case SDLK_RETURN:
                    continuer=0;
                    if(choix==0)
                    {
                        *continuer_jeux=0;
                    }
                    else if(choix==1)
                    {
                        *continuer_jeux=0;
                        *continuer_stage=0;
                    }
                    else if(choix==2)
                    {
                        *continuer_jeux=0;
                        p->stage++;
                    }
                    continuer=0;
                    break;
                case SDLK_LEFT:
                    choix--;
                    break;
                case SDLK_RIGHT:
                    choix++;
                    break;
                }
                break;
            }

            if(choix>2)
                choix=0;
            if(choix<0)
                choix=2;

            SDL_BlitSurface(message,NULL,ecran,&position_message);
            SDL_BlitSurface(option_winnner[choix],NULL,ecran,&position_winner[choix]);

            SDL_Flip(ecran);

        }

        for (int i = 0; i < 3; ++i)
        {
            SDL_FreeSurface(option_winnner[i]);
        }
    }
    else if(p->game_over==1)
    {
        message=IMG_Load("Image/parametre/over.png");

        option_loser[0]=IMG_Load("Image/parametre/reload.png");
        option_loser[1]=IMG_Load("Image/parametre/home.png");



        SDL_BlitSurface(message,NULL,ecran,&position_message);
        SDL_Flip(ecran);
        printf("%d continuer\n",continuer );
        while(continuer)
        {
            arduinoReadDataAutre(au);
            if(f!=NULL)
            {
                if(au[0]==0 && auprev!=0)
                {

                    choix--;
                }
                if(au[0]==2 && auprev!=2)
                {
                    choix++;
                }
                if(au[1]==1)
                {
                    continuer=0;
                    if(choix==0)
                    {
                        *continuer_jeux=0;
                    }
                    else if(choix==1)
                    {
                        *continuer_jeux=0;
                        *continuer_stage=0;
                    }
                    continuer=0;
                }
            }
            if(f==NULL)
            {
                SDL_WaitEvent(&touch);
            }
            switch(touch.type)
            {
            case SDL_KEYDOWN:
                switch(touch.key.keysym.sym)
                {
                case SDLK_RETURN:
                    continuer=0;
                    if(choix==0)
                    {
                        *continuer_jeux=0;

                    }
                    else if(choix==1)
                    {
                        *continuer_jeux=0;
                        *continuer_stage=0;
                    }
                    continuer=0;
                    break;
                case SDLK_LEFT:
                    choix--;
                    break;
                case SDLK_RIGHT:
                    choix++;
                    break;
                }
                break;
            }

            if(choix>1)
                choix=0;
            if(choix<0)
                choix=1;

            SDL_BlitSurface(message,NULL,ecran,&position_message);
            SDL_BlitSurface(option_loser[choix],NULL,ecran,&position_loser[choix]);

            SDL_Flip(ecran);
        }

        for (int i = 0; i < 2; ++i)
        {
            SDL_FreeSurface(option_loser[i]);
        }

    }
    

    SDL_FreeSurface(message);
}


void message_fin_jeu_multi(Player p[],SDL_Surface *ecran,int *continuer_jeux,int *recommencer)
{
    int continuer=1,choix=0,i;
    SDL_Surface *message=NULL,*option_winnner[2]= {NULL},*option_loser[2];
    SDL_Rect position_message,position_winner[3],position_loser[2];
    SDL_Event touch;
    position_message.x=0;
    position_message.y=0;

    position_winner[0].x=346;
    position_winner[0].y=357;
    position_winner[1].x=422;
    position_winner[1].y=358;

    position_loser[0].x=358;
    position_loser[0].y=360;
    position_loser[1].x=427;
    position_loser[1].y=360;


    option_winnner[0]=IMG_Load("Image/multiplayer/reload.png");
    option_winnner[1]=IMG_Load("Image/multiplayer/home.png");

    if(p[0].gagner==1)
    {
        message=IMG_Load("Image/multiplayer/player-1.png");
    }
    else if(p[1].gagner==1||p[0].game_over==1)
    {
        message=IMG_Load("Image/multiplayer/player-2.png");
    }


    if(p[0].gagner==1||p[1].gagner==1)
    {
        SDL_BlitSurface(message,NULL,ecran,&position_message);
        SDL_Flip(ecran);

        while(continuer)
        {
            arduinoReadDataAutre(au);

            if(f!=NULL)
            {
                if(au[0]==0 && auprev!=0)
                {
                    choix--;
                }
                if(au[0]==2 && auprev!=2)
                {
                    choix++;
                }
                if(au[1]==1)
                {
                    continuer=0;
                    if(choix==0)
                    {
                        *continuer_jeux=0;
                    }
                    else if(choix==1)
                    {
                        *continuer_jeux=0;
                        *recommencer=0;
                    }

                    continuer=0;
                }

            }
            if(f==NULL)
            {
                SDL_WaitEvent(&touch);
            }
            switch(touch.type)
            {
            case SDL_KEYDOWN:
                switch(touch.key.keysym.sym)
                {
                case SDLK_RETURN:
                    continuer=0;
                    if(choix==0)
                    {
                        *continuer_jeux=0;
                    }
                    else if(choix==1)
                    {
                        *continuer_jeux=0;
                        *recommencer=0;
                    }

                    continuer=0;
                    break;
                case SDLK_LEFT:
                    choix--;
                    break;
                case SDLK_RIGHT:
                    choix++;
                    break;
                case SDLK_q:
                    choix--;
                    break;

                case SDLK_d:
                    choix++;
                    break;
                }
                break;
            }

            if(choix>1)
                choix=0;
            if(choix<0)
                choix=1;

            SDL_BlitSurface(message,NULL,ecran,&position_message);
            SDL_BlitSurface(option_winnner[choix],NULL,ecran,&position_winner[choix]);

            SDL_Flip(ecran);

        }

        for (int i = 0; i < 2; ++i)
        {
            SDL_FreeSurface(option_winnner[i]);
        }



        SDL_FreeSurface(message);
    }
    if(p[0].game_over==1||p[1].game_over==1)
    {
        message=IMG_Load("Image/parametre/over.png");

        option_loser[0]=IMG_Load("Image/parametre/reload.png");
        option_loser[1]=IMG_Load("Image/parametre/home.png");



        SDL_BlitSurface(message,NULL,ecran,&position_message);
        SDL_Flip(ecran);
        while(continuer)
        {
            arduinoReadDataAutre(au);

            if(f!=NULL)
            {
                if(au[0]==0 && auprev!=0)
                {

                    choix--;
                }
                if(au[0]==2 && auprev!=2)
                {
                    choix++;
                }
                if(au[1]==1)
                {
                    continuer=0;
                    if(choix==0)
                    {
                        *continuer_jeux=0;

                    }
                    else if(choix==1)
                    {
                        *continuer_jeux=0;
                        *recommencer=0;
                    }
                    continuer=0;
                }
            }

            if(f!=NULL)
            {
                SDL_PollEvent(&touch);
            }
            else
            {
                SDL_WaitEvent(&touch);
            }
            switch(touch.type)
            {
            case SDL_KEYDOWN:
                switch(touch.key.keysym.sym)
                {
                case SDLK_RETURN:
                    continuer=0;
                    if(choix==0)
                    {
                        *continuer_jeux=0;

                    }
                    else if(choix==1)
                    {
                        *continuer_jeux=0;
                        *recommencer=0;
                    }
                    continuer=0;
                    break;
                case SDLK_LEFT:
                    choix--;
                    break;
                case SDLK_RIGHT:
                    choix++;
                    break;
                }
                break;
            }

            if(choix>1)
                choix=0;
            if(choix<0)
                choix=1;

            SDL_BlitSurface(message,NULL,ecran,&position_message);
            SDL_BlitSurface(option_loser[choix],NULL,ecran,&position_loser[choix]);

            SDL_Flip(ecran);
        }

        for (int i = 0; i < 2; ++i)
        {
            SDL_FreeSurface(option_loser[i]);
        }



        SDL_FreeSurface(message);
    }

}

/*void tuto(SDL_Surface *ecran,char *chemin_fichier)
{
    int continuer=1;
    SDL_Surface *image=NULL;
    SDL_Rect position;
    position.x=0;
    position.y=0;
    image=IMG_Load(chemin_fichier);

    SDL_BlitSurface(image,NULL,ecran,&position);

    SDL_Flip(ecran);

    SDL_Event press;
    while(continuer)
    {
        SDL_WaitEvent(&press);
        switch(press.type)
        {
        case SDL_KEYDOWN:
            switch(press.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                continuer=0;
                break;
            }
            break;
        }
        if(continuer!=0)
        SDL_BlitSurface(image,NULL,ecran,&position);

        SDL_Flip(ecran);
    }

    SDL_FreeSurface(image);
}
*/

void cine_fin(SDL_Surface *ecran)
{
    char nom[100];
    SDL_Rect position;
    position.x=0;
    position.y=0;
    int continuer = 1,i;
    SDL_Event event;
    Getf(f);
    SDL_Surface *load[5]= {NULL},*fin[534]= {NULL};

    for (int i = 0; i < 5; ++i)
    {
        sprintf(nom,"Image/%d.png",i+1);
        load[i]=IMG_Load(nom);
    }
    SDL_BlitSurface(load[0],NULL,ecran,&position);
    SDL_Flip(ecran);
    SDL_Delay(1500);

    SDL_BlitSurface(load[1],NULL,ecran,&position);
    SDL_Flip(ecran);
    SDL_Delay(1700);
    for (int i = 0; i < 534; ++i)
    {
        if(i==1)
        {
            SDL_BlitSurface(load[2],NULL,ecran,&position);
            SDL_Flip(ecran);
        }
        if(i==416)
        {
            SDL_BlitSurface(load[3],NULL,ecran,&position);
            SDL_Flip(ecran);
        }
        sprintf(nom,"Video/fin/Composition 1_%d",i);
        strcat(nom,".png");

        fin[i]=IMG_Load(nom);
    }
    SDL_BlitSurface(load[4],NULL,ecran,&position);
    SDL_Flip(ecran);

    for (int i = 0; i < 5; ++i)
    {
        SDL_FreeSurface(load[i]);
    }

    Mix_Chunk *fin_mus; //Création du pointeur de type Mix_Music
    fin_mus=Mix_LoadWAV("Son/son_fin.wav");
    Mix_AllocateChannels(32); //Allouer 32 canaux
    Mix_Volume(1, MIX_MAX_VOLUME/2); //Mettre à mi-volume le post 1
    Mix_VolumeChunk(fin_mus, MIX_MAX_VOLUME/2);

    Mix_PlayChannel(1, fin_mus, 0); //Jouer infiniment la musique
    for (int i = 0; i < 534; ++i)
    {
        SDL_BlitSurface(fin[i],NULL,ecran,&position);
        SDL_Flip(ecran);

        SDL_PollEvent(&event);
        if(event.key.keysym.sym==SDLK_RETURN)
        {
            break;
        }
        SDL_Delay(20);
    }

    for (int i = 0; i < 534; ++i)
    {
        SDL_FreeSurface(fin[i]);
    }
    Mix_FreeChunk(fin_mus);

}
