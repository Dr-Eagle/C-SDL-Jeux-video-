#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "BgCam.h"
#include <math.h>


void initialiser_bg_multi(Background b[])
{

    b[0].position.x=0;
    b[0].position.y=0;
    b[1].position.x=0;
    b[1].position.y=0;

    b[0].position.w=4222;
    b[0].position.h=2354;
    b[1].position.w=4222;
    b[1].position.h=2354;


    b[0].stage=IMG_Load("Image/multiplayer/map.png");
    b[1].stage=IMG_Load("Image/multiplayer/stage1.png");

    printf("bg multi initialise\n");
}

void initialiser_cam_multi(Camera c[])
{
    c[0].position_cam.h=300;
    c[0].position_cam.w=800;

    c[1].position_cam.h=300;
    c[1].position_cam.w=800;

    c[0].position_cam.x=750;
    c[0].position_cam.y=100;

    c[1].position_cam.x=750;
    c[1].position_cam.y=100;

    c[0].position_ecran.x=0;
    c[0].position_ecran.y=0;
    c[1].position_ecran.x=0;
    c[1].position_ecran.y=300;


    printf("camera initialisee\n");
}

void scrolling_multi(Camera c[],SDL_Surface *ecran,SDL_Surface *bg)
{
    SDL_BlitSurface(bg,&c[0].position_cam, ecran,&c[0].position_ecran);
    SDL_BlitSurface(bg,&c[1].position_cam, ecran,&c[1].position_ecran);
}

void deplacement_camera_multi1(Camera *c,int tab[],float *vitesse,SDL_Rect position_bg,int *etat_voiture, int angle,int angle_gauche,int indice_voiture,int coll_boss, int coll_map)
{
    if(tab[0]==1&&!coll_boss&&!coll_map)
    {
        if(indice_voiture>=0&&indice_voiture<4)
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle_gauche)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=4&&indice_voiture<8)
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle_gauche)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=8&&indice_voiture<12)
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle)*M_PI/180)*(*vitesse);
        }
        else
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle)*M_PI/180)*(*vitesse);
        }

        *etat_voiture=1;
        //printf("camera deplacee left\n");
    }
    if(tab[1]==1&&!coll_boss&&!coll_map)
    {
        if(indice_voiture>=0&&indice_voiture<4)
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle_gauche)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=4&&indice_voiture<8)
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle_gauche)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=8&&indice_voiture<12)
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle)*M_PI/180)*(*vitesse);
        }
        else
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle)*M_PI/180)*(*vitesse);
        }

        *etat_voiture=1;
        //printf("camera deplacee right\n");
    }
    if(tab[2]==1&&!coll_boss&&!coll_map)
    {
        if(indice_voiture>=0&&indice_voiture<4)
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=4&&indice_voiture<8)
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=8&&indice_voiture<12)
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x-=tan((angle)*M_PI/180)*(*vitesse);
        }
        else
        {

            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle_gauche)*M_PI/180)*(*vitesse);
        }

        *etat_voiture=1;
        //printf("camera deplacee up\n");
    }
    if(tab[3]==1&&!coll_boss&&!coll_map)
    {
        if(indice_voiture>=0&&indice_voiture<4)
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=4&&indice_voiture<8)
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=8&&indice_voiture<12)
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x+=tan((angle)*M_PI/180)*(*vitesse);
        }
        else
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle_gauche)*M_PI/180)*(*vitesse);

        }

        *etat_voiture=1;
        //printf("camera deplacee down\n");
    }

    if(c->position_cam.x>position_bg.w-800)
        c->position_cam.x=position_bg.w-800;
    if(c->position_cam.x<0)
        c->position_cam.x=0;
    if(c->position_cam.y>position_bg.h-300)
        c->position_cam.y=position_bg.h-300;
    if(c->position_cam.y<0)
        c->position_cam.y=0;



}

