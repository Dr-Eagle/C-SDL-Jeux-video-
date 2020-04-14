#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "Player.h"
#include "Collision.h"
//#define M_PI	3.1415926535897932384626433832795

void initialiser_multi(Player p[])
{
    char nom[50];
    int i,j;

    for (int j = 0; j < 2; ++j)
    {
        p[j].v.angle=60;
        p[j].v.angle_gauche=120;
        p[j].v.vitesse=0;
        p[j].v.direction=4;
        p[j].v.etat_voiture=0;
        p[j].v.nombre_de_turbo=3;
        p[j].v.turbo=0;
        p[j].v.temps_turbo=0;
        p[j].v.delai_turbo=0;
        p[j].v.autorisation_turbo=1;
        p[j].pv=100;
        p[j].gagner=0;
        p[j].game_over=0;

        p[j].son.son_voiture=Mix_LoadMUS("Son/voiture.mp3");

        p[j].v.indice_voiture=p[j].v.direction;

        for (int i = 1; i <= 16; ++i)
        {
            sprintf(nom,"Image/multiplayer/voiture%d/%d",p[j].v.couleur,i);
            strcat(nom,".png");
            p[j].v.deplacement[i-1]=IMG_Load(nom);
        }
        for (int i = 1; i <= 16; ++i)
        {
            sprintf(nom,"Image/multiplayer/turbo/voiture%d/%d",p[j].v.couleur,i);
            strcat(nom,".png");
            p[j].v.deplacement_turbo[i-1]=IMG_Load(nom);
        }
    }

    p[0].v.position.x=323;
    p[0].v.position.y=104;

    p[1].v.position.x=360;
    p[1].v.position.y=136;
    printf("mutiplayer initialiser\n");
}

void afficher_voiture_multi(SDL_Surface *ecran,Player p[],SDL_Rect position_camera1,SDL_Rect position_camera2)
{
    SDL_Rect position1,position2,position_ecran1,position_ecran2;

    position_ecran1.x=position_camera2.x- position_camera1.x + p[1].v.position.x;
    position_ecran1.y=position_camera2.y- position_camera1.y + p[1].v.position.y;

    position_ecran2.x=position_camera1.x- position_camera2.x + p[0].v.position.x;
    position_ecran2.y=position_camera1.y- position_camera2.y + p[0].v.position.y;

    position1.x=position_camera1.x+p[0].v.position.x;
    position1.y=position_camera1.y+p[0].v.position.y;

    position2.x=position_camera2.x+p[1].v.position.x;
    position2.y=position_camera2.y+p[1].v.position.y;



    position_ecran2.y+=300;
    if(p[0].v.turbo==0)
    {
        SDL_BlitSurface(p[0].v.deplacement[p[0].v.indice_voiture],NULL,ecran,&p[0].v.position);
        if(position_ecran2.y>300)
            SDL_BlitSurface(p[0].v.deplacement[p[0].v.indice_voiture],NULL,ecran,&position_ecran2);
    }
    else
    {
        SDL_BlitSurface(p[0].v.deplacement_turbo[p[0].v.indice_voiture],NULL,ecran,&p[0].v.position);
        if(position_ecran2.y>300)
            SDL_BlitSurface(p[0].v.deplacement_turbo[p[0].v.indice_voiture],NULL,ecran,&position_ecran2);
    }
    position_ecran2.y-=300;

    p[1].v.position.y+=300;
    if(p[1].v.turbo==0)
    {
        SDL_BlitSurface(p[1].v.deplacement[p[1].v.indice_voiture],NULL,ecran,&p[1].v.position);
        if(position_ecran1.y<300-109)
            SDL_BlitSurface(p[1].v.deplacement[p[1].v.indice_voiture],NULL,ecran,&position_ecran1);
    }
    else
    {
        SDL_BlitSurface(p[1].v.deplacement_turbo[p[1].v.indice_voiture],NULL,ecran,&p[1].v.position);
        if(position_ecran1.y<300-109)
            SDL_BlitSurface(p[1].v.deplacement_turbo[p[1].v.indice_voiture],NULL,ecran,&position_ecran1);
    }
    p[1].v.position.y-=300;


}

void modifier_score_col_multi(int collision,Player *p)
{
    if(collision==1)
    {
        p->pv-=0.001;
        if(p->pv<0)
        {
            p->pv=0;
        }
        //printf("point de vie modifie collision\n");
    }
}

void prochaine_position2(SDL_Rect *nouvelle_position,int tab[],Voiture *v)
{

    if(tab[6]==1)
    {

        if(v->indice_voiture>=0&&v->indice_voiture<4)
        {
            nouvelle_position->y-=v->vitesse;
            nouvelle_position->x+=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
        }
        else if(v->indice_voiture>=4&&v->indice_voiture<8)
        {
            nouvelle_position->y+=v->vitesse;
            nouvelle_position->x-=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
        }
        else if(v->indice_voiture>=8&&v->indice_voiture<12)
        {
            nouvelle_position->y+=v->vitesse;
            nouvelle_position->x-=tan((v->angle)*M_PI/180)*(v->vitesse);
        }
        else
        {
            nouvelle_position->y-=v->vitesse;
            nouvelle_position->x+=tan((v->angle)*M_PI/180)*(v->vitesse);
        }

    }
    if(tab[7]==1)
    {

        if(v->indice_voiture>=0&&v->indice_voiture<4)
        {
            nouvelle_position->y+=v->vitesse;
            nouvelle_position->x-=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
        }
        else if(v->indice_voiture>=4&&v->indice_voiture<8)
        {
            nouvelle_position->y-=v->vitesse;
            nouvelle_position->x+=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
        }
        else if(v->indice_voiture>=8&&v->indice_voiture<12)
        {
            nouvelle_position->y-=v->vitesse;
            nouvelle_position->x+=tan((v->angle)*M_PI/180)*(v->vitesse);
        }
        else
        {
            nouvelle_position->y+=v->vitesse;
            nouvelle_position->x-=tan((v->angle)*M_PI/180)*(v->vitesse);
        }

    }
    if(tab[8]==1)
    {

        if(v->indice_voiture>=0&&v->indice_voiture<4)
        {
            nouvelle_position->y-=v->vitesse;
            nouvelle_position->x+=tan((v->angle)*M_PI/180)*(v->vitesse);
        }
        else if(v->indice_voiture>=4&&v->indice_voiture<8)
        {
            nouvelle_position->y+=v->vitesse;
            nouvelle_position->x-=tan((v->angle)*M_PI/180)*(v->vitesse);
        }
        else if(v->indice_voiture>=8&&v->indice_voiture<12)
        {
            nouvelle_position->y-=v->vitesse;
            nouvelle_position->x-=tan((v->angle)*M_PI/180)*(v->vitesse);
        }
        else
        {

            nouvelle_position->y+=v->vitesse;
            nouvelle_position->x-=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
        }

    }
    if(tab[9]==1)
    {
        if(v->indice_voiture>=0&&v->indice_voiture<4)
        {
            nouvelle_position->y+=v->vitesse;
            nouvelle_position->x-=tan((v->angle)*M_PI/180)*(v->vitesse);
        }
        else if(v->indice_voiture>=4&&v->indice_voiture<8)
        {
            nouvelle_position->y-=v->vitesse;
            nouvelle_position->x+=tan((v->angle)*M_PI/180)*(v->vitesse);
        }
        else if(v->indice_voiture>=8&&v->indice_voiture<12)
        {
            nouvelle_position->y+=v->vitesse;
            nouvelle_position->x+=tan((v->angle)*M_PI/180)*(v->vitesse);
        }
        else
        {
            nouvelle_position->y-=v->vitesse;
            nouvelle_position->x+=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);

        }

    }

}


