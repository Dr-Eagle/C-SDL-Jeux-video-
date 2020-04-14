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

void miser_jour_multi(Multi *multi,int tab[])
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

	prochaine_position(&nouvelle_position1,tab,multi->p[0].v.vitesse);
	prochaine_position2(&nouvelle_position2,tab,multi->p[1].v.vitesse);

	verif_collision1=verifier_collision(multi->col.bg_collision,nouvelle_position1,position_neutre);
	verif_collision2=verifier_collision(multi->col.bg_collision,nouvelle_position2,position_neutre);

	

	/*if(verif_collision1==1)
	{
			modifier_score_col(verif_collision1,&multi->p[0]);
			position_cas_collision(multi->col.bg_collision,&multi->cam[0].position_cam,&multi->p[0].v,tab,multi->bg[0].position);
	}
	else*/
	{
		deplacement_camera_multi1(&multi->cam[0],tab,multi->p[0].v.vitesse,multi->bg[0].position,&multi->p[0].v.etat_voiture);
		deplacer_voiture_multi1(multi->p,multi->cam[0].position_cam,tab,multi->bg[0].position);
	}

	/*if(verif_collision2==1)
	{
			modifier_score_col(verif_collision2,&multi->p[1]);
			position_cas_collision2(multi->col.bg_collision,&multi->cam[1].position_cam,&multi->p[1].v,tab,multi->bg[1].position);	
	}
	else*/
	{
		deplacement_camera_multi2(&multi->cam[1],tab,multi->p[1].v.vitesse,multi->bg[1].position,&multi->p[1].v.etat_voiture);
		deplacer_voiture_multi2(multi->p,multi->cam[1].position_cam,tab,multi->bg[0].position);
	}

	printf("2----%d %d %d %d\n",multi->cam[1].position_cam.x,multi->cam[1].position_cam.y ,multi->p[1].v.position.x,multi->p[1].v.position.y);
	printf("1----%d %d\n",multi->cam[0].position_cam.x,multi->cam[0].position_cam.y );

	printf("%d\n",verif_collision2 );
	
	gagner_multi(multi->p,multi->cam[0].position_cam,multi->cam[1].position_cam);

}

void display_multi(SDL_Surface *ecran,Multi *multi)
{
	scrolling_multi(multi->cam,ecran,multi->bg[0].stage);
	afficher_voiture_multi(ecran,multi->p,multi->cam[0].position_cam,multi->cam[1].position_cam);
	afficher_score_multi(multi->p,ecran);
}

void liberer_multi(Multi multi)
{

}

void jouer_multi(SDL_Surface *ecran,Player p[],int *k)
{
	Multi multi;
	multi.p[0]=p[0];
	multi.p[1]=p[1];
	SDL_Event touch;

	int continuer_jeux=1,recommencer=1;
	int now=0;
	int ex=0;
	int periodeFPS=33;
	int dt=0;
	float delta_s=0;

	while(recommencer)
	{
		ini_multi(&multi);
		while(continuer_jeux)
		{

			SDL_PollEvent(&touch);
			
			now=SDL_GetTicks();
			dt=now -ex;
			if(dt>periodeFPS)
			{
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
						case SDLK_n:
							//multi.p.gagner=1;
						break;
					}
					break;
				}
				
				miser_jour_multi(&multi,multi.inp.tab_clavier);
				display_multi(ecran,&multi);

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
}