void deplacement_camera_multi2(Camera *c,int tab[],float *vitesse,SDL_Rect position_bg,int *etat_voiture, int angle,int angle_gauche,int indice_voiture,int coll_boss, int coll_map)
{

    if(tab[6]==1&&!coll_boss&&!coll_map)
    {
        if(indice_voiture>=0&&indice_voiture<4)
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle_gauche)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=4&&indice_voiture<8)
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle_gauche)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=8&&indice_voiture<12)
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle)*M_PI/180)*(*vitesse);
        }
        else
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle)*M_PI/180)*(*vitesse);
        }

        *etat_voiture=1;
        //printf("camera deplacee left\n");
    }
    if(tab[7]==1&&!coll_boss&&!coll_map)
    {
        if(indice_voiture>=0&&indice_voiture<4)
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle_gauche)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=4&&indice_voiture<8)
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle_gauche)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=8&&indice_voiture<12)
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle)*M_PI/180)*(*vitesse);
        }
        else
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle)*M_PI/180)*(*vitesse);
        }

        *etat_voiture=1;
        //printf("camera deplacee right\n");
    }
    if(tab[8]==1&&!coll_boss&&!coll_map)
    {
        if(indice_voiture>=0&&indice_voiture<4)
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=4&&indice_voiture<8)
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=8&&indice_voiture<12)
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x-=tan((angle)*M_PI/180)*(*vitesse);
        }
        else
        {

            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle_gauche)*M_PI/180)*(*vitesse);
        }

        *etat_voiture=1;
        //printf("camera deplacee up\n");
    }
    if(tab[9]==1&&!coll_boss&&!coll_map)
    {
        if(indice_voiture>=0&&indice_voiture<4)
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=4&&indice_voiture<8)
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=8&&indice_voiture<12)
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x+=tan((angle)*M_PI/180)*(*vitesse);
        }
        else
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle_gauche)*M_PI/180)*(*vitesse);

        }

        *etat_voiture=1;
        //printf("camera deplacee down\n");
    }

    if(c->position_cam.x>position_bg.w-800)
        c->position_cam.x=position_bg.w-800;
    if(c->position_cam.x<0)
        c->position_cam.x=0;
    if(c->position_cam.y>position_bg.h-300)
        c->position_cam.y=position_bg.h-300;
    if(c->position_cam.y<0)
        c->position_cam.y=0;

}



void initialiser_Background(Background *b,int stage)
{
    b->position.x=0;
    b->position.y=0;

    SDL_Surface* temp=NULL;

    char nom[30];
    sprintf(nom,"Image/stage%d",stage+1);
    strcat(nom,".png");

    temp=IMG_Load(nom);
    b->stage=SDL_DisplayFormat(temp);

    SDL_FreeSurface(temp);

    sprintf(nom,"Image/mini_map/s-%d.png",stage+1);
    b->mini_map=IMG_Load(nom);
    b->position_mini.x=650;
    b->position_mini.y=500;

    if(stage==0)
    {
        b->position.w=6435;
        b->position.h=5304;

        b->position_mini.w=114;
        b->position_mini.h=94;
    }
    else if(stage==1)
    {
        b->position.w=6956;
        b->position.h=6220;

        b->position_mini.w=114;
        b->position_mini.h=94;
    }
    else if(stage==2)
    {
        b->position.w=16255;
        b->position.h=7970;

        b->position_mini.w=114;
        b->position_mini.h=56;
    }
    else if(stage==3)
    {
        b->position.w=10060;
        b->position.h=5304;

        b->position_mini.w=114;
        b->position_mini.h=56;
    }
    else if(stage==4)
    {
        b->position.w=11359;
        b->position.h=5990;

        b->position_mini.w=114;
        b->position_mini.h=56;
    }
    printf("bg initialise\n");
}


void initialiser_camera(Camera *c,SDL_Rect position_bg,int stage)
{

    c->position_cam.h=600;
    c->position_cam.w=800;
    if(stage==0)
    {
        c->position_cam.x=5420;
        c->position_cam.y=0;

        printf("camera stage 1 initialisee\n");
    }
    else if(stage==1)
    {
        c->position_cam.x=5050;
        c->position_cam.y=235;

        printf("camera stage 2 initialisee\n");
    }
    else if(stage==2)
    {
        c->position_cam.x=13141;
        c->position_cam.y=3154;

        printf("camera stage 3 initialisee\n");

    }
    else if(stage==3)
    {
        c->position_cam.x=2700;
        c->position_cam.y=6000;

        printf("camera stage 4 initialisee\n");

    }
    else if(stage==4)
    {
        c->position_cam.x=3125;
        c->position_cam.y=6150;

        printf("camera stage 5 initialisee\n");
    }


}


void afficher_camera(Camera c,SDL_Surface *ecran,Background b)
{
    SDL_BlitSurface(b.stage,&c.position_cam, ecran,&b.position);
    //printf("camera affichee\n");
}

