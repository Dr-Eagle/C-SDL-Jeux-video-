#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <time.h>
#include "Multiplayer.h"


void ini_multi(Multi *multi)
{
    initialiser_multi(multi->p);
    initialiser_bg_multi(multi->bg);
    initialiser_cam_multi(multi->cam);
    initialiser_collision_multi(&multi->col);
    initialiser_input_multi(&multi->inp);
}

void miser_jour_multi(Multi *multi,int tab[],int *continuer_jeux,int *recommencer)
{
    int verif_collision1,verif_collision2;
    SDL_Rect nouvelle_position1,nouvelle_position2,position_neutre;

    nouvelle_position1.x=multi->cam[0].position_cam.x+multi->p[0].v.position.x;
    nouvelle_position1.y=multi->cam[0].position_cam.y+multi->p[0].v.position.y;

    nouvelle_position2.x=multi->cam[1].position_cam.x+multi->p[1].v.position.x;
    nouvelle_position2.y=multi->cam[1].position_cam.y+multi->p[1].v.position.y;

    position_neutre.x=0;
    position_neutre.y=0;

    acceleration_turbo_multi(multi->p,tab);

    changer_image_voiture_multi(multi->col.bg_collision,multi->cam[0].position_cam,&multi->p[0]) ;
    changer_image_voiture_multi(multi->col.bg_collision,multi->cam[1].position_cam,&multi->p[1]) ;

    animation_voiture_multi(multi->p,tab);

    prochaine_position(&nouvelle_position1,tab,&multi->p[0].v);
    prochaine_position2(&nouvelle_position2,tab,&multi->p[1].v);

    verif_collision1=verifier_collision_multi(multi->col.bg_collision,nouvelle_position1,position_neutre);
    verif_collision2=verifier_collision_multi(multi->col.bg_collision,nouvelle_position2,position_neutre);



    if(verif_collision1==1)
    {
        modifier_score_col_multi(verif_collision1,&multi->p[0]);
        //multi->p[0].v.vitesse=0;
    }


    if(verif_collision2==1)
    {
        modifier_score_col_multi(verif_collision2,&multi->p[1]);
        //multi->p[1].v.vitesse=0;
    }
    // collision_multi(SDL_Rect position_joueur1, SDL_Rect position_joueur2 ,SDL_Rect position_cam1,SDL_Rect position_cam2);

    //printf("2----%d %d %d %d\n",multi->cam[1].position_cam.x,multi->cam[1].position_cam.y ,multi->p[1].v.position.x,multi->p[1].v.position.y);
    //printf("1----%d %d\n",multi->cam[0].position_cam.x,multi->cam[0].position_cam.y );

    deplacement_camera_multi1(&multi->cam[0],tab,&multi->p[0].v.vitesse,multi->bg[0].position,&multi->p[0].v.etat_voiture,multi->p[0].v.angle,multi->p[0].v.angle_gauche,multi->p[0].v.indice_voiture,0, verif_collision1);
    deplacement_camera_multi2(&multi->cam[1],tab,&multi->p[1].v.vitesse,multi->bg[1].position,&multi->p[1].v.etat_voiture,multi->p[1].v.angle,multi->p[1].v.angle_gauche,multi->p[1].v.indice_voiture,0, verif_collision2);

    deplacer_voiture_multi1(&multi->p[0].v,multi->cam[0].position_cam,tab,multi->bg[0].position,0,verif_collision1);
    deplacer_voiture_multi2(&multi->p[1].v,multi->cam[1].position_cam,tab,multi->bg[0].position,0,verif_collision2);

    gagner_multi(multi->p,multi->cam[0].position_cam,multi->cam[1].position_cam);

}

void display_multi(SDL_Surface *ecran,Multi *multi,int *continuer_jeux,int *recommencer)
{
    scrolling_multi(multi->cam,ecran,multi->bg[0].stage);
    afficher_voiture_multi(ecran,multi->p,multi->cam[0].position_cam,multi->cam[1].position_cam);
    afficher_score_multi(multi->p,ecran);
    afficher_etat_turbo_multi(ecran,multi->p);
    message_fin_jeu_multi(multi->p,ecran,continuer_jeux,recommencer);
}

void liberer_multi(Multi *multi)
{
    int i,j;
    for (int i = 0; i < 2; ++i)
    {
        SDL_FreeSurface(multi->bg[i].stage);
        for (int j = 0; j < 16; ++j)
        {
            SDL_FreeSurface(multi->p[i].v.deplacement[j]);
            SDL_FreeSurface(multi->p[i].v.deplacement_turbo[j]);
        }
    }
    SDL_FreeSurface(multi->col.bg_collision);


}

void jouer_multi(SDL_Surface *ecran,Player p[],int *k)
{
    Multi multi;
    multi.p[0]=p[0];
    multi.p[1]=p[1];
    SDL_Event touch;

    int continuer_jeux=1,recommencer=1;
    int start=0;
    int periodeFPS=33;


    while(recommencer)
    {
        ini_multi(&multi);
        continuer_jeux=1;
        while(continuer_jeux)
        {

            SDL_PollEvent(&touch);

            start=SDL_GetTicks();

            recuperer_touch_multi(&multi.inp,touch);
            switch(touch.type)
            {
            case SDL_QUIT:
                continuer_jeux=0;
                recommencer=0;
                break;
            case SDL_KEYDOWN:
                switch(touch.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    continuer_jeux=0;
                    recommencer=0;
                    break;
                }
                break;
            }

            miser_jour_multi(&multi,multi.inp.tab_clavier,&continuer_jeux,&recommencer);
            display_multi(ecran,&multi,&continuer_jeux,&recommencer);

            SDL_Flip(ecran);
            touch.type = 66;

            if(1000/periodeFPS>SDL_GetTicks()-start)
                SDL_Delay(1000/periodeFPS-(SDL_GetTicks()-start));

        }
    }
    liberer_multi(&multi);
}