void afficher_score_multi(Player p[],SDL_Surface *ecran)
{
    char Nom[2][30]= {"",""},Pv[2][30]= {"",""},Vitsse[2][30]= {"",""};

    int i;

    SDL_Surface *nom[2]= {NULL},*pv[2]= {NULL},*vitesse[2]= {NULL};
    SDL_Rect position_nom[2],position_pv[2],position_vitesse[2];

    position_nom[0].x=90;
    position_nom[0].y=20;
    position_pv[0].x=380;
    position_pv[0].y=20;
    position_vitesse[0].x=10;
    position_vitesse[0].y=55;

    position_nom[1].x=90;
    position_nom[1].y=20+300;
    position_pv[1].x=380;
    position_pv[1].y=20+300;
    position_vitesse[1].x=10;
    position_vitesse[1].y=55+300;

    TTF_Font *police=NULL,*police_vit;
    police=TTF_OpenFont("Police/arial.ttf",18);
    police_vit=TTF_OpenFont("Police/Heroes Legend.ttf",10);
    SDL_Color couleur[2];
    SDL_Color couleur_score1= {255,0,0};
    SDL_Color couleur_score2= {0,255,0};

    for (int i = 0; i < 2; ++i)
    {
        if(p[i].v.couleur==3)
        {
            couleur[i].r=204;
            couleur[i].g=175;
            couleur[i].b=0;

        }
        else if(p[i].v.couleur==4)
        {
            couleur[i].r=217;
            couleur[i].g=1;
            couleur[i].b=27;
        }
        else if(p[i].v.couleur==5)
        {
            couleur[i].r=116;
            couleur[i].g=208;
            couleur[i].b=241;
        }
        else if(p[i].v.couleur==6)
        {
            couleur[i].r=22;
            couleur[i].g=184;
            couleur[i].b=76;
        }
        else
        {
            couleur[i].r=255;
            couleur[i].g=255;
            couleur[i].b=0;
        }
        sprintf(Vitsse[i],"Vitsse:%.2f km/h",p[i].v.vitesse*10);
        sprintf(Pv[i],"Pv:%d",p[i].pv);
        strcpy(Nom[i],p[i].pseudo);

        if (p[i].pv<50)
        {
            pv[i]=TTF_RenderText_Blended(police,Pv[i],couleur_score1);
        }
        else
        {
            pv[i]=TTF_RenderText_Blended(police,Pv[i],couleur_score2);
        }
        if(p[i].v.vitesse>10)
        {
            vitesse[i]=TTF_RenderText_Solid(police_vit,Vitsse[i],couleur_score1);
        }
        else
        {
            vitesse[i]=TTF_RenderText_Solid(police_vit,Vitsse[i],couleur_score2);
        }

        nom[i]=TTF_RenderText_Solid(police,Nom[i],couleur[i]);

        SDL_BlitSurface(nom[i],NULL,ecran,&position_nom[i]);
        SDL_BlitSurface(pv[i],NULL,ecran,&position_pv[i]);
        SDL_BlitSurface(vitesse[i],NULL,ecran,&position_vitesse[i]);

        SDL_FreeSurface(vitesse[i]);
        SDL_FreeSurface(nom[i]);
        SDL_FreeSurface(pv[i]);
    }


    TTF_CloseFont(police);
    TTF_CloseFont(police_vit);

    //printf("score affiche\n");
}

void gagner_multi(Player p[],SDL_Rect position_camera,SDL_Rect position_camera2)
{
    SDL_Rect centre_voiture, centre_voiture2;
    int hauteur_voiture=181,largeur_voiture=109;

    centre_voiture.x=(position_camera.x+p[0].v.position.x)+(largeur_voiture/2);
    centre_voiture.y=(position_camera.y+p[0].v.position.y)+(largeur_voiture/2);

    centre_voiture2.x=(position_camera2.x+p[1].v.position.x)+(largeur_voiture/2);
    centre_voiture2.y=(position_camera2.y+p[1].v.position.y)+(largeur_voiture/2);

    if(centre_voiture.x>1493&&centre_voiture.x<1641&&centre_voiture.y>157&&centre_voiture.y<327)
    {
        p[0].gagner=1;
        printf("p1 a gagne\n");
    }
    else if(centre_voiture2.x>1493&&centre_voiture2.x<1641&&centre_voiture2.y>157&&centre_voiture2.y<327)
    {
        p[1].gagner=1;
        printf("p2 a gagne\n");
    }
    if(p[0].pv==0)
    {
        p[1].gagner=1;
    }
    else if(p[1].pv==0)
    {
        p[0].gagner=1;
    }

}

