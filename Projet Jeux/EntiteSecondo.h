#ifndef _ENTITESECONDO_H_
#define _ENTITESECONDO_H_

typedef struct Entite
{
	int indice;
	int indice_voiture;
	int direction;
	int turbo;
	int pv;
	SDL_Rect position;
	SDL_Surface *deplacement[16];
	SDL_Surface *deplacement_turbo[16];
}Entite;



void ecrire_nombreFichier(char *nom,int indice);
void lire_nombreFichier(char *nom,int *indice);
void ajouter_position(char *nom,SDL_Rect position_joueur,SDL_Rect position_camera,int direction,int turbo);
void lire_position(FILE *fi,char *nom,Entite *boss);
void ouvrir_fichier(FILE **fi,char *nom );
void fermer_fichier(FILE **fi,char *nom);

void initialiser_boss(Entite *e);
void afficher_boss(Entite e,SDL_Surface *ecran,SDL_Rect position_camera);
void deplacement_entite(Entite *e,SDL_Surface *fond_collision);
void animation_boss(Entite *boss);
void deplacement_boss(Entite *boss,int indice,FILE *fi);


#endif
