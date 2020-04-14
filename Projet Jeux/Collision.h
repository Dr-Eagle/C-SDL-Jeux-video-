#ifndef _COLLISION_H_
#define _COLLISION_H_

typedef struct collision
{
	SDL_Surface *bg_collision;
}collision;

void initialiser_collision_multi(collision *c);
int verifier_collision_multi(SDL_Surface *fond_collision,SDL_Rect position_camera,SDL_Rect position_voiture);
int collision_multi(SDL_Rect position_joueur1, SDL_Rect position_joueur2 ,SDL_Rect position_cam1,SDL_Rect position_cam2);

void initialiser_collision(collision *c,int stage);
int collision_deplacement_entite(SDL_Rect position_boss, SDL_Rect position_joueur ,SDL_Rect position_cam, int direction);
void deplacement_collision_entite(SDL_Rect position_boss, SDL_Rect *position ,SDL_Rect *position_camera,int tab[],SDL_Rect position_bg);
SDL_Color recuperer_couleur(SDL_Surface *fond_collision,SDL_Rect position);
int verifier_collision(SDL_Surface *fond_collision,SDL_Rect position_camera,SDL_Rect position_voiture);
int collision_tournant(SDL_Surface *fond_collision,SDL_Rect centre_voiture);//f  
int collision2_entite(SDL_Rect position_camera,SDL_Rect position1,SDL_Rect position2,int stage);


#endif