void animation_voiture_multi(Player p[],int tab[])
{
    int a=0,i;
    for (int i = 0; i < 4; ++i)
    {
        if(tab[i]==1)
        {
            a++;
        }
    }
    if(a!=0)
    {

        p[0].v.indice_voiture++;
        if(p[0].v.indice_voiture>p[0].v.direction+3)
        {
            p[0].v.indice_voiture=p[0].v.direction;
        }
    }
    a=0;
    for (int i = 6; i < 10; ++i)
    {
        if(tab[i]==1)
        {
            a++;
        }
    }
    if (a!=0)
    {
        p[1].v.indice_voiture++;
        if(p[1].v.indice_voiture>p[1].v.direction+3)
        {
            p[1].v.indice_voiture=p[1].v.direction;
        }
    }
}

void changer_image_voiture_multi(SDL_Surface *bg_collision,SDL_Rect position_camera,Player *p)
{
    int collision;
    SDL_Rect centre_voiture;
    centre_voiture.x=(position_camera.x+p->v.position.x)+(182/2);
    centre_voiture.y=(position_camera.y+p->v.position.y)+(109/2);
    collision=collision_tournant(bg_collision,centre_voiture);

    if(collision!=20)
    {
        p->v.direction=collision;
    }

}

void acceleration_turbo_multi(Player p[],int tab[])
{
    int i,a=0;

    for (int i = 0; i < 4; ++i)
    {
        if(tab[i]==1)
        {
            a++;
        }
    }
    if(p[0].v.autorisation_turbo==1)
    {
        if(tab[4]==1)
        {
            p[0].v.vitesse+=(15-p[0].v.vitesse);
        }
    }


    if(p[0].v.vitesse>13)
    {
        p[0].v.turbo=1;
    }
    else
        p[0].v.turbo=0;


    if(a>0)
    {
        if(p[0].v.vitesse<3)
        {
            p[0].v.vitesse+=0.1;
        }
        else
        {
            p[0].v.vitesse+=0.0001;
            if(p[0].v.vitesse>10&&p[0].v.turbo==0)
                p[0].v.vitesse=10;
        }
        if(p[0].v.vitesse>=15&&p[0].v.turbo==1)
        {
            p[0].v.vitesse=15;
        }

    }
    else
    {
        p[0].v.vitesse=0;
    }

    if(p[0].v.turbo==1)
    {
        p[0].v.temps_turbo++;
        if(p[0].v.temps_turbo>150)
        {
            p[0].v.vitesse=10;
            p[0].v.temps_turbo=0;
            p[0].v.autorisation_turbo=0;
        }
    }

    if(p[0].v.autorisation_turbo==0)
    {
        p[0].v.delai_turbo++;
        if(p[0].v.delai_turbo>300)
        {
            p[0].v.delai_turbo=0;
            p[0].v.autorisation_turbo=1;
        }
    }
    a=0;

    for (int i = 6; i < 10; ++i)
    {
        if(tab[i]==1)
        {
            a++;
        }
    }
    if(p[1].v.autorisation_turbo==1)
    {
        if(tab[10]==1)
        {
            p[1].v.vitesse+=(15-p[1].v.vitesse);
        }
    }


    if(p[1].v.vitesse>13)
    {
        p[1].v.turbo=1;
    }
    else
        p[1].v.turbo=0;


    if(a>0)
    {
        if(p[1].v.vitesse<3)
        {
            p[1].v.vitesse+=0.1;
        }
        else
        {
            p[1].v.vitesse+=0.0001;
            if(p[1].v.vitesse>10&&p[1].v.turbo==0)
                p[1].v.vitesse=10;
        }
        if(p[1].v.vitesse>=15&&p[1].v.turbo==1)
        {
            p[1].v.vitesse=15;
        }

    }
    else
    {
        p[1].v.vitesse=0;
    }

    if(p[1].v.turbo==1)
    {
        p[1].v.temps_turbo++;
        if(p[1].v.temps_turbo>150)
        {
            p[1].v.vitesse=10;
            p[1].v.temps_turbo=0;
            p[1].v.autorisation_turbo=0;
        }
    }

    if(p[1].v.autorisation_turbo==0)
    {
        p[1].v.delai_turbo++;
        if(p[1].v.delai_turbo>300)
        {
            p[1].v.delai_turbo=0;
            p[1].v.autorisation_turbo=1;
        }
    }

}

