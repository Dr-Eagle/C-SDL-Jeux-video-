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

void afficher_parametre(SDL_Surface *ecran,int *k,int *continuer_jeux,int *continuer_stage,Update *update,temps *t)
{
	int continuer=1,choix=0,i;


	SDL_Surface *option_parametre[6]={NULL};
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
		
		//pause(t);
			SDL_WaitEvent(&touch);
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
							sauvegarder("profils.txt",update->p);
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
	SDL_Surface *message=NULL,*option_winnner[3]={NULL},*option_loser[2]={NULL};
	SDL_Rect position_message,position_winner[3],position_loser[2];
	SDL_Event touch;
	position_message.x=0;
	position_message.y=0;

	position_winner[0].x=262;
	position_winner[0].y=358;
	position_winner[1].x=382;
	position_winner[1].y=359;
	position_winner[2].x=501;
	position_winner[2].y=359;

	position_loser[0].x=358;
	position_loser[0].y=360;
	position_loser[1].x=427;
	position_loser[1].y=360;


	if(p->gagner==1)
	{
		message=IMG_Load("Image/parametre/win.png");

		option_winnner[0]=IMG_Load("Image/parametre/reload.png");
		option_winnner[1]=IMG_Load("Image/parametre/home.png");
		option_winnner[2]=IMG_Load("Image/parametre/next.png");
		

		SDL_BlitSurface(message,NULL,ecran,&position_message);
		SDL_Flip(ecran);

		while(continuer)
		{
			SDL_WaitEvent(&touch);
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
			SDL_WaitEvent(&touch);
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

/*void message_fin_jeu_multi(Player p[],SDL_Surface *ecran,int *continuer_jeux,int *recommencer)
{
	int continuer=1,choix=0,i;
	SDL_Surface *message=NULL,*option_winnner[3]={NULL},*option_loser[2]={NULL};
	SDL_Rect position_message,position_winner[3],position_loser[2];
	SDL_Event touch;
	position_message.x=0;
	position_message.y=0;

	position_winner[0].x=262;
	position_winner[0].y=358;
	position_winner[1].x=382;
	position_winner[1].y=359;
	position_winner[2].x=501;
	position_winner[2].y=359;

	position_loser[0].x=358;
	position_loser[0].y=360;
	position_loser[1].x=427;
	position_loser[1].y=360;


	if(p[0].gagner==1)
	{
		message=IMG_Load("Image/parametre/win.png");

		option_winnner[0]=IMG_Load("Image/parametre/reload.png");
		option_winnner[1]=IMG_Load("Image/parametre/home.png");
		option_winnner[2]=IMG_Load("Image/parametre/next.png");
		

		SDL_BlitSurface(message,NULL,ecran,&position_message);
		SDL_Flip(ecran);

		while(continuer)
		{
			SDL_WaitEvent(&touch);
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
			SDL_WaitEvent(&touch);
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
*/


