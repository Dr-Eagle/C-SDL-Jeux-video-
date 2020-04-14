#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "Menu.h"


int main()
{
    SDL_Surface *ecran=NULL;
    Player j;


    int continuer = 1;
    int n=0,i,a,suit=1,b=0,pos[4]= {0},k=5,u=1,r=1;
    char chemin[]="profils.txt";
   

    SDL_Surface  *imagedefond=NULL,*option[5]= {NULL},*aiguille[5]= {NULL},*texte=NULL, *intro[433]={NULL};
    SDL_Rect positionFond,position_aiguille[5],positiontexte,positionfond1,position_option[5];
    charger_image(intro);

    positionfond1.x = 0;
    positionfond1.y = 0;

    positionFond.x = 0;
    positionFond.y = 0;

    position_aiguille[0].x=24;
    position_aiguille[0].y=325;

    position_aiguille[1].x=24;
    position_aiguille[1].y=380;

    position_aiguille[2].x=24;
    position_aiguille[2].y=400;

    position_aiguille[3].x=24;
    position_aiguille[3].y=453;

    position_aiguille[4].x=22;
    position_aiguille[4].y=430;

    position_option[0].x=251;
    position_option[0].y=279;

    position_option[1].x=294;
    position_option[1].y=341;

    position_option[2].x=321;
    position_option[2].y=403;

    position_option[3].x=342;
    position_option[3].y=465;

    position_option[4].x=326;
    position_option[4].y=527;





    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
        printf("%s", Mix_GetError());
    }
    Mix_Music *musique; //Création du pointeur de type Mix_Music
    Mix_Chunk *son;//Créer un pointeur pour stocker un .WAV
	musique = Mix_LoadMUS("Son/menu.mp3"); //Chargement de la musique
    son = Mix_LoadWAV("Son/VOV.wav"); //Charger un wav dans un pointeur
    


    ecran=SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetIcon(SDL_LoadBMP("Image/logo-jeux.bmp"), NULL);
    SDL_WM_SetCaption("Eagle Race",NULL);
    imagedefond = IMG_Load("Image/menu-final.png");

    //intr(ecran);

    jouer_son(musique,son,k);

    SDL_BlitSurface(imagedefond, NULL, ecran, &positionFond);
    option[0] = IMG_Load("Image/bouton_new.png");
    option[1] = IMG_Load("Image/bouton-load.png");
    option[2] = IMG_Load("Image/bouton-multiplayer.png");
    option[3] = IMG_Load("Image/bouton-setting.png");
    option[4] = IMG_Load("Image/bouton-exit.png");
    for(i=0; i<5; i++)
    {
        SDL_BlitSurface(option[i], NULL, ecran, &position_option[i]);
    }

    aiguille[0]= IMG_Load("Image/aiguille-new.png");
    aiguille[1]= IMG_Load("Image/aiguille-load.png");
    aiguille[2]= IMG_Load("Image/aiguille-multiplayer.png");
    aiguille[3]= IMG_Load("Image/aiguille-setting.png");
    aiguille[4]= IMG_Load("Image/aiguille-exit.png");

    SDL_EnableKeyRepeat(200, 200);
    SDL_BlitSurface(aiguille[0], NULL, ecran, &position_aiguille[0]);
    SDL_Flip(ecran);

    SDL_Event event;
    while (continuer)
    {

        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_UP:
                n--;
                break;
            case SDLK_DOWN:
                n++;
                break;
            case SDLK_RETURN:
                if(n==4)
                    exit_game(ecran,musique,son,&k,&continuer);
                else if(n==3)
                    setting(ecran,musique,son,&k);

                else if(n==2)
                {
                    multiplayers(ecran,musique,son,k);
                    jouer_son(musique,son,k);
                }
                else if(n==1)
                {
                    saisi_info(ecran,musique,son,&k,&j,chemin);
                    jouer_son(musique,son,k);
                    
                }
                else if(n==0)
                {
                	new_game(ecran,musique,son,&k,&j,chemin,intro);
                    jouer_son(musique,son,k);
                }
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button==SDL_BUTTON_LEFT)
            {
                if(event.button.x>position_option[0].x && event.button.x<position_option[0].x+422 && event.button.y>position_option[0].y && event.button.y<position_option[0].y+55)
                    {
                        new_game(ecran,musique,son,&k,&j,chemin,intro);
                        jouer_son(musique,son,k);
                    }
                else if(event.button.x>position_option[1].x && event.button.x<position_option[1].x+388 && event.button.y>position_option[1].y && event.button.y<position_option[1].y+56)
                {
                    saisi_info(ecran,musique,son,&k,&j,chemin);
                    jouer_son(musique,son,k);
                }
                else if(event.button.x>position_option[2].x && event.button.x<position_option[2].x+363 && event.button.y>position_option[2].y && event.button.y<position_option[2].y+57)
                    {
                        multiplayers(ecran,musique,son,k);
                        jouer_son(musique,son,k);
                    }

                else if(event.button.x>position_option[3].x && event.button.x<position_option[3].x+319 && event.button.y>position_option[3].y && event.button.y<position_option[3].y+56)
                {
                    setting(ecran,musique,son,&k);
                }
                else if(event.button.x>position_option[4].x && event.button.x<position_option[4].x+304 && event.button.y>position_option[4].y && event.button.y<position_option[4].y+55)
                	{exit_game(ecran,musique,son,&k,&continuer);}

            }
            break;

        case SDL_MOUSEMOTION:

            if(event.motion.x>position_option[0].x && event.motion.x<position_option[0].x+422 && event.motion.y>position_option[0].y && event.motion.y<position_option[0].y+55)
                n=0;
            else if(event.motion.x>position_option[1].x && event.motion.x<position_option[1].x+388 && event.motion.y>position_option[1].y && event.motion.y<position_option[1].y+56)
                n=1;
            else if(event.motion.x>position_option[2].x && event.motion.x<position_option[2].x+363 && event.motion.y>position_option[2].y && event.motion.y<position_option[2].y+57)
                n=2;
            else if(event.motion.x>position_option[3].x && event.motion.x<position_option[3].x+319 && event.motion.y>position_option[3].y && event.motion.y<position_option[3].y+56)
                n=3;
            else if(event.motion.x>position_option[4].x && event.button.x<position_option[4].x+304 && event.motion.y>position_option[4].y && event.motion.y<position_option[4].y+55)
                n=4;

            break;
        }

        if(a!=n)
        {
            Mix_PlayChannel(1, son, 0);//Joue
            a=n;
        }

        if (n>4)
            n=0;
        if(n<0)
            n=4;

        if(continuer!=0)
        {
	        SDL_BlitSurface(imagedefond, NULL, ecran, &positionFond);
	        SDL_BlitSurface(aiguille[n], NULL, ecran, &position_aiguille[n]);
	        SDL_BlitSurface(option[n],NULL,ecran,&position_option[n]);

	        for (i = 0; i < 5; ++i)
	        {
	            SDL_BlitSurface(option[i], NULL, ecran, &position_option[i]);
	        }

	        Mix_VolumeChunk(son, MIX_MAX_VOLUME/(10/k)); //Mettre un volume pour ce wav
	        Mix_VolumeMusic(MIX_MAX_VOLUME /(10/k));
        }
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(imagedefond);
    for(i=0; i<5; i++)
    {
        SDL_FreeSurface(option[i]);
        SDL_FreeSurface(aiguille[i]);
    }
    
    for (int i = 0; i < 433; ++i)
    {
        SDL_FreeSurface(intro[i]);
    }


    Mix_FreeChunk(son);//Libération du son 1
    Mix_FreeMusic(musique); //Libération de la musique

    Mix_CloseAudio();
    
    
	TTF_Quit();
    SDL_Quit();
    return 0;
}