void deplacer_voiture_multi1(Voiture *v,SDL_Rect position_camera,int tab[],SDL_Rect position_bg,int coll_boss, int coll_map)
{
    int a=0;

    if(position_camera.x==position_bg.w-800||position_camera.x==0||position_camera.y==0||position_camera.y==position_bg.h-300)
    {
        if(tab[0]==1&&!coll_boss&&!coll_map)
        {

            if(v->indice_voiture>=0&&v->indice_voiture<4)
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=4&&v->indice_voiture<8)
            {
                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=8&&v->indice_voiture<12)
            {
                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle)*M_PI/180)*(v->vitesse);
            }

            v->etat_voiture=1;


            //printf("voiture deplacee left\n");
        }
        if(tab[1]==1&&!coll_boss&&!coll_map)
        {

            if(v->indice_voiture>=0&&v->indice_voiture<4)
            {
                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=4&&v->indice_voiture<8)
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=8&&v->indice_voiture<12)
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else
            {
                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle)*M_PI/180)*(v->vitesse);
            }

            v->etat_voiture=1;


            //printf("voiture deplacee right\n");
        }
        if(tab[2]==1&&!coll_boss&&!coll_map)
        {

            if(v->indice_voiture>=0&&v->indice_voiture<4)
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=4&&v->indice_voiture<8)
            {
                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=8&&v->indice_voiture<12)
            {
                v->position.y-=v->vitesse;
                v->position.x-=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else
            {

                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
            }

            v->etat_voiture=1;

            //printf("voiture deplacee up\n");
        }
        if(tab[3]==1&&!coll_boss&&!coll_map)
        {
            if(v->indice_voiture>=0&&v->indice_voiture<4)
            {
                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=4&&v->indice_voiture<8)
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=8&&v->indice_voiture<12)
            {
                v->position.y+=v->vitesse;
                v->position.x+=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);

            }

            v->etat_voiture=1;

        }

        if(v->position.y>300-109)
        {
            v->position.y=300-109;
        }
        if(v->position.y<0)
        {
            v->position.y=0;
        }
        if(v->position.x<0)
        {
            v->position.x=0;
        }
        if(v->position.x>800-182)
        {
            v->position.x=800-182;
        }
    }

}
void deplacer_voiture_multi2(Voiture *v,SDL_Rect position_camera,int tab[],SDL_Rect position_bg,int coll_boss, int coll_map)
{
    int a=0;

    if(position_camera.x==position_bg.w-800||position_camera.x==0||position_camera.y==0||position_camera.y==position_bg.h-300)
    {
        if(tab[6]==1&&!coll_boss&&!coll_map)
        {

            if(v->indice_voiture>=0&&v->indice_voiture<4)
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=4&&v->indice_voiture<8)
            {
                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=8&&v->indice_voiture<12)
            {
                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle)*M_PI/180)*(v->vitesse);
            }

            v->etat_voiture=1;
            if(v->position.y>600-182)
            {
                v->position.y=600-182;
            }

            //printf("voiture deplacee left\n");
        }
        if(tab[7]==1&&!coll_boss&&!coll_map)
        {

            if(v->indice_voiture>=0&&v->indice_voiture<4)
            {
                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=4&&v->indice_voiture<8)
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=8&&v->indice_voiture<12)
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else
            {
                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle)*M_PI/180)*(v->vitesse);
            }

            v->etat_voiture=1;
            if(v->position.y<0)
            {
                v->position.y=0;
            }

            //printf("voiture deplacee right\n");
        }
        if(tab[8]==1&&!coll_boss&&!coll_map)
        {

            if(v->indice_voiture>=0&&v->indice_voiture<4)
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=4&&v->indice_voiture<8)
            {
                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=8&&v->indice_voiture<12)
            {
                v->position.y-=v->vitesse;
                v->position.x-=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else
            {

                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
            }

            v->etat_voiture=1;
            if(v->position.x<0)
            {
                v->position.x=0;
            }
            //printf("voiture deplacee up\n");
        }
        if(tab[9]==1&&!coll_boss&&!coll_map)
        {
            if(v->indice_voiture>=0&&v->indice_voiture<4)
            {
                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=4&&v->indice_voiture<8)
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=8&&v->indice_voiture<12)
            {
                v->position.y+=v->vitesse;
                v->position.x+=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);

            }

            v->etat_voiture=1;
            if(v->position.x>800-109)
            {
                v->position.x=800-109;
            }
        }
    }

}



void afficher_etat_turbo_multi(SDL_Surface *ecran,Player p[])
{
    SDL_Surface *vert=NULL;
    int h,w=20;
    SDL_Rect position,position2;
    position.x=800-30;
    position.y=600-200;

    position2.x=800-30;
    position2.y=80;



    if(p[0].v.autorisation_turbo==1)
    {
        h=150-p[0].v.temps_turbo;
        vert=SDL_CreateRGBSurface(SDL_HWSURFACE,w,h,32,0,0,0,0);
        SDL_FillRect(vert,NULL,SDL_MapRGB(ecran->format,0,255,0));
        SDL_BlitSurface(vert,NULL,ecran,&position2);

    }
    else
    {
        h=p[0].v.delai_turbo;
        if(h>150)
            h=150;
        vert=SDL_CreateRGBSurface(SDL_HWSURFACE,w,h,32,0,0,0,0);
        SDL_FillRect(vert,NULL,SDL_MapRGB(ecran->format,255,0,0));
        SDL_BlitSurface(vert,NULL,ecran,&position2);

    }

    if(p[1].v.autorisation_turbo==1)
    {
        h=150-p[1].v.temps_turbo;
        vert=SDL_CreateRGBSurface(SDL_HWSURFACE,w,h,32,0,0,0,0);
        SDL_FillRect(vert,NULL,SDL_MapRGB(ecran->format,0,255,0));
        SDL_BlitSurface(vert,NULL,ecran,&position);

    }
    else
    {
        h=p[1].v.delai_turbo;
        if(h>150)
            h=150;
        vert=SDL_CreateRGBSurface(SDL_HWSURFACE,w,h,32,0,0,0,0);
        SDL_FillRect(vert,NULL,SDL_MapRGB(ecran->format,255,0,0));
        SDL_BlitSurface(vert,NULL,ecran,&position);
        //SDL_FreeSurface(vert);
    }

}

void compte_a_rebour(int *jouer,SDL_Surface *ecran,temps *t)
{
    if(*jouer<1)
    {
        SDL_Surface *test[3]= {NULL};

        SDL_Rect position_test;
        position_test.x=0;
        position_test.y=0;


        test[0]=IMG_Load("Image/compte/1.png");
        test[1]=IMG_Load("Image/compte/2.png");
        test[2]=IMG_Load("Image/compte/3.png");


        for (int i = 0; i < 3; ++i)
        {
            SDL_BlitSurface(test[i],NULL,ecran,&position_test);
            SDL_Flip(ecran);
            SDL_Delay(1700);
        }

        for (int i = 0; i < 3; ++i)
        {
            SDL_FreeSurface(test[i]);
        }

        t->commencer+=(1700*3);
        (*jouer)++;
    }

}

