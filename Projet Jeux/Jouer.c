#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <time.h>
#include "Jouer.h"
#include "autre.h"
#define M_PI	3.1415926535897932384626433832795

FILE *fi=NULL;



void initialiser(Update *update)
{
    char nomfich2[50];
    initialiser_player(&update->p);
    initialiser_Background(&update->bg,update->p.stage);
    initialiser_camera(&update->cam,update->bg.position,update->p.stage);
    initialiser_collision(&update->col,update->p.stage);
    initialiser_input(&update->inp);

    if(update->p.stage==2)
    {
        initialiser_enigmes(&update->enig);
    }
    /*if(update->p.stage==3)
    {
    	//initialiser_entite(update->enti[0]);
    }*/
    if(update->p.stage==4)
    {
        initialiser_boss(&update->boss);
        sprintf(nomfich2,"%d.txt",update->boss.indice);
        ouvrir_fichier(&fi,nomfich2);
    }




}

void entree_clavier(SDL_Event event, input *touch )
{
    recuperer_touch(touch,event);
}

void mise_jour(Update *update,int tab[],int *Collision,SDL_Event touch,SDL_Surface *ecran,int *indice,int *continuer_stage,int *continuer_jeux,temps *t,int *k,int dt)
{

    char nomfich[20],nomfich2[20];
    int verif_collision=0,nouvel_etat,indice_enigme,verifier_eni,stage=4,continuer=1,a=0,i,indice_entite,coll_boss=0;
    SDL_Rect nouvelle_position,position_neutre;
    nouvelle_position.x=update->cam.position_cam.x+update->p.v.position.x;
    nouvelle_position.y=update->cam.position_cam.y+update->p.v.position.y;

    position_neutre.x=0;
    position_neutre.y=0;
    acceleration_turbo(&update->p,tab);

    changer_image_voiture(update->col.bg_collision,update->cam.position_cam,&update->p.v);


    prochaine_position(&nouvelle_position,tab,&update->p.v);
    animation_voiture(&update->p,tab);

    //printf("%d %d %d \n",update->cam.position_cam.x,update->cam.position_cam.y,update->p.v.etat_voiture);
    //printf("%d %d \n",update->p.v.position.x,update->p.v.position.y );

    verif_collision=verifier_collision(update->col.bg_collision,nouvelle_position,position_neutre);
    *Collision=verif_collision;

    if(verif_collision==1)
    {
        modifier_score_col(verif_collision,&update->p);
        update->p.v.vitesse=0;

    }



    if(update->p.stage==1)
    {
        compter_temps_stage2(t);
    }

    if(update->p.stage==2)
    {

        compter_temps_stage3(t);

        if(verif_collision==1)
        {
            Mix_RewindMusic();
            Mix_PauseMusic();

            son_collision(update->p,*k);
            indice_enigme=generation_enigme();
            *indice=indice_enigme;
            afficher_enigme(update->enig,update->cam.position_cam,ecran,indice_enigme);
            afficher_reponse_saisie(ecran,update->enig.choix);
            SDL_Flip(ecran);

            SDL_Event event;
            continuer=1;
            while(continuer)
            {

                SDL_WaitEvent(&event);
                saisir_reponse(event,&update->enig.choix);

                printf("%d\n",update->enig.choix );
                switch(event.type)
                {
                case SDL_KEYDOWN:

                    switch(event.key.keysym.sym)
                    {
                    case SDLK_RETURN:
                        modifier_score(update->enig,&update->p.score,update->enig.choix,indice_enigme);
                        continuer=0;
                        deplacement_cas_enigme(update->col.bg_collision,&update->cam.position_cam,&update->p.v);
                        for (int i = 0; i < 4; ++i)
                        {
                            tab[i]=0;
                        }
                        update->enig.choix=0;
                        printf("sortie\n");
                        break;

                    }

                    afficher_enigme(update->enig,update->cam.position_cam,ecran,indice_enigme);
                    afficher_reponse_saisie(ecran,update->enig.choix);

                    SDL_Flip(ecran);
                    break;

                }

            }
            Mix_ResumeMusic();
        }
    }


    if(update->p.stage==4)
    {
        lire_nombreFichier("indice.txt",&indice_entite);

        sprintf(nomfich,"%d.txt",indice_entite+1);
        ajouter_position(nomfich,update->p.v.position,update->cam.position_cam,update->p.v.indice_voiture,update->p.v.turbo);

        if(indice_entite>0)
            lire_position(fi,nomfich2,&update->boss);

        if(feof(fi))
            update->p.game_over=1;

        coll_boss=collision_deplacement_entite(update->boss.position,update->p.v.position,update->cam.position_cam,update->p.v.direction);
        if(coll_boss)
        {
            update->p.v.vitesse-=5;
            if(update->p.v.vitesse<0)
                update->p.v.vitesse=0;
        }

    }


    deplacement_camera(&update->cam,tab,&update->p.v.vitesse,update->bg.position,&update->p.v.etat_voiture,update->p.v.angle,update->p.v.angle_gauche,update->p.v.indice_voiture,coll_boss,verif_collision);
    deplacer_voiture(&update->p.v,update->cam.position_cam,tab,update->bg.position,coll_boss,verif_collision);




    for (int i = 0; i < 6; ++i)
    {
        if(tab[i]==1)
            a++;
    }
    if(a==0)
        update->p.v.etat_voiture=0;

    gagner(&update->p,update->cam.position_cam);
    defaite(&update->p,*t);

    if(update->p.stage==4)
    {
        if(update->p.game_over==1||(*continuer_jeux)==0)
        {
            sprintf(nomfich,"%d.txt",indice_entite+1);
            remove(nomfich);
            ecrire_nombreFichier("indice.txt",indice_entite);
        }
        else if(update->p.gagner==1)
        {
            indice_entite++;
            ecrire_nombreFichier("indice.txt",indice_entite);
        }

    }


    if(update->p.v.etat_voiture==1)
    {
        Mix_ResumeMusic();
        //printf("%d\n",update->p.v.etat_voiture );
    }
    else if(update->p.v.etat_voiture==0)
    {
        Mix_RewindMusic();
        Mix_PauseMusic();
        //printf("%d\n",update->p.v.etat_voiture );
    }
    if(tab[4]==1&&update->p.v.turbo==1)
        son_turbo(update->p,*k);


}
void display(SDL_Surface *ecran,Update *update,int *jouer,int indice_enigme,temps *t,int *continuer_jeux,int *continuer_stage)
{

    if(continuer_jeux!=0)
    {

        afficher_camera(update->cam,ecran,update->bg);
        afficher_voiture(ecran,update->p);
        afficher_score(update->p,ecran);
        if(update->p.stage==1||update->p.stage==2)
        {
            afficher_temps(*t,ecran,update->p.stage);
        }

        if(update->p.stage==4)
            afficher_boss(update->boss,ecran,update->cam.position_cam);

        afficher_etat_turbo(ecran,update->p);
        afficher_minimap(update->cam.position_cam,update->p.v.position,update->bg,ecran,update->p.v.couleur,update->p.stage,update->boss.position);
        if(update->p.gagner==1||update->p.game_over==1)
        {
            Mix_PlayChannel(1,update->p.son.son_horloge,0);
            Mix_PauseMusic();
        }
        message_fin_jeu(&update->p,ecran,continuer_jeux,continuer_stage);
        if(*jouer==0&&update->p.stage==0)
            image_mission(ecran,"Image/tuto.png");

        //compte_a_rebour(jouer,ecran,t);
    }



}
void liberer(Update *update)
{
    int i;
    SDL_FreeSurface(update->bg.stage);
    SDL_FreeSurface(update->col.bg_collision);
    for (int i = 0; i < 16; ++i)
    {
        SDL_FreeSurface(update->p.v.deplacement[i]);
        SDL_FreeSurface(update->p.v.deplacement_turbo[i]);
    }
    if(update->p.stage==2)
    {
        for (int i = 0; i < 18; ++i)
        {
            SDL_FreeSurface(update->enig.enigme[i]);
        }
    }
    if(update->p.stage==4)
    {
        for (int i = 0; i < 16; ++i)
        {
            SDL_FreeSurface(update->boss.deplacement[i]);
            SDL_FreeSurface(update->boss.deplacement_turbo[i]);
        }
    }

    Mix_FreeMusic(update->p.son.son_voiture);
    Mix_FreeChunk(update->p.son.son_horloge);
    Mix_FreeChunk(update->p.son.son_collision);
    Mix_FreeChunk(update->p.son.son_turbo);
    char nomfich2[50];
    sprintf(nomfich2,"%d.txt",update->boss.indice);
    char fich2[2];
    snprintf(fich2,10,"%d.txt",update->boss.indice);
    if(update->p.stage==4)
        fermer_fichier(&fi,fich2);
}