void deplacement_camera(Camera *c,int tab[],float *vitesse,SDL_Rect position_bg,int *etat_voiture, int angle,int angle_gauche,int indice_voiture,int coll_boss, int coll_map)
{
    if(tab[0]==1&&!coll_boss&&!coll_map)
    {
        if(indice_voiture>=0&&indice_voiture<4)
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle_gauche)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=4&&indice_voiture<8)
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle_gauche)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=8&&indice_voiture<12)
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle)*M_PI/180)*(*vitesse);
        }
        else
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle)*M_PI/180)*(*vitesse);
        }

        *etat_voiture=1;
        //printf("camera deplacee left\n");
    }
    if(tab[1]==1&&!coll_boss&&!coll_map)
    {
        if(indice_voiture>=0&&indice_voiture<4)
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle_gauche)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=4&&indice_voiture<8)
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle_gauche)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=8&&indice_voiture<12)
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle)*M_PI/180)*(*vitesse);
        }
        else
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle)*M_PI/180)*(*vitesse);
        }

        *etat_voiture=1;
        //printf("camera deplacee right\n");
    }
    if(tab[2]==1&&!coll_boss&&!coll_map)
    {
        if(indice_voiture>=0&&indice_voiture<4)
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=4&&indice_voiture<8)
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=8&&indice_voiture<12)
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x-=tan((angle)*M_PI/180)*(*vitesse);
        }
        else
        {

            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle_gauche)*M_PI/180)*(*vitesse);
        }

        *etat_voiture=1;
        //printf("camera deplacee up\n");
    }
    if(tab[3]==1&&!coll_boss&&!coll_map)
    {
        if(indice_voiture>=0&&indice_voiture<4)
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x-=tan((angle)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=4&&indice_voiture<8)
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle)*M_PI/180)*(*vitesse);
        }
        else if(indice_voiture>=8&&indice_voiture<12)
        {
            c->position_cam.y+=*vitesse;
            c->position_cam.x+=tan((angle)*M_PI/180)*(*vitesse);
        }
        else
        {
            c->position_cam.y-=*vitesse;
            c->position_cam.x+=tan((angle_gauche)*M_PI/180)*(*vitesse);

        }

        *etat_voiture=1;
        //printf("camera deplacee down\n");
    }

    if(c->position_cam.x>position_bg.w-800)
        c->position_cam.x=position_bg.w-800;
    if(c->position_cam.x<0)
        c->position_cam.x=0;
    if(c->position_cam.y>position_bg.h-600)
        c->position_cam.y=position_bg.h-600;
    if(c->position_cam.y<0)
        c->position_cam.y=0;


}


void afficher_minimap(SDL_Rect position_cam,SDL_Rect position_player,Background b,SDL_Surface *ecran,int couleur_player,int stage,SDL_Rect position_boss)
{
    SDL_Rect position_repere, pos_boss;
    char nom[30];
    float rapportx,rapporty;
    SDL_Surface *point=NULL,*boss;
    sprintf(nom,"Image/mini_map/c%d.png",couleur_player);

    point= IMG_Load(nom);
    rapportx=b.position.w/(b.position_mini.w);
    rapporty=b.position.h/(b.position_mini.h);


    if(stage==0)
    {
        position_repere.x=b.position_mini.x+((position_cam.x+position_player.x)/rapportx)-18;
        position_repere.y=b.position_mini.y+((position_cam.y+position_player.y)/rapporty)-15;
    }
    else if(stage==1)
    {
        position_repere.x=b.position_mini.x+((position_cam.x+position_player.x)/rapportx)-18;
        position_repere.y=b.position_mini.y+((position_cam.y+position_player.y)/rapporty)-12;
    }
    else if(stage==2)
    {
        position_repere.x=b.position_mini.x+((position_cam.x+position_player.x)/rapportx)-18;
        position_repere.y=b.position_mini.y+((position_cam.y+position_player.y)/rapporty)-15;
    }
    else if(stage==3)
    {
        position_repere.x=b.position_mini.x+((position_cam.x+position_player.x)/rapportx)-20;
        position_repere.y=b.position_mini.y+((position_cam.y+position_player.y)/rapporty)-15;
    }
    else
    {
        position_repere.x=b.position_mini.x+((position_cam.x+position_player.x)/rapportx)-20;
        position_repere.y=b.position_mini.y+((position_cam.y+position_player.y)/rapporty)-15;

        pos_boss.x=b.position_mini.x+(position_boss.x/rapportx)-20;
        pos_boss.y=b.position_mini.y+(position_boss.y/rapporty)-15;

        boss=IMG_Load("Image/mini_map/cn.png");
    }

    SDL_BlitSurface(b.mini_map,NULL,ecran,&b.position_mini);
    SDL_BlitSurface(point,NULL,ecran,&position_repere);
    if(stage==4)
    {
        SDL_BlitSurface(boss,NULL,ecran,&pos_boss);
        SDL_FreeSurface(boss);
    }


    SDL_FreeSurface(point);

}