void initialiser_player(Player *p)
{
    char nom[30];
    int i;

    p->v.vitesse=0;
    if(p->stage==0)
    {
        p->v.direction=4;
        p->score=200;
    }
    else if(p->stage==1)
    {
        p->v.direction=4;
    }
    else if(p->stage==2)
    {
        p->v.direction=12;
    }
    else if(p->stage==3)
    {
        p->v.direction=0;
    }
    else if(p->stage==4)
    {
        p->v.direction=0;
    }

    p->v.turbo=0;
    p->v.etat_voiture=0;
    p->v.nombre_de_turbo=3;
    p->v.temps_turbo=0;
    p->v.delai_turbo=0;
    p->v.autorisation_turbo=1;

    for (int i = 1; i <= 16; ++i)
    {
        sprintf(nom,"Image/voiture%d/%d",p->v.couleur,i);
        strcat(nom,".png");
        p->v.deplacement[i-1]=IMG_Load(nom);
    }
    for (int i = 1; i <= 16; ++i)
    {
        sprintf(nom,"Image/turbo/voiture%d/%d",p->v.couleur,i);
        strcat(nom,".png");
        p->v.deplacement_turbo[i-1]=IMG_Load(nom);
    }


    p->v.angle=60;
    p->v.angle_gauche=120;
    p->pv=100;
    p->gagner=0;
    p->game_over=0;

    p->son.son_voiture=Mix_LoadMUS("Son/voiture.mp3");
    p->son.son_horloge=Mix_LoadWAV("Son/tic-tac.wav");
    p->son.son_turbo=Mix_LoadWAV("Son/son-turbo.wav");
    p->son.son_collision=Mix_LoadWAV("Son/son-collision.wav");

    p->v.position.x=150;
    p->v.position.y=150;


    p->v.indice_voiture=p->v.direction;

    //strcpy(p->pseudo,"TOTO");
    printf("player initialise\n");

}



void initialiser_temps(temps *t)
{
    t->commencer=0;
    t->temps_stage2=0;
    t->temps_stage3=0;
    t->pause=0;
}

void temps_jeu(temps *t)
{
    t->commencer=SDL_GetTicks();
}
void compter_temps_stage2(temps *t)
{
    if(t->temps_stage3==0)
    {
        t->temps_stage2=SDL_GetTicks()-t->commencer;
    }
    else
    {
        t->temps_stage2=SDL_GetTicks()-t->temps_stage3-t->commencer;
    }

}
void compter_temps_stage3(temps *t)
{
    if(t->temps_stage2==0)
    {
        t->temps_stage3=SDL_GetTicks()-t->commencer;
    }
    else
    {
        t->temps_stage3=SDL_GetTicks()-t->temps_stage2-t->commencer;
    }
}
void pause(temps *t)
{
    t->pause=SDL_GetTicks();
}


void animation_voiture(Player *p,int tab[])
{
    int a=0,i;
    for (int i = 0; i < 4; ++i)
    {
        if(tab[i]==1)
        {
            a++;
        }
    }
    if(a!=0)
    {

        p->v.indice_voiture++;

        if(p->v.indice_voiture>(p->v.direction+3))
        {
            p->v.indice_voiture=p->v.direction;
        }
    }

}


int  charger_parti(char *nom_de_fichier,Player *player,char *pseudo)
{
    FILE *f=NULL;
    f=fopen(nom_de_fichier,"r");
    Player tmp[100];
    int i,a=0,nbre_joueur=0;
    i=0;
    while(!feof(f))
    {
        nbre_joueur=fscanf(f,"%s %d %d %d\n",tmp[i].pseudo,&tmp[i].score,&tmp[i].v.couleur,&tmp[i].stage);
        if(strcmp(pseudo,tmp[i].pseudo)==0)
        {

            strcpy(player->pseudo,tmp[i].pseudo);
            player->score=tmp[i].score;
            player->v.couleur=tmp[i].v.couleur;
            player->stage=tmp[i].stage;
            printf("joueur trouve\n");
            return 1;
        }
    }
    fclose(f);

    return 0;

}

void sauvegarder(char *nom_de_fichier,Player p)
{
    FILE *f=NULL;
    Player tmp[100];
    int i,a=0,nbre_joueur=0;
    f=fopen(nom_de_fichier,"r");
    nbre_joueur=0;
    while(!feof(f))
    {

        fscanf(f,"%s %d %d %d\n",tmp[nbre_joueur].pseudo,&tmp[nbre_joueur].score,&tmp[nbre_joueur].v.couleur,&tmp[nbre_joueur].stage);
        nbre_joueur++;

    }
    for (int i = 0; i < nbre_joueur; ++i)
    {
        if(strcmp(p.pseudo,tmp[i].pseudo)==0)
        {
            a++;
            tmp[i]=p;
            printf("joueur trouve\n");
        }
    }
    fclose(f);
    f=fopen(nom_de_fichier,"w");
    for (int i = 0; i < nbre_joueur; ++i)
    {
        fprintf(f,"%s %d %d %d\n",tmp[i].pseudo,tmp[i].score,tmp[i].v.couleur,tmp[i].stage);
    }
    fclose(f);
    if(a==0)
    {
        ajouter_joueur(nom_de_fichier,p);
        printf("joueur ajoute\n");
    }

}

void ajouter_joueur(char *nom_de_fichier,Player p)
{

    FILE *f=NULL;
    f=fopen(nom_de_fichier,"a");
    fprintf(f,"%s %d %d %d\n",p.pseudo,p.score,p.v.couleur,p.stage);
    fclose(f);
    printf("joueur ajoute\n");
}

int chercher_player(char *nom_de_fichier,Player p)
{

    int valider=0;
    Player tmp;
    FILE *f=NULL;
    f=fopen(nom_de_fichier,"r");
    while(!feof(f))
    {
        fscanf(f,"%s %d %d %d\n",tmp.pseudo,&tmp.score,&tmp.v.couleur,&tmp.stage);
        if(strcmp(p.pseudo,tmp.pseudo)==0)
        {
            valider=1;
            printf("joueur trouve\n");
        }
    }
    fclose(f);

    return valider;
}

void afficher_voiture(SDL_Surface *ecran,Player p)
{

    if(p.v.turbo==1)
    {
        SDL_BlitSurface(p.v.deplacement_turbo[p.v.indice_voiture],NULL,ecran,&p.v.position);
    }
    else
    {
        SDL_BlitSurface(p.v.deplacement[p.v.indice_voiture],NULL,ecran,&p.v.position);
    }

    //printf("voiture affichee\n");

}

void modifier_score_col(int collision,Player *p)
{
    if(collision==1)
    {
        p->pv-=1;
        if(p->pv<0)
        {
            p->pv=0;
        }
        //printf("point de vie modifie collision\n");
    }
}

