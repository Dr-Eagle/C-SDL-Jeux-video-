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




void initialiser(Update *update)
{
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
	}
	if(update->p.stage==4)
	{
		initialiser_boss(&update->boss);
	}*/
	
}

void entree_clavier(SDL_Event event, input *touch )
{
	recuperer_touch(touch,event);
}

void mise_jour(Update *update,int tab[],int *Collision,SDL_Event touch,SDL_Surface *ecran,int *indice,int *continuer_stage,int *continuer_jeux,temps *t,int *k,int dt)
{

	int verif_collision=0,nouvel_etat,indice_enigme,verifier_eni,stage=4,continuer=1,a=0,i;
	SDL_Rect nouvelle_position,position_neutre;
	nouvelle_position.x=update->cam.position_cam.x+update->p.v.position.x;
	nouvelle_position.y=update->cam.position_cam.y+update->p.v.position.y;

	position_neutre.x=0;
	position_neutre.y=0;
	acceleration_turbo(&update->p,tab);

	changer_image_voiture(update->col.bg_collision,update->cam.position_cam,&update->p.v);

	
	prochaine_position(&nouvelle_position,tab,update->p.v.vitesse);
	animation_voiture(&update->p,tab);

	//printf("%d %d %d \n",update->cam.position_cam.x,update->cam.position_cam.y,update->p.v.etat_voiture);
	//printf("%d %d \n",update->p.v.position.x,update->p.v.position.y );
					
	verif_collision=verifier_collision(update->col.bg_collision,nouvelle_position,position_neutre);
	*Collision=verif_collision;

		if(verif_collision==1)
		{
			modifier_score_col(verif_collision,&update->p);
			position_cas_collision(update->col.bg_collision,&update->cam.position_cam,&update->p.v,tab,update->bg.position);
			update->p.v.vitesse=3;
			//
		}
		else
		{
			deplacement_camera(&update->cam,tab,&update->p.v.vitesse,update->bg.position,&update->p.v.etat_voiture);
			deplacer_voiture(&update->p.v,update->cam.position_cam,tab,update->bg.position);
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


		if(/*update->p.*/stage==4)
		{
			//deplacement_entite(&update->boss,update->col.bg_collision);
			//verifier_collision=verifier_collision(update->col.bg_collision,update->enti[0].position,position_neutre);
		}

		for (int i = 0; i < 6; ++i)
		{
			if(tab[i]==1)
				a++;
		}
		if(a==0)
			update->p.v.etat_voiture=0;

		gagner(&update->p,update->cam.position_cam);
		defaite(&update->p,*t);
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
		if(tab[4]==1)
			son_turbo(update->p,*k);


}
void display(SDL_Surface *ecran,Update *update,int collision,int indice_enigme,temps t,int *continuer_jeux,int *continuer_stage)
{
	
	if(continuer_jeux!=0)
	{
		afficher_camera(update->cam.position_cam,ecran,update->bg.stage);
		afficher_voiture(ecran,update->p);
		afficher_score(update->p,ecran);
		if(update->p.stage==1||update->p.stage==2)
		{
			afficher_temps(t,ecran,update->p.stage);
		}

		/*if(update->boss.position.x>update->cam.position_cam.x&&update->boss.position.x<update->cam.position_cam.x+800&&update->boss.position.y>update->cam.position_cam.y&&update->boss.position.y<update->cam.position_cam.y+600)
		{
			afficher_boss(update->boss,ecran,update->cam.position_cam);
		}*/

		message_fin_jeu(&update->p,ecran,continuer_jeux,continuer_stage);
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
	
	// Mix_FreeChunk(son);
	//SDL_FreeSurface(update->);
	Mix_FreeMusic(update->p.son.son_voiture);
	Mix_FreeChunk(update->p.son.son_horloge);
	//Mix_FreeMusic(update->p.son.son_horloge_rapide);
	//Mix_FreeMusic(update->p.son.son_collision);
}

void jouer(SDL_Surface *ecran,int *k,Player p)
{
	Update update;
	temps t;
	update.p=p;
	int continuer_stage=1,continuer_jeux=1,indice_enigme,collision,stage=3,temps_actuel,i;
	SDL_Event touch;
	
	int now=0;
	int ex=0;
	int periodeFPS=33;
	int dt=0;
	float delta_s=0;

	//memset(&update.inp,0,sizeof(update.inp));

	SDL_WM_SetCaption("Eagle Race",NULL);

	//SDL_EnableKeyRepeat(0, 3000);
	initialiser_temps(&t);
	while(continuer_stage)
	{
   		temps_jeu(&t);
		continuer_jeux=1;
		initialiser(&update);
		//
		son_voiture(update.p,*k);
		if(update.p.stage==1||update.p.stage==2)
			son_tic_tac(update.p,*k);
		Mix_PauseMusic();
		//
		

		while(continuer_jeux)
		{
			
			SDL_PollEvent(&touch);
			
			now=SDL_GetTicks();
			dt=now -ex;
			if(dt>periodeFPS)
			{
				
				entree_clavier(touch,&update.inp);
				if(update.inp.tab_clavier[5]==1)
				{		if(update.p.stage==1||update.p.stage==2)
							Mix_PlayChannel(1,update.p.son.son_horloge,0);

						afficher_parametre(ecran,k,&continuer_jeux,&continuer_stage,&update,&t);
						update.inp.tab_clavier[5]=0;

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
				
				mise_jour(&update,update.inp.tab_clavier,&collision,touch,ecran,&indice_enigme,&continuer_jeux,&continuer_stage,&t,k,dt);

				display(ecran,&update,collision,indice_enigme,t,&continuer_jeux,&continuer_stage);
				
				Mix_VolumeMusic(MIX_MAX_VOLUME /(10/(*k)));
				 Mix_VolumeChunk(update.p.son.son_horloge, MIX_MAX_VOLUME/(10/(*k)));

				SDL_Flip(ecran);
				ex=now;
				touch.type = 66;

				//printf("%d input\n",touch.type );
			}
			else
			{
				SDL_Delay(periodeFPS-dt);
			}

		}
	}

	liberer(&update);
}