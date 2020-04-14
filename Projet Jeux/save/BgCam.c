#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "BgCam.h"

void initialiser_bg_multi(Background b[])
{

	b[0].position.x=0;
	b[0].position.y=0;
	b[1].position.x=0;
	b[1].position.y=0;

	b[0].position.w=3399;
	b[0].position.h=1894;
	b[1].position.w=3399;
	b[1].position.h=1894;


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

	c[0].position_cam.x=650;
	c[0].position_cam.y=100;

	c[1].position_cam.x=650;
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

void deplacement_camera_multi1(Camera *c,int tab[],float vitesse,SDL_Rect position_bg,int *etat_voiture)
{
		if(tab[0]==1)
		{
			c->position_cam.x-=vitesse;
			*etat_voiture=1;
			//printf("camera deplacee left\n");
		}
		if(tab[1]==1)
		{
			c->position_cam.x+=vitesse;
			*etat_voiture=1;
			//printf("camera deplacee right\n");
		}
		if(tab[2]==1)
		{
			c->position_cam.y-=vitesse;
			*etat_voiture=1;
			//printf("camera deplacee up\n");
		}
		if(tab[3]==1)
		{
			c->position_cam.y+=vitesse;
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

void deplacement_camera_multi2(Camera *c,int tab[],float vitesse,SDL_Rect position_bg,int *etat_voiture)
{

		if(tab[6]==1)
		{
			c->position_cam.x-=vitesse;
			*etat_voiture=1;
			//printf("camera deplacee left\n");
		}
		if(tab[7]==1)
		{
			c->position_cam.x+=vitesse;
			*etat_voiture=1;
			//printf("camera deplacee right\n");
		}
		if(tab[8]==1)
		{
			c->position_cam.y-=vitesse;
			*etat_voiture=1;
			//printf("camera deplacee up\n");
		}
		if(tab[9]==1)
		{
			c->position_cam.y+=vitesse;
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

	if(stage==0)
	{
		b->position.w=6435;
		b->position.h=5304;
	}
	else if(stage==1)
	{
		b->position.w=6956;
		b->position.h=5220;
	}
	else if(stage==2)
	{
		b->position.w=16255;
		b->position.h=7970;
	}
	else if(stage==3)
	{
		b->position.w=16913;
		b->position.h=18541;
	}
	else if(stage==4)
	{
		b->position.w=11359;
		b->position.h=5990;
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
		c->position_cam.x=1857;
		c->position_cam.y=16792;

		printf("camera stage 4 initialisee\n");
	
	}
	else if(stage==4)
	{
		c->position_cam.x=2825;
		c->position_cam.y=5600;
		
		printf("camera stage 5 initialisee\n");
	}
	
	
}


void afficher_camera(SDL_Rect position_cam,SDL_Surface *ecran,SDL_Surface *bg)
{
	SDL_BlitSurface(bg,&position_cam, ecran,NULL);
	//printf("camera affichee\n");
}

void deplacement_camera(Camera *c,int tab[],float *vitesse,SDL_Rect position_bg,int *etat_voiture)
{
		if(tab[0]==1)
		{
			c->position_cam.x-=*vitesse;
			*etat_voiture=1;
			//printf("camera deplacee left\n");
		}
		if(tab[1]==1)
		{
			c->position_cam.x+=*vitesse;
			*etat_voiture=1;
			//printf("camera deplacee right\n");
		}
		if(tab[2]==1)
		{
			c->position_cam.y-=*vitesse;
			*etat_voiture=1;
			//printf("camera deplacee up\n");
		}
		if(tab[3]==1)
		{
			c->position_cam.y+=*vitesse;
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