void afficher_score(Player p,SDL_Surface *ecran)
{
    char Nom[30]="",Pv[30]="",Score[30]="",Vitsse[30]="",Stage[30]="";

    sprintf(Vitsse,"Vitsse:%.2f km/h",p.v.vitesse*10);
    sprintf(Stage,"Stage:  %d ",p.stage+1);
    sprintf(Pv,"Pv:%d",p.pv);
    sprintf(Score,"score:%d",p.score);
    strcpy(Nom,p.pseudo);
    //printf("%s %s %s\n", Pv,Score,Nom );
    SDL_Surface *score=NULL,*nom=NULL,*pv=NULL,*vitesse=NULL,*stage=NULL;
    SDL_Rect position_score,position_nom,position_pv,position_vitesse,position_stage;
    position_score.x=560;
    position_score.y=20;
    position_nom.x=90;
    position_nom.y=20;
    position_pv.x=380;
    position_pv.y=20;
    position_vitesse.x=10;
    position_vitesse.y=55;
    position_stage.x=10;
    position_stage.y=80;


    TTF_Font *police=NULL,*police_vit;
    police=TTF_OpenFont("Police/arial.ttf",30);
    police_vit=TTF_OpenFont("Police/Heroes Legend.ttf",10);
    SDL_Color couleur= {255,255,0};
    SDL_Color couleur_score1= {255,0,0};
    SDL_Color couleur_score2= {0,255,0};
    SDL_Color couleur_stage= {0,0,0};
    if(p.score<50)
    {
        score=TTF_RenderText_Blended(police,Score,couleur_score1);
    }
    else
    {
        score=TTF_RenderText_Blended(police,Score,couleur_score2);
    }
    if (p.pv<50)
    {
        pv=TTF_RenderText_Blended(police,Pv,couleur_score1);
    }
    else
    {
        pv=TTF_RenderText_Blended(police,Pv,couleur_score2);
    }
    if(p.v.vitesse>10)
    {
        vitesse=TTF_RenderText_Solid(police_vit,Vitsse,couleur_score1);
    }
    else
    {
        vitesse=TTF_RenderText_Solid(police_vit,Vitsse,couleur_score2);
    }

    nom=TTF_RenderText_Solid(police,Nom,couleur);
    stage=TTF_RenderText_Solid(police_vit,Stage,couleur_stage);

    SDL_BlitSurface(score,NULL,ecran,&position_score);
    SDL_BlitSurface(nom,NULL,ecran,&position_nom);
    SDL_BlitSurface(pv,NULL,ecran,&position_pv);
    SDL_BlitSurface(vitesse,NULL,ecran,&position_vitesse);
    SDL_BlitSurface(stage,NULL,ecran,&position_stage);


    SDL_FreeSurface(score);
    SDL_FreeSurface(vitesse);
    SDL_FreeSurface(nom);
    SDL_FreeSurface(pv);
    TTF_CloseFont(police);
    TTF_CloseFont(police_vit);

    //printf("score affiche\n");
}


void son_voiture(Player p,int k)
{

    Mix_AllocateChannels(32); //Allouer 32 canaux
    Mix_Volume(1, MIX_MAX_VOLUME/2); //Mettre à mi-volume le post 1
    Mix_PlayMusic(p.son.son_voiture, -1); //Jouer infiniment la musique
    Mix_VolumeMusic(MIX_MAX_VOLUME /(10/(k)));
    //printf(" son voiture\n");
}

void son_tic_tac(Player p,int k)
{
    Mix_AllocateChannels(32); //Allouer 32 canaux
    Mix_VolumeChunk(p.son.son_horloge, MIX_MAX_VOLUME/(10/(k))); //Mettre un volume pour ce wav
    Mix_PlayChannel(1,p.son.son_horloge,-1);
}

void son_turbo(Player p,int k)
{
    Mix_AllocateChannels(32); //Allouer 32 canaux
    Mix_VolumeChunk(p.son.son_turbo, MIX_MAX_VOLUME/(10/(k))); //Mettre un volume pour ce wav
    Mix_PlayChannel(1,p.son.son_turbo,0);
}

void son_collision(Player p,int k)
{
    Mix_AllocateChannels(32); //Allouer 32 canaux
    Mix_VolumeChunk(p.son.son_collision, MIX_MAX_VOLUME/(10/(k))); //Mettre un volume pour ce wav
    Mix_PlayChannel(1,p.son.son_collision,0);
}

void prochaine_position(SDL_Rect *nouvelle_position,int tab[],Voiture *v)
{

    if(tab[0]==1)
    {

        if(v->indice_voiture>=0&&v->indice_voiture<4)
        {
            nouvelle_position->y-=v->vitesse;
            nouvelle_position->x+=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
        }
        else if(v->indice_voiture>=4&&v->indice_voiture<8)
        {
            nouvelle_position->y+=v->vitesse;
            nouvelle_position->x-=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
        }
        else if(v->indice_voiture>=8&&v->indice_voiture<12)
        {
            nouvelle_position->y+=v->vitesse;
            nouvelle_position->x-=tan((v->angle)*M_PI/180)*(v->vitesse);
        }
        else
        {
            nouvelle_position->y-=v->vitesse;
            nouvelle_position->x+=tan((v->angle)*M_PI/180)*(v->vitesse);
        }

    }
    if(tab[1]==1)
    {

        if(v->indice_voiture>=0&&v->indice_voiture<4)
        {
            nouvelle_position->y+=v->vitesse;
            nouvelle_position->x-=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
        }
        else if(v->indice_voiture>=4&&v->indice_voiture<8)
        {
            nouvelle_position->y-=v->vitesse;
            nouvelle_position->x+=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
        }
        else if(v->indice_voiture>=8&&v->indice_voiture<12)
        {
            nouvelle_position->y-=v->vitesse;
            nouvelle_position->x+=tan((v->angle)*M_PI/180)*(v->vitesse);
        }
        else
        {
            nouvelle_position->y+=v->vitesse;
            nouvelle_position->x-=tan((v->angle)*M_PI/180)*(v->vitesse);
        }

    }
    if(tab[2]==1)
    {

        if(v->indice_voiture>=0&&v->indice_voiture<4)
        {
            nouvelle_position->y-=v->vitesse;
            nouvelle_position->x+=tan((v->angle)*M_PI/180)*(v->vitesse);
        }
        else if(v->indice_voiture>=4&&v->indice_voiture<8)
        {
            nouvelle_position->y+=v->vitesse;
            nouvelle_position->x-=tan((v->angle)*M_PI/180)*(v->vitesse);
        }
        else if(v->indice_voiture>=8&&v->indice_voiture<12)
        {
            nouvelle_position->y-=v->vitesse;
            nouvelle_position->x-=tan((v->angle)*M_PI/180)*(v->vitesse);
        }
        else
        {

            nouvelle_position->y+=v->vitesse;
            nouvelle_position->x-=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
        }

    }
    if(tab[3]==1)
    {
        if(v->indice_voiture>=0&&v->indice_voiture<4)
        {
            nouvelle_position->y+=v->vitesse;
            nouvelle_position->x-=tan((v->angle)*M_PI/180)*(v->vitesse);
        }
        else if(v->indice_voiture>=4&&v->indice_voiture<8)
        {
            nouvelle_position->y-=v->vitesse;
            nouvelle_position->x+=tan((v->angle)*M_PI/180)*(v->vitesse);
        }
        else if(v->indice_voiture>=8&&v->indice_voiture<12)
        {
            nouvelle_position->y+=v->vitesse;
            nouvelle_position->x+=tan((v->angle)*M_PI/180)*(v->vitesse);
        }
        else
        {
            nouvelle_position->y-=v->vitesse;
            nouvelle_position->x+=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);

        }

    }

}