void jouer(SDL_Surface *ecran,int *k,Player p)
{
    Update update;
    temps t;
    update.p=p;
    int continuer_stage=1,continuer_jeux=1,indice_enigme,collision,stage=3,temps_actuel,i,jouer;
    SDL_Event touch;

    int start=0;
    int periodeFPS=33;
    int dt;

    SDL_WM_SetCaption("Eagle Race",NULL);

    //SDL_EnableKeyRepeat(0, 3000);
    initialiser_temps(&t);
    while(continuer_stage)
    {
        /*if(update.p.stage==3)
        	update.p.stage++;*/

        if(update.p.stage==5)
            update.p.stage=0;
        temps_jeu(&t);
        continuer_jeux=1;
        initialiser(&update);
        if(update.p.stage==1)
            image_mission(ecran,"Image/message-2.png");
        //
        son_voiture(update.p,*k);
        if(update.p.stage==1||update.p.stage==2)
            son_tic_tac(update.p,*k);
        Mix_PauseMusic();
        //
        jouer=0;

        while(continuer_jeux)
        {

            SDL_PollEvent(&touch);

            start=SDL_GetTicks();

            entree_clavier(touch,&update.inp);
            if(update.inp.tab_claviersolo[5]==1)
            {
                if(update.p.stage==1||update.p.stage==2)
                    Mix_PlayChannel(1,update.p.son.son_horloge,0);

                afficher_parametre(ecran,k,&continuer_jeux,&continuer_stage,&update.p,&t);
                update.inp.tab_claviersolo[5]=0;

                if(update.p.stage==1||update.p.stage==2)
                    Mix_PlayChannel(1,update.p.son.son_horloge,-1);

            }

            switch(touch.type)
            {
            case SDL_QUIT:
                continuer_jeux=0;
                continuer_stage=0;
                break;
            case SDL_KEYDOWN:
                switch(touch.key.keysym.sym)
                {
                case SDLK_n:
                    update.p.gagner=1;
                    break;
                }
                break;
            }

            mise_jour(&update,update.inp.tab_claviersolo,&collision,touch,ecran,&indice_enigme,&continuer_jeux,&continuer_stage,&t,k,dt);

            display(ecran,&update,&jouer,indice_enigme,&t,&continuer_jeux,&continuer_stage);

            Mix_VolumeMusic(MIX_MAX_VOLUME /(10/(*k)));
            Mix_VolumeChunk(update.p.son.son_horloge, MIX_MAX_VOLUME/(10/(*k)));

            SDL_Flip(ecran);
            touch.type = 66;

            if(1000/periodeFPS>SDL_GetTicks()-start)
                SDL_Delay(1000/periodeFPS-(SDL_GetTicks()-start));

        }
    }

    liberer(&update);
}
