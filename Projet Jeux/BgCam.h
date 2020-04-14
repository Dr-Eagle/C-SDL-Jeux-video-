#ifndef _BGCAM_H_
#define _BGCAM_H_

typedef struct Background
{
   SDL_Surface *stage;
   SDL_Rect position;
   SDL_Surface *mini_map;
   SDL_Rect position_mini;
   SDL_Surface *rotation_map;

}Background;

typedef struct Camera
{
	SDL_Rect position_cam;
	SDL_Rect position_ecran;
}Camera;

void initialiser_bg_multi(Background b[]);
void initialiser_cam_multi(Camera c[]);
void scrolling_multi(Camera c[],SDL_Surface *ecran,SDL_Surface *bg);
void deplacement_camera_multi1(Camera *c,int tab[],float *vitesse,SDL_Rect position_bg,int *etat_voiture, int angle ,int angle_gauche,int indice_voiture,int coll_boss, int coll_map);
void deplacement_camera_multi2(Camera *c,int tab[],float *vitesse,SDL_Rect position_bg,int *etat_voiture, int angle ,int angle_gauche,int indice_voiture,int coll_boss, int coll_map);

void initialiser_Background(Background *b,int stage);
void initialiser_camera(Camera *c,SDL_Rect position_bg,int stage);
void afficher_camera(Camera c,SDL_Surface *ecran,Background b);
void deplacement_camera(Camera *c,int tab[],float *vitesse,SDL_Rect position_bg,int *etat_voiture, int angle ,int angle_gauche,int indice_voiture,int coll_boss, int coll_map);
void afficher_minimap(SDL_Rect position_cam,SDL_Rect position_player,Background b,SDL_Surface *ecran,int couleur_player,int stage,SDL_Rect position_boss);

#endif