void acceleration_turbo(Player *p,int tab[])
{
    int i,a=0,delai;

    for (int i = 0; i < 4; ++i)
    {
        if(tab[i]==1)
        {
            a++;
        }
    }
    if(p->v.autorisation_turbo==1)
    {
        if(tab[4]==1)
        {
            p->v.vitesse+=(15-p->v.vitesse);
        }
    }


    if(p->v.vitesse>13)
    {
        p->v.turbo=1;
    }
    else
        p->v.turbo=0;

    if(a>0)
    {
        if(p->stage!=4&&p->stage!=2&&p->stage!=3)
        {
            if(p->v.vitesse<3)
            {
                p->v.vitesse+=0.1;
            }
            else
            {
                p->v.vitesse+=0.001;
                if(p->v.vitesse>10&&p->v.turbo==0)
                    p->v.vitesse=10;
            }
        }
        else
        {
            if(p->v.vitesse<3)
            {
                p->v.vitesse+=0.1;
            }
            else
            {
                p->v.vitesse+=0.01;
                if(p->v.vitesse>10&&p->v.turbo==0)
                    p->v.vitesse=10;
            }
        }


        if(p->v.vitesse>=15&&p->v.turbo==1)
        {
            p->v.vitesse=15;
        }

    }
    else
    {
        p->v.vitesse=0;
    }

    if(p->v.turbo==1)
    {
        p->v.temps_turbo++;
        if(p->v.temps_turbo>150)
        {
            p->v.vitesse=10;
            p->v.temps_turbo=0;
            p->v.autorisation_turbo=0;
        }
    }

    if(p->stage!=4)
    {
        delai=400;
    }
    else
    {
        delai=150;
    }
    if(p->v.autorisation_turbo==0)
    {
        p->v.delai_turbo++;
        if(p->v.delai_turbo>delai)
        {
            p->v.delai_turbo=0;
            p->v.autorisation_turbo=1;
        }
    }

}

void afficher_etat_turbo(SDL_Surface *ecran,Player p)
{
    SDL_Surface *vert=NULL;
    int h,w=20;
    SDL_Rect position;
    position.x=800-30;
    position.y=600-200;

    if(p.v.autorisation_turbo==1)
    {
        h=150-p.v.temps_turbo;
        vert=SDL_CreateRGBSurface(SDL_HWSURFACE,w,h,32,0,0,0,0);
        SDL_FillRect(vert,NULL,SDL_MapRGB(ecran->format,0,255,0));
        SDL_BlitSurface(vert,NULL,ecran,&position);
        SDL_FreeSurface(ecran);
    }
    else
    {
        h=p.v.delai_turbo;
        if(h>150)
            h=150;
        vert=SDL_CreateRGBSurface(SDL_HWSURFACE,w,h,32,0,0,0,0);
        SDL_FillRect(vert,NULL,SDL_MapRGB(ecran->format,255,0,0));
        SDL_BlitSurface(vert,NULL,ecran,&position);
        SDL_FreeSurface(ecran);
    }

    SDL_FreeSurface(vert);
}


void deplacement_cas_enigme(SDL_Surface *bg_collision,SDL_Rect *position_camera, Voiture *v)
{
    int collision;
    SDL_Rect position,position_voiture;
    position.x=position_camera->x;
    position.y=position_camera->y;

    position_voiture.x=v->position.x;
    position_voiture.y=v->position.y;

    position.x-=50;
    //position_voiture.x-=30;
    collision=verifier_collision(bg_collision,position,v->position);
    if(collision==1)
    {
        position.x=position_camera->x;
    }
    else
    {
        position_camera->x=position.x;
        return ;
    }

    position.x+=50;
    //position_voiture.x+=30;
    collision=verifier_collision(bg_collision,position,v->position);
    if(collision==1)
    {
        position.x=position_camera->x;
    }
    else
    {
        position_camera->x=position.x;
        return ;
    }

    position.y+=50;
    //position_voiture.y+=30;
    collision=verifier_collision(bg_collision,position,v->position);
    if(collision==1)
    {
        position.y=position_camera->y;
    }
    else
    {
        position_camera->y=position.y;
        return ;
    }

    position.y-=50;
    //position_voiture.y-=30;
    collision=verifier_collision(bg_collision,position,v->position);
    if(collision==1)
    {
        position.y=position_camera->y;
    }
    else
    {
        position_camera->y=position.y;
        return ;
    }

}


