#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "Menu.h"
#include "Jouer.h"
#include "Arduino.h"


int s[3],sprev=1,sprev2=1,setbprev=1,l[3],lprev=1,new[3],newprev=1,multi[3],multiprev=1,multiprevb=1,Sa[3],ex[3],exprev=1,exprevb=1,set[3],setprev=1,cm[3],cmprev=1,cmprevb=1;
FILE *f;

void jouer_son(Mix_Music *musique,Mix_Chunk *son,int k)
{

    Mix_AllocateChannels(32); //Allouer 32 canaux
    Mix_Volume(1, MIX_MAX_VOLUME/2); //Mettre à mi-volume le post 1
    Mix_PlayMusic(musique, -1); //Jouer infiniment la musique
    Mix_VolumeMusic(MIX_MAX_VOLUME /(10/(k)));
    Mix_VolumeChunk(son, MIX_MAX_VOLUME/(10/(k))); //Mettre un volume pour ce wav


}
void image_mission(SDL_Surface *ecran,char *chemin_fichier)
{
    int continuer=1;
    SDL_Surface *image=NULL;
    SDL_Rect position;
    position.x=0;
    position.y=0;
    Getf(f);
    image=IMG_Load(chemin_fichier);

    SDL_BlitSurface(image,NULL,ecran,&position);

    SDL_Flip(ecran);

    SDL_Event press;
    while(continuer)
    {
        sprev2=s[2];
        arduinoReadDataMenu(s);
        if(f!=NULL)
        {
            if(s[2]==1 && sprev2!=1)
            {
                continuer=0;
            }
        }

        if(f==NULL)
        {
            SDL_WaitEvent(&press);
        }
        switch(press.type)
        {
        case SDL_KEYDOWN:
            switch(press.key.keysym.sym)
            {
            case SDLK_RETURN:
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
void intr(SDL_Surface *ecran)
{
    SDL_Surface *intro[471]= {NULL};
    int continuer = 1,i;
    char nom[100];
    SDL_Event event;
    SDL_Rect position;
    position.x=0;
    position.y=0;
    Getf(f);
    Mix_Music *intr; //Création du pointeur de type Mix_Music
    intr=Mix_LoadMUS("Son/intro.mp3");
    Mix_AllocateChannels(32); //Allouer 32 canaux
    Mix_Volume(1, MIX_MAX_VOLUME/2); //Mettre à mi-volume le post 1
    Mix_VolumeMusic(MIX_MAX_VOLUME /2);


    for (int i = 0; i < 471; ++i)
    {
        sprintf(nom,"Video/Intro/Untitled_%d",i);
        strcat(nom,".png");

        intro[i]=IMG_Load(nom);
    }

    Mix_PlayMusic(intr, 0); //Jouer infiniment la musique
    for (int i = 0; i < 471; ++i)
    {
        SDL_BlitSurface(intro[i],NULL,ecran,&position);
        SDL_Flip(ecran);

        arduinoReadDataMenu(s);
        if(s[2]==1)
        {
            break;
        }

        if(f==NULL)
        {
            SDL_PollEvent(&event);
        }
        if(event.key.keysym.sym==SDLK_RETURN)
        {
            break;
        }
        SDL_Delay(20);
    }

    for (int i = 0; i < 471; ++i)
    {
        SDL_FreeSurface(intro[i]);
    }
    Mix_FreeMusic(intr);
}
void charger_image(SDL_Surface *intro[],SDL_Surface *ecran)
{
    char nom[100];
    SDL_Rect position;
    position.x=0;
    position.y=0;
    SDL_Surface *load[5]= {NULL};

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
    for (int i = 0; i < 432; ++i)
    {
        if(i==1)
        {
            SDL_BlitSurface(load[2],NULL,ecran,&position);
            SDL_Flip(ecran);
        }
        if(i==216)
        {
            SDL_BlitSurface(load[3],NULL,ecran,&position);
            SDL_Flip(ecran);
        }
        sprintf(nom,"Video/BD/m_%d",i);
        strcat(nom,".png");

        intro[i]=IMG_Load(nom);
    }
    SDL_BlitSurface(load[4],NULL,ecran,&position);
    SDL_Flip(ecran);

    for (int i = 0; i < 5; ++i)
    {
        SDL_FreeSurface(load[i]);
    }
}
void histoire(SDL_Surface *ecran,SDL_Surface *intro[])
{
    int continuer = 1,i;

    SDL_Event event;
    SDL_Rect position;
    position.x=0;
    position.y=0;
    Getf(f);

    for (int i = 0; i < 433; ++i)
    {
        SDL_BlitSurface(intro[i],NULL,ecran,&position);
        SDL_Flip(ecran);

        arduinoReadDataMenu(s);
        if(s[2]==1)
        {
            break;
        }

        if(f==NULL)
        {
            SDL_PollEvent(&event);
        }
        if(event.key.keysym.sym==SDLK_ESCAPE)
        {
            break;
        }
        SDL_Delay(20);
    }


    //  Mix_FreeMusic(intr);

}

void saisi(SDL_Event event,char ch[],int *continuer)
{

    int n=0,i;
    Getf(f);
    if(f!=NULL)
    {
        arduinoReadDataMenu(s);
        if(s[1]==1)
        {
            *continuer = 0;
        }

    }

    switch(event.type)
    {
    case SDLK_RETURN:
        *continuer = 0;
        break;



    case SDL_KEYDOWN:

        switch (event.key.keysym.sym)
        {
        case SDLK_a:
            n++;
            strcat(ch,"A");
            break;
        case SDLK_b:
            n++;
            strcat(ch,"B");
            break;
        case SDLK_c:
            n++;
            strcat(ch,"C");
            break;
        case SDLK_d:
            n++;
            strcat(ch,"D");
            break;
        case SDLK_e:
            n++;
            strcat(ch,"E");
            break;
        case SDLK_f:
            n++;
            strcat(ch,"F");
            break;
        case SDLK_g:
            n++;
            strcat(ch,"G");
            break;
        case SDLK_h:
            n++;
            strcat(ch,"H");
            break;
        case SDLK_i:
            n++;
            strcat(ch,"I");
            break;
        case SDLK_j:
            n++;
            strcat(ch,"J");
            break;
        case SDLK_k:
            n++;
            strcat(ch,"K");
            break;
        case SDLK_l:
            n++;
            strcat(ch,"L");
            break;
        case SDLK_m:
            n++;
            strcat(ch,"M");
            break;
        case SDLK_n:
            n++;
            strcat(ch,"N");
            break;
        case SDLK_o:
            n++;
            strcat(ch,"O");
            break;
        case SDLK_p:
            n++;
            strcat(ch,"P");
            break;
        case SDLK_q:
            n++;
            strcat(ch,"Q");
            break;
        case SDLK_r:
            n++;
            strcat(ch,"R");
            break;
        case SDLK_s:
            n++;
            strcat(ch,"S");
            break;
        case SDLK_t:
            n++;
            strcat(ch,"T");
            break;
        case SDLK_u:
            n++;
            strcat(ch,"U");
            break;
        case SDLK_v:
            n++;
            strcat(ch,"V");
            break;
        case SDLK_w:
            n++;
            strcat(ch,"W");
            break;
        case SDLK_x:
            n++;
            strcat(ch,"X");
            break;
        case SDLK_y:
            n++;
            strcat(ch,"Y");
            break;
        case SDLK_z:

            n++;
            strcat(ch,"Z");
            break;
        case SDLK_SPACE:

            n++;
            strcat(ch," ");
            break;


        }
        break;
    }
}

void choisir_voiture_multi(SDL_Surface *ecran,Mix_Music *musique,Mix_Chunk *son,int *k,Player player[])
{
    int pause=1,i,z=0,z2=0,a,a2,choix=3,choix2=3,couleur,valider=0,valider2=0;

    SDL_Event press;
    SDL_Surface *option_car[8]= {NULL},*image_done=NULL;
    SDL_Rect position_car[4],position_car2[4],position_bg;
    position_car[0].x = 102;
    position_car[0].y = 143;
    position_car[1].x = 659;
    position_car[1].y = 145;
    position_car[2].x = 298;
    position_car[2].y = 256;
    position_car[3].x = 0;
    position_car[3].y = 0;

    position_car2[0].x = 102;
    position_car2[0].y = 143+300;
    position_car2[1].x = 659;
    position_car2[1].y = 145+300;
    position_car2[2].x = 298;
    position_car2[2].y = 256+300;
    position_car2[3].x = 0;
    position_car2[3].y = 300;

    position_bg.x=0;
    position_bg.y=0;
    Getf(f);

    jouer_son(musique,son,*k);

    image_done=IMG_Load("Image/multiplayer/image_ready.png");
    option_car[0]=IMG_Load("Image/multiplayer/bouton-back1.png");
    option_car[1]=IMG_Load("Image/multiplayer/bouton-next1.png");
    option_car[2]=IMG_Load("Image/multiplayer/bouton-done.png");
    option_car[3]=IMG_Load("Image/multiplayer/voiture-2.png");
    option_car[4]=IMG_Load("Image/multiplayer/voiture-3.png");
    option_car[5]=IMG_Load("Image/multiplayer/voiture-4.png");
    option_car[6]=IMG_Load("Image/multiplayer/voiture-5.png");
    option_car[7]=IMG_Load("Image/multiplayer/voiture-6.png");


    SDL_BlitSurface(option_car[3],NULL,ecran,&position_car[3]);
    SDL_BlitSurface(option_car[3],NULL,ecran,&position_car2[3]);

    SDL_Flip(ecran);
    while(pause)
    {
        cmprev=cm[0];
        cmprevb=cm[1];
        arduinoReadDataMenu(cm);

        if(f!=NULL)
        {
            if(cm[0]==0 && cmprev!=0)
            {

                choix2--;
            }
            if(cm[0]==2 && cmprev!=2)
            {
                choix2++;
            }
            if(cm[1]==1 && cmprevb!=1)
            {
                valider2=1;
            }
            SDL_PollEvent(&press);
        }
        else
        {
            SDL_WaitEvent(&press);
        }

        switch(press.type)
        {
        case SDL_KEYDOWN:
            switch(press.key.keysym.sym)
            {
            case SDLK_LEFT:
                choix--;
                break;
            case SDLK_RIGHT:
                choix++;
                break;
            case SDLK_q:
                choix2--;
                break;
            case SDLK_d:
                choix2++;
                break;
            case SDLK_RETURN:
                valider=1;
                break;

            case SDLK_KP_ENTER:
                valider2=1;
                break;

            case SDLK_ESCAPE:
                pause=0;
                break;
            case SDLK_BACKSPACE:
                valider=0;
                valider2=0;
                break;
            }

        case SDL_MOUSEMOTION:
            if(press.motion.x>position_car[0].x && press.motion.x<position_car[0].x+47 && press.motion.y>position_car[0].y && press.motion.y<position_car[0].y+63)
            {
                z=0;
            }
            if(press.motion.x>position_car[1].x && press.motion.x<position_car[1].x+43 && press.motion.y>position_car[1].y && press.motion.y<position_car[1].y+63)
            {
                z=1;
            }
            if(press.motion.x>position_car[2].x && press.motion.x<position_car[2].x+195 && press.motion.y>position_car[2].y && press.motion.y<position_car[2].y+38)
            {
                z=2;
            }


            if(press.motion.x>position_car2[0].x && press.motion.x<position_car2[0].x+47 && press.motion.y>position_car2[0].y && press.motion.y<position_car2[0].y+63)
            {
                z2=0;
            }
            if(press.motion.x>position_car2[1].x && press.motion.x<position_car2[1].x+43 && press.motion.y>position_car2[1].y && press.motion.y<position_car2[1].y+63)
            {
                z2=1;
            }
            if(press.motion.x>position_car2[2].x && press.motion.x<position_car2[2].x+195 && press.motion.y>position_car2[2].y && press.motion.y<position_car2[2].y+38)
            {
                z2=2;
            }

            break;


        case SDL_MOUSEBUTTONDOWN:
            if (press.button.button==SDL_BUTTON_LEFT)
            {
                if(press.button.x>position_car[0].x && press.button.x<position_car[0].x+47 && press.button.y>position_car[0].y && press.button.y<position_car[0].y+63)
                {
                    choix++;
                }
                if(press.button.x>position_car[1].x && press.button.x<position_car[1].x+43 && press.button.y>position_car[1].y && press.button.y<position_car[1].y+63)
                {
                    choix--;
                }
                if(press.button.x>position_car[2].x && press.button.x<position_car[2].x+195 && press.button.y>position_car[2].y && press.button.y<position_car[2].y+38)
                {
                    valider=1;
                }

                if(press.button.x>position_car2[0].x && press.button.x<position_car2[0].x+47 && press.button.y>position_car2[0].y && press.button.y<position_car2[0].y+63)
                {
                    choix2++;
                }
                if(press.button.x>position_car2[1].x && press.button.x<position_car2[1].x+43 && press.button.y>position_car2[1].y && press.button.y<position_car2[1].y+63)
                {
                    choix2--;
                }
                if(press.button.x>position_car2[2].x && press.button.x<position_car2[2].x+195 && press.button.y>position_car2[2].y && press.button.y<position_car2[2].y+38)
                {
                    valider2=1;
                }

            }
            break;

        }

        if (valider==1)
        {
            player[0].v.couleur=choix;
        }
        if(valider2==1)
        {
            player[1].v.couleur=choix2;
        }

        if(valider==1&&valider2==1)
        {
            jouer_multi(ecran,player,k);
            pause=0;
        }

        if(choix>7)
            choix=3;
        if(choix<3)
            choix=7;

        if(choix2>7)
            choix2=3;
        if(choix2<3)
            choix2=7;

        if(a!=choix&&valider!=1)
        {
            Mix_PlayChannel(1, son, 0);//Joue
            a=choix;
        }
        if(a2!=choix2&&valider2!=1)
        {
            Mix_PlayChannel(1, son, 0);//Joue
            a2=choix2;
        }

        if(pause!=0)
        {
            SDL_BlitSurface(option_car[choix],NULL,ecran,&position_car[3]);
            SDL_BlitSurface(option_car[choix2],NULL,ecran,&position_car2[3]);
            SDL_BlitSurface(option_car[z],NULL,ecran,&position_car[z]);
            SDL_BlitSurface(option_car[z2],NULL,ecran,&position_car2[z2]);
            if(valider==1)
            {
                SDL_BlitSurface(image_done,NULL,ecran,&position_car[3]);
            }
            if(valider2==1)
            {
                SDL_BlitSurface(image_done,NULL,ecran,&position_car2[3]);
            }

        }

        SDL_Flip(ecran);

    }
    for (int i = 0; i < 8; ++i)
    {
        SDL_FreeSurface(option_car[i]);
    }
    SDL_FreeSurface(image_done);

}


void choisir_voiture(SDL_Surface *ecran,Mix_Music *musique,Mix_Chunk *son,int *k,Player *player,char *chemin,SDL_Surface *intro[])
{
    int pause=1,i,z=0,a,choix=3,couleur;
    char chemin_fichier[]="Image/message.png";

    SDL_Event press;
    SDL_Surface *option_car[8]= {NULL},*option_texte[6]= {NULL},*image=NULL;
    SDL_Rect position_car[4],position_bg;
    position_car[0].x = 25;
    position_car[0].y = 322;
    position_car[1].x = 708;
    position_car[1].y = 330;
    position_car[2].x = 260;
    position_car[2].y = 520;
    position_car[3].x = 0;
    position_car[3].y = 0;

    position_bg.x=0;
    position_bg.y=0;
    Getf(f);

    jouer_son(musique,son,*k);

    option_car[0]=IMG_Load("Image/bouton-back1.png");
    option_car[1]=IMG_Load("Image/bouton-next1.png");
    option_car[2]=IMG_Load("Image/bouton-done.png");
    option_car[3]=IMG_Load("Image/voiture-2.png");
    option_car[4]=IMG_Load("Image/voiture-3.png");
    option_car[5]=IMG_Load("Image/voiture-4.png");
    option_car[6]=IMG_Load("Image/voiture-5.png");
    option_car[7]=IMG_Load("Image/voiture-6.png");


    SDL_BlitSurface(option_car[3],NULL,ecran,&position_car[3]);

    SDL_Flip(ecran);
    while(pause)
    {
        sprev=s[0];
        arduinoReadDataMenu(s);
        printf("s0v=%d\n", s[0]);
        printf("bv=%d\n", s[1]);

        if(f!=NULL)
        {
            if(s[0]==0 && sprev!=0)
            {

                choix--;
            }
            if(s[0]==2 && sprev!=2)
            {
                choix++;
            }
            if(s[1]==1)
            {
                player->v.couleur=choix;
                player->stage=0;
                ajouter_player(chemin,*player);
                histoire(ecran,intro);
                image_mission(ecran,chemin_fichier);
                jouer(ecran,k,*player);
                pause=0;
            }
        }
        if(f!=NULL)
        {
            SDL_PollEvent(&press);
        }
        else
        {
            SDL_WaitEvent(&press);
        }

        switch(press.type)
        {
        case SDL_KEYDOWN:
            switch(press.key.keysym.sym)
            {
            case SDLK_LEFT:
                choix--;
                break;
            case SDLK_RIGHT:
                choix++;
                break;
            case SDLK_RETURN:
                player->v.couleur=choix;
                player->stage=0;
                ajouter_player(chemin,*player);
                histoire(ecran,intro);
                image_mission(ecran,chemin_fichier);
                jouer(ecran,k,*player);
                pause=0;
                break;
            }

        case SDL_MOUSEMOTION:
            if(press.motion.x>position_car[0].x && press.motion.x<position_car[0].x+76 && press.motion.y>position_car[0].y && press.motion.y<position_car[0].y+71)
            {
                z=0;
            }
            if(press.motion.x>position_car[1].x && press.motion.x<position_car[1].x+58 && press.motion.y>position_car[1].y && press.motion.y<position_car[1].y+66)
            {
                z=1;
            }
            if(press.motion.x>position_car[2].x && press.motion.x<position_car[2].x+292 && press.motion.y>position_car[2].y && press.motion.y<position_car[2].y+58)
            {
                z=2;
            }

            break;

        case SDL_MOUSEBUTTONDOWN:
            if (press.button.button==SDL_BUTTON_LEFT)
            {
                if(press.button.x>position_car[0].x && press.button.x<position_car[0].x+76 && press.button.y>position_car[0].y && press.button.y<position_car[0].y+71)
                {
                    choix++;
                }
                if(press.button.x>position_car[1].x && press.button.x<position_car[1].x+58 && press.button.y>position_car[1].y && press.button.y<position_car[1].y+66)
                {
                    choix--;
                }
                if(press.button.x>position_car[2].x && press.button.x<position_car[2].x+292 && press.button.y>position_car[2].y && press.button.y<position_car[2].y+58)
                {
                    player->v.couleur=choix;
                    player->stage=0;
                    ajouter_player(chemin,*player);
                    histoire(ecran,intro);
                    image_mission(ecran,chemin_fichier);
                    jouer(ecran,k,*player);
                    pause=0;
                }

            }
            break;
        }

        if(choix>7)
            choix=3;
        if(choix<3)
            choix=7;
        if(a!=choix)
        {
            Mix_PlayChannel(1, son, 0);//Joue
            a=choix;
        }

        if(pause!=0)
        {
            SDL_BlitSurface(option_car[choix],NULL,ecran,&position_car[3]);
            SDL_BlitSurface(option_car[z],NULL,ecran,&position_car[z]);

        }

        SDL_Flip(ecran);

    }
    for (int i = 0; i < 8; ++i)
    {
        SDL_FreeSurface(option_car[i]);
    }
    for (int i = 0; i < 6; ++i)
    {
        SDL_FreeSurface(option_texte[i]);
    }
}

int verifier_player(char *chemin,char *pseudo)
{
    Player p;

    int valider=0;
    FILE *f=NULL;
    f=fopen(chemin,"r");
    while(!feof(f))
    {
        fscanf(f,"%s %d %d %d",p.pseudo,&p.score,&p.v.couleur,&p.stage);
        if(strcmp(p.pseudo,pseudo)==0)
        {
            valider=1;
        }
    }
    fclose(f);

    return valider;
}

void ajouter_player(char *chemin,Player j)
{
    FILE *f=NULL;
    f=fopen(chemin,"a");
    //fwrite(&j,sizeof(joueur),1,f);
    fprintf(f,"%s %d %d %d\n",j.pseudo,j.score,j.v.couleur,j.stage );
    fclose(f);
}

void saisi_info(SDL_Surface *ecran,Mix_Music *musique,Mix_Chunk *son,int *k,Player *player,char *chemin)
{

    int pause=1,i,z=1,a,b,x=0,n,valider=-1;
    strcpy(player->pseudo,"");
    player->stage=0;
    char pseudo[20];
    SDL_Event press;
    SDL_Surface *option_new[3]= {NULL},*texte=NULL,*erreur=NULL;
    SDL_Rect position_new[3],position_texte,position_texte_erreur;
    position_new[0].x = 0;
    position_new[0].y = 0;
    position_new[1].x = 690;
    position_new[1].y = 324;
    position_new[2].x = 45;
    position_new[2].y = 324;
    position_texte.x=152;
    position_texte.y=383;
    position_texte_erreur.x=80;
    position_texte_erreur.y=500;
    Getf(f);


    TTF_Font *police=NULL,*police_erreur=NULL;
    police=TTF_OpenFont("Police/arial.ttf",35);
    police_erreur=TTF_OpenFont("Police/Heroes Legend.ttf",25);
    SDL_Color couleur= {250,250,250};
    SDL_Color couleur_erreur= {120,120,20};

    jouer_son(musique,son,*k);

    option_new[0]=IMG_Load("Image/menu-new.png");
    option_new[1]=IMG_Load("Image/bouton-next1.png");
    option_new[2]=IMG_Load("Image/bouton-back1.png");



    pause=1;
    for(i=0; i<3; i++)
    {
        SDL_BlitSurface(option_new[i],NULL,ecran,&position_new[i]);
    }
    SDL_Flip(ecran);



    strcpy(pseudo,"");
    while(pause)
    {
        if(f!=NULL)
        {
            arduinoReadDataSaisi(Sa);
            if(Sa[0]==2)
            {
                valider=charger_parti(chemin,player,pseudo);
                if(valider==1&&strlen(pseudo)>1)
                {
                    load(ecran,musique,son,k,player);
                    pause=0;
                }
                else
                {
                    strcpy(pseudo,"");
                    erreur=TTF_RenderText_Blended(police_erreur,"sorry this name is not valide",couleur_erreur);
                }
            }
            if(Sa[0]==0)
            {
                pause=0;
            }
        }
        if(f!=NULL)
        {
            SDL_PollEvent(&press);
        }
        else
        {
            SDL_WaitEvent(&press);
        }

        switch(press.type)
        {
        case SDL_MOUSEMOTION:
            if(press.motion.x>position_new[1].x && press.motion.x<position_new[1].x+74 && press.motion.y>position_new[1].y && press.motion.y<position_new[1].y+71)
            {
                z=1;
            }
            if(press.motion.x>position_new[2].x && press.motion.x<position_new[2].x+74 && press.motion.y>position_new[2].y && press.motion.y<position_new[2].y+71)
            {
                z=2;
            }


            break;

        case SDL_MOUSEBUTTONDOWN:
            if (press.button.button==SDL_BUTTON_LEFT)
            {
                if(press.button.x>position_new[1].x && press.button.x<position_new[1].x+74 && press.button.y>position_new[1].y && press.button.y<position_new[1].y+71)
                {
                    valider=charger_parti(chemin,player,pseudo);
                    if(valider==1&&strlen(pseudo)>1)
                    {
                        load(ecran,musique,son,k,player);
                        pause=0;
                    }
                    else
                    {
                        strcpy(pseudo,"");
                        erreur=TTF_RenderText_Blended(police_erreur,"sorry this name is not valide",couleur_erreur);
                    }
                }
                if(press.button.x>position_new[2].x && press.button.x<position_new[2].x+74 && press.button.y>position_new[2].y && press.button.y<position_new[2].y+71)
                {
                    pause=0;
                }

            }
            break;
        case SDL_KEYDOWN:
            n=strlen(pseudo);
            if (n<9)
                saisi(press,pseudo,&pause);


            switch (press.key.keysym.sym)
            {

            case SDLK_BACKSPACE:
                if (n>0)
                {
                    n--;
                    pseudo[n]='\0';
                    break;
                }
            case SDLK_RETURN:
                valider=charger_parti( chemin,player,pseudo);
                if(valider==1&&strlen(pseudo)>1)
                {
                    load(ecran,musique,son,k,player);
                    pause=0;
                }
                else
                {
                    strcpy(pseudo,"");
                    erreur=TTF_RenderText_Blended(police_erreur,"sorry this name is not valide",couleur_erreur);
                }
                break;

            }

            texte=TTF_RenderText_Blended(police,pseudo,couleur);

            break;
        }
        if(a!=z)
        {
            Mix_PlayChannel(1, son, 0);//Joue
            a=z;
        }

        if(pause==1)
        {
            for(i=0; i<3; i++)
            {
                SDL_BlitSurface(option_new[i],NULL,ecran,&position_new[i]);
            }
            SDL_BlitSurface(option_new[z],NULL,ecran,&position_new[z]);


            SDL_BlitSurface(texte,NULL,ecran,&position_texte);
            if(valider==0)
            {
                SDL_BlitSurface(erreur,NULL,ecran,&position_texte_erreur);
            }
        }

        SDL_Flip(ecran);

    }

    TTF_CloseFont(police);
    TTF_CloseFont(police_erreur);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(erreur);
    for(i=0; i<3; i++)
    {
        SDL_FreeSurface(option_new[i]);
    }


}

void new_game(SDL_Surface *ecran,Mix_Music *musique,Mix_Chunk *son,int *k,Player *player,char *chemin,SDL_Surface *intro[])
{

    int pause=1,i,z=1,a,b,x=0,n,valider=-1;
    strcpy(player->pseudo,"");
    player->stage=0;
    char pseudo[20];
    SDL_Event press;
    SDL_Surface *option_new[3]= {NULL},*texte=NULL,*erreur=NULL;
    SDL_Rect position_new[3],position_texte,position_texte_erreur;
    position_new[0].x = 0;
    position_new[0].y = 0;
    position_new[1].x = 690;
    position_new[1].y = 324;
    position_new[2].x = 45;
    position_new[2].y = 324;
    position_texte.x=152;
    position_texte.y=383;
    position_texte_erreur.x=80;
    position_texte_erreur.y=500;
    Getf(f);


    TTF_Font *police=NULL,*police_erreur=NULL;
    police=TTF_OpenFont("Police/arial.ttf",35);
    police_erreur=TTF_OpenFont("Police/Heroes Legend.ttf",25);
    SDL_Color couleur= {250,250,250};
    SDL_Color couleur_erreur= {120,120,20};

    jouer_son(musique,son,*k);

    option_new[0]=IMG_Load("Image/menu-new.png");
    option_new[1]=IMG_Load("Image/bouton-next1.png");
    option_new[2]=IMG_Load("Image/bouton-back1.png");



    pause=1;
    for(i=0; i<3; i++)
    {
        SDL_BlitSurface(option_new[i],NULL,ecran,&position_new[i]);
    }
    SDL_Flip(ecran);



    strcpy(pseudo,"");
    while(pause)
    {

        if(f!=NULL)
        {
            arduinoReadDataNew(new);
            if(new[0]==2)
            {
                valider=verifier_player(chemin,pseudo);
                if(valider==0&&strlen(pseudo)>1)
                {
                    strcat(player->pseudo,pseudo);
                    choisir_voiture(ecran,musique,son,k,player,chemin,intro);
                    pause=0;
                }
            }

            if(new[0]==0)
            {
                pause=0;
            }
        }

        if(f!=NULL)
        {
            SDL_PollEvent(&press);
        }
        else
        {
            SDL_WaitEvent(&press);
        }


        switch(press.type)
        {
        case SDL_MOUSEMOTION:
            if(press.motion.x>position_new[1].x && press.motion.x<position_new[1].x+74 && press.motion.y>position_new[1].y && press.motion.y<position_new[1].y+71)
            {
                z=1;
            }
            if(press.motion.x>position_new[2].x && press.motion.x<position_new[2].x+74 && press.motion.y>position_new[2].y && press.motion.y<position_new[2].y+71)
            {
                z=2;
            }


            break;

        case SDL_MOUSEBUTTONDOWN:
            if (press.button.button==SDL_BUTTON_LEFT)
            {
                if(press.button.x>position_new[1].x && press.button.x<position_new[1].x+74 && press.button.y>position_new[1].y && press.button.y<position_new[1].y+71)
                {
                    valider=verifier_player(chemin,pseudo);
                    if(valider==0&&strlen(pseudo)>1)
                    {
                        strcat(player->pseudo,pseudo);
                        choisir_voiture(ecran,musique,son,k,player,chemin,intro);
                        pause=0;
                    }
                    else
                    {
                        strcpy(pseudo,"");
                        erreur=TTF_RenderText_Blended(police_erreur,"sorry this name is already used",couleur_erreur);
                    }
                }
                if(press.button.x>position_new[2].x && press.button.x<position_new[2].x+74 && press.button.y>position_new[2].y && press.button.y<position_new[2].y+71)
                {
                    pause=0;
                }

            }
            break;
        case SDL_KEYDOWN:
            n=strlen(pseudo);
            if (n<9)
                saisi(press,pseudo,&pause);


            switch (press.key.keysym.sym)
            {

            case SDLK_BACKSPACE:
                if (n>0)
                {
                    n--;
                    pseudo[n]='\0';
                    break;
                }
            case SDLK_RETURN:
                valider=verifier_player(chemin,pseudo);
                //printf("%d\n",valider );
                if(valider==0&&strlen(pseudo)>1)
                {
                    strcpy(player->pseudo,pseudo);
                    choisir_voiture(ecran,musique,son,k,player,chemin,intro);
                    pause=0;
                }
                else
                {
                    strcpy(pseudo,"");
                    erreur=TTF_RenderText_Blended(police_erreur,"sorry this name is already used",couleur_erreur);

                }
                break;

            }

            texte=TTF_RenderText_Blended(police,pseudo,couleur);

            break;
        }
        if(a!=z)
        {
            Mix_PlayChannel(1, son, 0);//Joue
            a=z;
        }

        if(pause==1)
        {
            for(i=0; i<3; i++)
            {
                SDL_BlitSurface(option_new[i],NULL,ecran,&position_new[i]);
            }
            SDL_BlitSurface(option_new[z],NULL,ecran,&position_new[z]);


            SDL_BlitSurface(texte,NULL,ecran,&position_texte);
            if(valider==1)
            {

                SDL_BlitSurface(erreur,NULL,ecran,&position_texte_erreur);

            }
        }

        SDL_Flip(ecran);

    }

    TTF_CloseFont(police);
    TTF_CloseFont(police_erreur);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(erreur);
    for(i=0; i<3; i++)
    {
        SDL_FreeSurface(option_new[i]);
    }


}

void load(SDL_Surface *ecran,Mix_Music *musique,Mix_Chunk *son,int *k,Player *player)
{
    int pause=1,i,z=1,a,erreur=0,temps,ancien;
    SDL_Event press;
    SDL_Surface *option_load[7]= {NULL},*texte=NULL;
    SDL_Rect position_load[7],position_texte;
    position_load[0].x = 0;
    position_load[0].y = 0;
    position_load[1].x = 0;
    position_load[1].y = 174;
    position_load[2].x = 0;
    position_load[2].y = 249;
    position_load[3].x = 0;
    position_load[3].y = 319;
    position_load[4].x = 0;
    position_load[4].y = 388;
    position_load[5].x = 0;
    position_load[5].y = 460;
    position_load[6].x = 0;
    position_load[6].y = 529;

    position_texte.x=140;
    position_texte.y=300;
    Getf(f);

    TTF_Font *police=NULL;
    police=TTF_OpenFont("Police/Heroes Legend.ttf",60);
    SDL_Color couleur= {255,0,0};


    jouer_son(musique,son,*k);

    option_load[0]=IMG_Load("Image/background.png");
    option_load[1]=IMG_Load("Image/bouton-resume.png");
    option_load[2]=IMG_Load("Image/bouton-stage2.png");
    option_load[3]=IMG_Load("Image/bouton-stage3.png");
    option_load[4]=IMG_Load("Image/bouton-stage4.png");
    option_load[5]=IMG_Load("Image/bouton-stage5.png");
    option_load[6]=IMG_Load("Image/bouton-back-load.png");

    pause=1;
    for(i=0; i<7; i++)
    {
        SDL_BlitSurface(option_load[i],NULL,ecran,&position_load[i]);
    }
    SDL_Flip(ecran);
    while(pause)
    {
        if(f!=NULL)
        {

            lprev=l[0];
            arduinoReadDataLoad(l);
            printf("arduino load\n");
            printf("lo= %d l1= %d\n",l[0],l[1] );
            if(l[0]==0 && lprev!=0)
            {
                z--;

            }
            if(l[0]==2 && lprev!=2)
            {
                z++;
            }
            printf("z=%d\n",z );
            if(l[1]==1)
            {
                if(z==1)
                {
                    jouer(ecran,k,*player);
                }
                else if(z==2)
                {
                    if(player->stage>=1)
                    {
                        player->stage=1;
                        jouer(ecran,k,*player);
                    }
                    else
                    {
                        erreur=1;
                    }
                }
                else if(z==3)
                {
                    if(player->stage>=2)
                    {
                        player->stage=2;
                        jouer(ecran,k,*player);
                    }
                    else
                    {
                        erreur=1;
                    }
                }
                else if(z==4)
                {
                    if(player->stage>=3)
                    {
                        player->stage=3;
                        jouer(ecran,k,*player);
                    }
                    else
                    {
                        erreur=1;
                    }
                }
                else if(z==5)
                {
                    if(player->stage>=4)
                    {
                        player->stage=4;
                        jouer(ecran,k,*player);
                    }
                    else
                    {
                        erreur=1;
                    }
                }
                if(z==6)
                {
                    pause=0;
                }

            }
        }

        if(f!=NULL)
        {
            SDL_PollEvent(&press);
        }
        else
        {
            SDL_WaitEvent(&press);
        }

        switch(press.type)
        {
        case SDL_KEYDOWN:
            switch(press.key.keysym.sym)
            {
            case SDLK_UP:
                z--;
                break;
            case SDLK_DOWN:
                z++;
                break;
            case SDLK_RETURN:
                if(z==1)
                {
                    jouer(ecran,k,*player);
                    jouer_son(musique,son,*k);
                }
                else if(z==2)
                {
                    if(player->stage>=1)
                    {
                        player->stage=1;
                        jouer(ecran,k,*player);
                        jouer_son(musique,son,*k);
                    }
                    else
                    {
                        erreur=1;
                    }
                }
                else if(z==3)
                {
                    if(player->stage>=2)
                    {
                        player->stage=2;
                        jouer(ecran,k,*player);
                        jouer_son(musique,son,*k);
                    }
                    else
                    {
                        erreur=1;
                    }
                }
                else if(z==4)
                {
                    if(player->stage>=3)
                    {
                        player->stage=3;
                        jouer(ecran,k,*player);
                        jouer_son(musique,son,*k);
                    }
                    else
                    {
                        erreur=1;
                    }
                }
                else if(z==5)
                {
                    if(player->stage>=4)
                    {
                        player->stage=4;
                        jouer(ecran,k,*player);
                        jouer_son(musique,son,*k);
                    }
                    else
                    {
                        erreur=1;
                    }
                }
                if(z==6)
                {
                    pause=0;
                }

                break;
            }

        case SDL_MOUSEMOTION:
            if(press.motion.x>position_load[1].x && press.motion.x<position_load[1].x+452 && press.motion.y>position_load[1].y && press.motion.y<position_load[1].y+98)
            {
                z=1;
            }
            if(press.motion.x>position_load[2].x && press.motion.x<position_load[2].x+491 && press.motion.y>position_load[2].y && press.motion.y<position_load[2].y+93)
            {
                z=2;
            }
            if(press.motion.x>position_load[3].x && press.motion.x<position_load[3].x+497 && press.motion.y>position_load[3].y && press.motion.y<position_load[3].y+93)
            {
                z=3;
            }
            if(press.motion.x>position_load[4].x && press.motion.x<position_load[4].x+503 && press.motion.y>position_load[4].y && press.motion.y<position_load[4].y+96)
            {
                z=4;
            }
            if(press.motion.x>position_load[5].x && press.motion.x<position_load[5].x+503 && press.motion.y>position_load[5].y && press.motion.y<position_load[5].y+94)
            {
                z=5;
            }
            if(press.motion.x>position_load[6].x && press.motion.x<position_load[6].x+464 && press.motion.y>position_load[6].y && press.motion.y<position_load[6].y+87)
            {
                z=6;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (press.button.button==SDL_BUTTON_LEFT)
            {
                if(press.button.x>position_load[1].x && press.button.x<position_load[1].x+452 && press.button.y>position_load[1].y && press.button.y<position_load[1].y+98)
                {
                    jouer(ecran,k,*player);
                    jouer_son(musique,son,*k);
                }
                if(press.button.x>position_load[2].x && press.button.x<position_load[2].x+491 && press.button.y>position_load[2].y && press.button.y<position_load[2].y+93)
                {
                    if(player->stage>=1)
                    {
                        player->stage=1;
                        jouer(ecran,k,*player);
                        jouer_son(musique,son,*k);
                    }
                    else
                    {
                        erreur=1;
                    }
                }
                if(press.button.x>position_load[3].x && press.button.x<position_load[3].x+497 && press.button.y>position_load[3].y && press.button.y<position_load[3].y+93)
                {
                    if(player->stage>=2)
                    {
                        player->stage=2;
                        jouer(ecran,k,*player);
                        jouer_son(musique,son,*k);
                    }
                    else
                    {
                        erreur=1;
                    }
                }
                if(press.button.x>position_load[4].x && press.button.x<position_load[4].x+503 && press.button.y>position_load[4].y && press.button.y<position_load[4].y+96)
                {
                    if(player->stage>=3)
                    {
                        player->stage=3;
                        jouer(ecran,k,*player);
                        jouer_son(musique,son,*k);
                    }
                    else
                    {
                        erreur=1;
                    }
                }
                if(press.button.x>position_load[5].x && press.button.x<position_load[5].x+503 && press.button.y>position_load[5].y && press.button.y<position_load[5].y+94)
                {
                    if(player->stage>=4)
                    {
                        player->stage=4;
                        jouer(ecran,k,*player);
                        jouer_son(musique,son,*k);
                    }
                    else
                    {
                        erreur=1;
                    }
                }
                if(press.button.x>position_load[6].x && press.button.x<position_load[6].x+464 && press.button.y>position_load[6].y && press.button.y<position_load[6].y+87)
                {
                    pause=0;
                }
            }
            break;
        }

        if(z>6)
            z=1;
        if(z<1)
            z=6;
        if(a!=z)
        {
            Mix_PlayChannel(1, son, 0);//Joue
            a=z;
        }
        if(pause!=0)
        {
            for(i=0; i<7; i++)
            {
                SDL_BlitSurface(option_load[i],NULL,ecran,&position_load[i]);
            }
            SDL_BlitSurface(option_load[z],NULL,ecran,&position_load[z]);
        }

        if(erreur==1)
        {
            texte=TTF_RenderText_Blended(police,"level blocked",couleur);
            SDL_BlitSurface(texte,NULL,ecran,&position_texte);
            erreur=0;
        }

        SDL_Flip(ecran);
    }
    for (int i = 0; i < 7; ++i)
    {
        SDL_FreeSurface(option_load[i]);
    }
    SDL_FreeSurface(texte);
}

void multiplayers(SDL_Surface *ecran,Mix_Music *musique,Mix_Chunk *son,int k)
{
    Player p[2];
    strcpy(p[0].pseudo,"PLAYER 1");
    strcpy(p[1].pseudo,"PLAYER 2");

    int pause=1,i,z=1,a;
    SDL_Event press;
    SDL_Surface *option_multi[4]= {NULL};
    SDL_Rect position_multi[4];
    position_multi[0].x = 0;
    position_multi[0].y = 0;
    position_multi[1].x = 0;
    position_multi[1].y = 220;
    position_multi[2].x = 0;
    position_multi[2].y = 327;
    position_multi[3].x = 0;
    position_multi[3].y = 435;
    Getf(f);

    jouer_son(musique,son,k);

    option_multi[0]=IMG_Load("Image/background.png");
    option_multi[1]=IMG_Load("Image/bouton-start-local.png");
    option_multi[2]=IMG_Load("Image/bouton-join-local.png");
    option_multi[3]=IMG_Load("Image/bouton-back-multi.png");


    pause=1;
    for(i=0; i<4; i++)
    {
        SDL_BlitSurface(option_multi[i],NULL,ecran,&position_multi[i]);
    }
    SDL_Flip(ecran);
    while(pause)
    {
        multiprev=multi[0];
        multiprevb=multi[1];
        arduinoReadDataMulti(multi);
        printf("multi0=%d\n", multi[0]);
        printf("multi1=%d\n", multi[1]);
        if(f!=NULL)
        {

        }
        if(multi[0]==0 && multiprev!=0)
        {
            z--;
        }
        if(multi[0]==2 && multiprev!=2)
        {
            z++;
        }

        if(multi[1]==1 && multiprevb!=1)
        {
            if(z==1)
            {
                choisir_voiture_multi(ecran,musique,son,&k,p);
                jouer_son(musique,son,k);
            }

            if(z=3)
            {
                pause=0;
            }
        }

        if(f==NULL)
        {
            SDL_WaitEvent(&press);

            switch(press.type)
            {
            case SDL_KEYDOWN:
                switch(press.key.keysym.sym)
                {
                case SDLK_UP:
                    z--;
                    break;
                case SDLK_DOWN:
                    z++;
                    break;
                case SDLK_RETURN:
                    if(z==3)
                        pause=0;

                    if(z==1)
                    {
                        choisir_voiture_multi(ecran,musique,son,&k,p);
                        jouer_son(musique,son,k);
                    }
                    break;
                }

            case SDL_MOUSEMOTION:
                if(press.motion.x>position_multi[1].x && press.motion.x<position_multi[1].x+530 && press.motion.y>position_multi[1].y && press.motion.y<position_multi[1].y+126)
                {
                    z=1;
                }
                if(press.motion.x>position_multi[2].x && press.motion.x<position_multi[2].x+539 && press.motion.y>position_multi[2].y && press.motion.y<position_multi[2].y+126)
                {
                    z=2;
                }
                if(press.motion.x>position_multi[3].x && press.motion.x<position_multi[3].x+521 && press.motion.y>position_multi[3].y && press.motion.y<position_multi[3].y+138)
                {
                    z=3;
                }

                break;

            case SDL_MOUSEBUTTONDOWN:
                if (press.button.button==SDL_BUTTON_LEFT)
                {
                    if(press.button.x>position_multi[1].x && press.button.x<position_multi[1].x+530 && press.button.y>position_multi[1].y && press.button.y<position_multi[1].y+126)
                    {
                        choisir_voiture_multi(ecran,musique,son,&k,p);
                        jouer_son(musique,son,k);
                        z=1;
                    }
                    if(press.button.x>position_multi[2].x && press.button.x<position_multi[2].x+539 && press.button.y>position_multi[2].y && press.button.y<position_multi[2].y+126)
                    {
                        z=2;
                    }

                    if(press.button.x>position_multi[3].x && press.button.x<position_multi[3].x+521 && press.button.y>position_multi[3].y && press.button.y<position_multi[3].y+138)
                    {
                        pause=0;
                    }
                }
                break;
            }

        }

        if(z>3)
            z=1;
        if(z<1)
            z=3;
        if(a!=z)
        {
            Mix_PlayChannel(1, son, 0);//Joue
            a=z;
        }

        for(i=0; i<4; i++)
        {
            SDL_BlitSurface(option_multi[i],NULL,ecran,&position_multi[i]);
        }
        SDL_BlitSurface(option_multi[z],NULL,ecran,&position_multi[z]);

        SDL_Flip(ecran);
    }
    for (int i = 0; i < 4; ++i)
    {
        SDL_FreeSurface(option_multi[i]);
    }
}

void setting(SDL_Surface *ecran,Mix_Music *musique,Mix_Chunk *son,int *k)
{
    int i,a,suit=1,b=0,pos[2]= {0},u=1,z=0;


    SDL_Surface *option_setting[7]= {NULL},*image_story=NULL,*back_story=NULL;
    SDL_Rect position_story,position_back,position_setting[7];
    position_story.x=0;
    position_story.y=0;
    position_back.x=22;
    position_back.y=520;

    position_setting[0].x=0;
    position_setting[0].y=0;
    position_setting[1].x=1;
    position_setting[1].y=220;
    position_setting[2].x=1;
    position_setting[2].y=300;
    position_setting[3].x=1;
    position_setting[3].y=370;
    position_setting[4].x=1;
    position_setting[4].y=468;
    position_setting[5].x=35;
    position_setting[5].y=225;
    position_setting[6].x=358;
    position_setting[6].y=225;

    Getf(f);


    option_setting[0]=IMG_Load("Image/background.png");
    option_setting[1]=IMG_Load("Image/bouton-sound.png");
    option_setting[2]=IMG_Load("Image/bouton-contrast.png");
    option_setting[3]=IMG_Load("Image/bouton-full-screen.png");
    option_setting[4]=IMG_Load("Image/bouton-back.png");
    option_setting[6]=IMG_Load("Image/bouton-plus.png");
    option_setting[5]=IMG_Load("Image/bouton-moins.png");

    image_story=IMG_Load("Image/menu-story.png");
    back_story=IMG_Load("Image/bouton.png");

    jouer_son(musique,son,*k);

    suit=1;
    for(i=0; i<7; i++)
    {
        SDL_BlitSurface(option_setting[i],NULL,ecran,&position_setting[i]);
    }
    SDL_Flip(ecran);

    SDL_Event touch;

    while(suit)
    {
        if(f!=NULL)
        {
            setprev=set[0];
            setbprev=set[1];
            arduinoReadDataSet(set);
            printf("%d,%d,%d,%d",set[0],set[1],set[2],set[3]);

            if(set[0]==0 && setprev!=0)
            {

                b--;
            }
            if(set[0]==2 && setprev!=2)
            {
                b++;
            }

            if(set[1]==1 && setbprev!=1)
            {
                if(b==4)
                    suit=0;
                else if(b==3)
                {
                    ecran =SDL_GetVideoSurface();
                    Uint32 flags        =(ecran->flags^SDL_FULLSCREEN);
                    ecran =SDL_SetVideoMode(0,0,0, flags);
                    //SDL_WM_ToggleFullScreen(ecran);
                }

                else if(b==2)
                {
                    SDL_BlitSurface(image_story,NULL,ecran,&position_story);
                    SDL_Flip(ecran);
                    SDL_Event event;
                    u=1;
                    while(u)
                    {
                        if(set[0]==0)
                        {
                            u=0;
                        }

                        if(set[0]==2)
                        {
                            SDL_BlitSurface(back_story,NULL,ecran,&position_story);
                        }
                        else if(s[0]!=2)
                        {
                            SDL_BlitSurface(image_story,NULL,ecran,&position_story);
                        }
                        SDL_Flip(ecran);

                    }
                }

            }
        }

        else
        {
            SDL_WaitEvent(&touch);
            switch(touch.type)
            {
            case SDL_QUIT:
                suit=0;
                break;
            case SDL_KEYDOWN:
                switch(touch.key.keysym.sym)
                {
                case SDLK_UP:
                    b--;
                    break;
                case SDLK_DOWN:
                    b++;
                    break;
                case SDLK_RETURN:
                    if(b==4)
                        suit=0;
                    else if(b==3)
                    {
                        ecran =SDL_GetVideoSurface();
                        Uint32 flags        =(ecran->flags^SDL_FULLSCREEN);
                        ecran =SDL_SetVideoMode(0,0,0, flags);
                        //SDL_WM_ToggleFullScreen(ecran);
                    }

                    else if(b==2)
                    {
                        SDL_BlitSurface(image_story,NULL,ecran,&position_story);
                        SDL_Flip(ecran);
                        SDL_Event event;
                        u=1;
                        while(u)
                        {
                            SDL_WaitEvent(&event);
                            switch(event.type)
                            {
                            case SDL_MOUSEMOTION:
                                if(event.motion.x>position_back.x&&event.motion.x<position_back.x+85&&event.motion.y>position_back.y&&event.motion.y<position_back.y+85)
                                    z=1;
                                else  if(event.motion.x<position_back.x||event.motion.x>position_back.x+85||event.motion.y<position_back.y||event.motion.y>position_back.y+85)
                                    z=2;
                                break;
                            case SDL_MOUSEBUTTONDOWN:
                                if(event.button.button==SDL_BUTTON_LEFT)
                                {
                                    if(event.button.x>position_back.x&&event.button.x<position_back.x+85&&event.button.y>position_back.y&&event.button.y<position_back.y+85)
                                        u=0;
                                }
                                break;
                            }
                            if(z==1)
                                SDL_BlitSurface(back_story,NULL,ecran,&position_story);
                            else if(z!=1)
                            {
                                SDL_BlitSurface(image_story,NULL,ecran,&position_story);
                            }
                            SDL_Flip(ecran);

                        }
                    }

                }
                break;
            case SDL_MOUSEMOTION:
                if(touch.motion.x>position_setting[1].x && touch.motion.x<position_setting[1].x+542 && touch.motion.y>position_setting[1].y && touch.motion.y<position_setting[1].y+108)
                    b=1;
                else if(touch.motion.x>position_setting[2].x && touch.motion.x<position_setting[2].x+554 && touch.motion.y>position_setting[2].y && touch.motion.y<position_setting[2].y+117)
                    b=2;
                else if(touch.motion.x>position_setting[3].x && touch.motion.x<position_setting[3].x+542 && touch.motion.y>position_setting[3].y && touch.motion.y<position_setting[3].y+120)
                    b=3;

                else if(touch.motion.x>position_setting[4].x && touch.motion.x<position_setting[4].x+500 && touch.motion.y>position_setting[4].y && touch.motion.y<position_setting[4].y+102)
                    b=4;
                if(touch.motion.x>position_setting[5].x && touch.motion.x<position_setting[5].x+82 && touch.motion.y>position_setting[5].y && touch.motion.y<position_setting[5].y+84)
                    pos[0]=5;
                else if(touch.motion.x>position_setting[6].x && touch.motion.x<position_setting[6].x+83 && touch.motion.y>position_setting[6].y && touch.motion.y<position_setting[6].y+84)
                    pos[1]=6;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (touch.button.button==SDL_BUTTON_LEFT)
                {
                    if(touch.button.x>position_setting[1].x && touch.button.x<position_setting[1].x+542 && touch.button.y>position_setting[1].y && touch.button.y<position_setting[1].y+108)
                        b=1;
                    else if(touch.button.x>position_setting[2].x && touch.button.x<position_setting[2].x+554 && touch.button.y>position_setting[2].y && touch.button.y<position_setting[2].y+117)
                    {

                        SDL_BlitSurface(image_story,NULL,ecran,&position_story);
                        SDL_Flip(ecran);
                        SDL_Event event;
                        u=1;
                        while(u)
                        {
                            SDL_WaitEvent(&event);
                            switch(event.type)
                            {
                            case SDL_MOUSEMOTION:
                                if(event.motion.x>position_back.x&&event.motion.x<position_back.x+85&&event.motion.y>position_back.y&&event.motion.y<position_back.y+85)
                                    z=1;
                                else  if(event.motion.x<position_back.x||event.motion.x>position_back.x+85||event.motion.y<position_back.y||event.motion.y>position_back.y+85)
                                    z=2;
                                break;
                            case SDL_MOUSEBUTTONDOWN:
                                if(event.button.button==SDL_BUTTON_LEFT)
                                {
                                    if(event.button.x>position_back.x&&event.button.x<position_back.x+85&&event.button.y>position_back.y&&event.button.y<position_back.y+85)
                                        u=0;
                                }
                                break;
                            }
                            if(z==1)
                                SDL_BlitSurface(back_story,NULL,ecran,&position_story);
                            else if(z!=1)
                            {
                                SDL_BlitSurface(image_story,NULL,ecran,&position_story);
                            }
                            SDL_Flip(ecran);

                        }
                    }
                    else if(touch.button.x>position_setting[3].x && touch.button.x<position_setting[3].x+542 && touch.button.y>position_setting[3].y && touch.button.y<position_setting[3].y+120)
                    {
                        b=3;
                        ecran =SDL_GetVideoSurface();
                        Uint32 flags        =(ecran->flags^SDL_FULLSCREEN);
                        ecran =SDL_SetVideoMode(0,0,0, flags);
                    }
                    else if(touch.button.x>position_setting[4].x && touch.button.x<position_setting[4].x+500 && touch.button.y>position_setting[4].y && touch.button.y<position_setting[4].y+102)
                        suit=0;
                    if(touch.button.x>position_setting[5].x && touch.button.x<position_setting[5].x+82 && touch.button.y>position_setting[5].y && touch.button.y<position_setting[5].y+84)
                    {
                        (*k)--;
                        pos[0]=5;
                    }
                    else if(touch.button.x>position_setting[6].x && touch.button.x<position_setting[6].x+83 && touch.button.y>position_setting[6].y && touch.button.y<position_setting[6].y+84)
                    {
                        (*k)++;
                        pos[1]=6;
                    }

                    break;

                }
            }
        }
        if(a!=b)
        {
            Mix_PlayChannel(1, son, 0);//Joue
            a=b;
        }

        if (b>4)
            b=1;
        if(b<1)
            b=4;

        if((*k)>10)
            (*k)=10;
        else if((*k)<1)
            (*k)=1;

        Mix_VolumeChunk(son, MIX_MAX_VOLUME/(10/(*k))); //Mettre un volume pour ce wav
        Mix_VolumeMusic(MIX_MAX_VOLUME /(10/(*k)));


        for(i=0; i<7; i++)
        {
            SDL_BlitSurface(option_setting[i],NULL,ecran,&position_setting[i]);
        }
        SDL_BlitSurface(option_setting[b],NULL,ecran,&position_setting[b]);
        for (i = 0; i < 2; i++)
        {
            if(pos[i]>4&&pos[i]<7)
            {
                SDL_BlitSurface(option_setting[pos[i]],NULL,ecran,&position_setting[pos[i]]);
                SDL_BlitSurface(option_setting[pos[i]],NULL,ecran,&position_setting[pos[i]]);
            }

            pos[i]=0;
        }
        SDL_Flip(ecran);

    }
    for (int i = 0; i < 7; ++i)
    {
        SDL_FreeSurface(option_setting[i]);
    }
}
void exit_game(SDL_Surface *ecran,Mix_Music *musique,Mix_Chunk *son,int *k,int *continuer)
{
    int suit =1,a=0,i,z;
    SDL_Surface *option_exit[3]= {NULL};
    SDL_Rect positionexit[3];

    positionexit[0].x=0;
    positionexit[0].y=0;
    positionexit[1].x=98;
    positionexit[1].y=306;
    positionexit[2].x=444;
    positionexit[2].y=312;
    Getf(f);

    option_exit[0]=IMG_Load("Image/menu-exit.png");
    option_exit[1]=IMG_Load("Image/bouton-yes.png");
    option_exit[2]=IMG_Load("Image/bouton-no.png");

    for(i=0; i<3; i++)
    {
        SDL_BlitSurface(option_exit[i],NULL,ecran,&positionexit[i]);
    }
    SDL_Flip(ecran);

    SDL_Event touch;

    while(suit)
    {
        if(f!=NULL)
        {
            exprev=ex[0];
            exprevb=ex[1];
            arduinoReadDataEx(ex);


            if(ex[0]==0 && exprev!=0)
            {

                a--;
            }
            if(ex[0]==2 && exprev!=2)
            {
                a++;
            }

            if(ex[1]==1 && exprevb!=1)
            {
                if(a==1)
                {
                    *continuer=0;
                    suit=0;
                }
                else
                {
                    suit=0;
                }
            }
        }

        if(f==NULL)
        {
            SDL_WaitEvent(&touch);
        }

        switch(touch.type)
        {
        case SDL_MOUSEMOTION:
            if(touch.motion.x>positionexit[1].x&&touch.motion.x<positionexit[1].x+213&&touch.motion.y>positionexit[1].y&&touch.motion.y<positionexit[1].y+87)
            {
                a=1;

            }
            else if(touch.motion.x>positionexit[2].x&&touch.motion.x<positionexit[2].x+217&&touch.motion.y>positionexit[2].y&&touch.motion.y<positionexit[2].y+79)
            {
                a=2;

            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (touch.button.button==SDL_BUTTON_LEFT)
            {
                if(touch.button.x>positionexit[1].x&&touch.button.x<positionexit[1].x+213&&touch.button.y>positionexit[1].y&&touch.button.y<positionexit[1].y+87)
                {
                    *continuer=0;
                    suit=0;
                }
                else if(touch.button.x>positionexit[2].x&&touch.button.x<positionexit[2].x+213&&touch.button.y>positionexit[2].y&&touch.button.y<positionexit[2].y+79)
                    suit=0;
            }
            break;

        case SDL_KEYDOWN:
            switch(touch.key.keysym.sym)
            {
            case SDLK_LEFT:
                a--;
                break;

            case SDLK_RIGHT:
                a++;
                break;

            case SDLK_RETURN:
                if(a==1)
                {
                    *continuer=0;
                    suit=0;
                }
                else
                {
                    suit=0;
                }
                break;
            }
            break;
        }
        if(z!=a)
        {
            Mix_PlayChannel(1, son, 0);//Joue
            z=a;
        }
        if(a>2)
            a=1;
        else if(a<1)
            a=2;

        SDL_BlitSurface(option_exit[0],NULL,ecran,&positionexit[0]);

        if(a>0&&a<3)
        {
            SDL_BlitSurface(option_exit[a],NULL,ecran,&positionexit[a]);
        }

        SDL_Flip(ecran);

    }
    for (int i = 0; i < 3; ++i)
    {
        SDL_FreeSurface(option_exit[i]);
    }

}