void deplacer_voiture(Voiture *v,SDL_Rect position_camera,int tab[],SDL_Rect position_bg,int coll_boss, int coll_map )
{
    int a=0;

    if(position_camera.x==position_bg.w-800||position_camera.x==0||position_camera.y==0||position_camera.y==position_bg.h-600)
    {
        if(tab[0]==1&&!coll_boss&&!coll_map)
        {

            if(v->indice_voiture>=0&&v->indice_voiture<4)
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=4&&v->indice_voiture<8)
            {
                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=8&&v->indice_voiture<12)
            {
                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle)*M_PI/180)*(v->vitesse);
            }

            v->etat_voiture=1;
            if(v->position.y>600-294)
            {
                v->position.y=600-211;
            }

            //printf("voiture deplacee left\n");
        }
        if(tab[1]==1&&!coll_boss&&!coll_map)
        {

            if(v->indice_voiture>=0&&v->indice_voiture<4)
            {
                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=4&&v->indice_voiture<8)
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=8&&v->indice_voiture<12)
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else
            {
                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle)*M_PI/180)*(v->vitesse);
            }

            v->etat_voiture=1;
            if(v->position.y<0)
            {
                v->position.y=0;
            }

            //printf("voiture deplacee right\n");
        }
        if(tab[2]==1&&!coll_boss&&!coll_map)
        {

            if(v->indice_voiture>=0&&v->indice_voiture<4)
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=4&&v->indice_voiture<8)
            {
                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=8&&v->indice_voiture<12)
            {
                v->position.y-=v->vitesse;
                v->position.x-=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else
            {

                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);
            }

            v->etat_voiture=1;
            if(v->position.x<0)
            {
                v->position.x=0;
            }
            //printf("voiture deplacee up\n");
        }
        if(tab[3]==1&&!coll_boss&&!coll_map)
        {
            if(v->indice_voiture>=0&&v->indice_voiture<4)
            {
                v->position.y+=v->vitesse;
                v->position.x-=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=4&&v->indice_voiture<8)
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else if(v->indice_voiture>=8&&v->indice_voiture<12)
            {
                v->position.y+=v->vitesse;
                v->position.x+=tan((v->angle)*M_PI/180)*(v->vitesse);
            }
            else
            {
                v->position.y-=v->vitesse;
                v->position.x+=tan((v->angle_gauche)*M_PI/180)*(v->vitesse);

            }

            v->etat_voiture=1;
            if(v->position.x>800-294)
            {
                v->position.x=800-211;
            }
        }
    }

}

void changer_image_voiture(SDL_Surface *bg_collision,SDL_Rect position_camera,Voiture *v)
{
    int collision;
    SDL_Rect centre_voiture;
    centre_voiture.x=(position_camera.x+v->position.x)+(294/2);
    centre_voiture.y=(position_camera.y+v->position.y)+(211/2);
    collision=collision_tournant(bg_collision,centre_voiture);

    if(collision!=20)
    {

        v->direction=collision;

    }

}

void gagner(Player *p,SDL_Rect position_camera)
{
    SDL_Rect centre_voiture;

    centre_voiture.x=(position_camera.x+p->v.position.x)+(294/2);
    centre_voiture.y=(position_camera.y+p->v.position.y)+(211/2);

    if(p->stage==0)
    {
        if(centre_voiture.x>4000&&centre_voiture.x<4682&&centre_voiture.y>4754&&centre_voiture.y<5282)
        {
            p->gagner=1;
            p->score+=400;
            //p->stage++;
            printf("gagner\n");
        }
    }
    if(p->stage==1)
    {
        if(centre_voiture.x>4807&&centre_voiture.x<5406&&centre_voiture.y>5944&&centre_voiture.y<6218)
        {
            p->gagner=1;
            p->score+=400;
            //p->stage++;
            printf("gagner\n");
        }
    }
    if(p->stage==2)
    {
        if(centre_voiture.x>456&&centre_voiture.x<1123&&centre_voiture.y>6152&&centre_voiture.y<6524)
        {
            p->gagner=1;
            p->score+=400;
            //p->stage++;
            printf("gagner\n");
        }
    }
    if(p->stage==3)
    {
        if(centre_voiture.x>504&&centre_voiture.x<1576&&centre_voiture.y>40&&centre_voiture.y<440)
        {
            p->gagner=1;
            p->score+=400;
            //p->stage++;
            printf("gagner\n");
        }
    }
    if(p->stage==4)
    {
        if(centre_voiture.x>1012&&centre_voiture.x<1572&&centre_voiture.y>168&&centre_voiture.y<492)
        {
            p->gagner=1;
            p->score+=400;
            //p->stage++;
            printf("gagner\n");
        }
    }
}

void defaite(Player *p,temps t)
{
    if(p->score==0||p->pv==0)
    {
        p->game_over=1;
        printf("game over\n");
    }
    if(p->stage==1)
    {
        if(t.temps_stage2>60*2*1000)
        {
            p->game_over=1;
            printf("game over\n");
        }
    }
    if(p->stage==2)
    {
        if(t.temps_stage3>60*3*1000)
        {
            p->game_over=1;
            printf("game over\n");
        }
    }
}

int convertir_milliseconde(int temps_milli)
{
    return temps_milli/1000;
}

void afficher_temps(temps t,SDL_Surface* ecran,int stage)
{
    int seconde=0,minute=0,temps_stage2=60*2*1000,temps_stage3=60*3*1000,delta_temps;
    char temps[10];

    SDL_Surface *Temps=NULL;
    SDL_Rect position_temps;
    position_temps.x=0;
    position_temps.y=0;

    if(stage==1)
    {
        delta_temps=temps_stage2 - t.temps_stage2;
    }
    else if(stage==2)
    {
        delta_temps=temps_stage3 - t.temps_stage3;
    }

    seconde=convertir_milliseconde(delta_temps);
    while(seconde>59)
    {
        minute++;
        seconde-=60;
    }

    sprintf(temps,"%d:%d",minute,seconde);
    printf("%s\n",temps );

    TTF_Font *police=NULL;
    police=TTF_OpenFont("Police/Heroes Legend.ttf",30);

    SDL_Color couleur_score1= {255,0,0};
    SDL_Color couleur_score2= {0,255,0};
    if(delta_temps<30*1000)
    {
        Temps=TTF_RenderText_Solid(police,temps,couleur_score1);
    }
    else
    {
        Temps=TTF_RenderText_Solid(police,temps,couleur_score2);
    }

    SDL_BlitSurface(Temps,NULL,ecran,&position_temps);

    TTF_CloseFont(police);
    SDL_FreeSurface(Temps);

}






