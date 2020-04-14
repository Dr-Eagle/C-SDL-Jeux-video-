#ifndef _PLAYER_H_
#define _PLAYER_H_
typedef struct Voiture
{
	int couleur;
	SDL_Rect position;
	SDL_Rect position_ro;
	float vitesse;
	int direction;
	int etat_voiture;// 0 en arret 1 en marche
	int turbo;
	int nombre_de_turbo;
	int temps_turbo;
	int delai_turbo;
	int autorisation_turbo;
	int indice_voiture;
	int angle;
	int angle_gauche;
	SDL_Surface *image_rotation_turbo;
	SDL_Surface *image_rotation;
	SDL_Surface *deplacement[16];
	SDL_Surface *deplacement_turbo[16];

}Voiture;
typedef struct Son
{
	Mix_Music *son_voiture;
	Mix_Chunk *son_collision;
	Mix_Chunk *son_horloge;
	Mix_Chunk *son_turbo;
}Son;
typedef struct Player
{
	char pseudo [30];
	int stage;
	int score;
	int pv;
	int gagner;
	int game_over;
	Voiture v;
	Son son;
}Player;

typedef struct temps
{
	int commencer;
	int temps_stage2;
	int temps_stage3;
	int pause;
}temps;


void initialiser_multi(Player p[]);
void afficher_voiture_multi(SDL_Surface *ecran,Player p[],SDL_Rect position_camera1,SDL_Rect position_camera2);
void prochaine_position2(SDL_Rect *nouvelle_position,int tab[],Voiture *v);
void afficher_score_multi(Player p[],SDL_Surface *ecran);
void gagner_multi(Player p[],SDL_Rect position_camera, SDL_Rect position_camera2);
void animation_voiture_multi(Player p[],int tab[]);
void changer_image_voiture_multi(SDL_Surface *bg_collision,SDL_Rect position_camera,Player *p) ;
void acceleration_turbo_multi(Player p[],int tab[]);
void deplacer_voiture_multi1(Voiture *v,SDL_Rect position_camera,int tab[],SDL_Rect position_bg,int coll_boss, int coll_map);
void deplacer_voiture_multi2(Voiture *v,SDL_Rect position_camera,int tab[],SDL_Rect position_bg,int coll_boss, int coll_map);
void afficher_etat_turbo_multi(SDL_Surface *ecran,Player p[]);
void modifier_score_col_multi(int collision,Player *p);


void initialiser_temps(temps *t);
void temps_jeu(temps *t);
void compter_temps_stage2(temps *t);
void compter_temps_stage3(temps *t);
void pause(temps *t);

void compte_a_rebour(int *jouer,SDL_Surface *ecran,temps *t);

void initialiser_player(Player *p);//f
void sauvegarder(char *nom_de_fichier,Player p);//mm
void ajouter_joueur(char *nom_de_fichier,Player p);//f
int  charger_parti(char *nom_de_fichier,Player *p,char *pseudo);
int  chercher_player(char *nom_de_fichier,Player p);//mm
void afficher_voiture(SDL_Surface *ecran,Player p);//mm
void deplacer_voiture(Voiture *v,SDL_Rect position_camera,int tab[],SDL_Rect position_bg,int coll_boss, int coll_map);//mm
void animation_voiture(Player *p,int tab[]);
void acceleration_turbo(Player *p,int tab[]);
void afficher_etat_turbo(SDL_Surface *ecran,Player p);
void son_voiture(Player p,int k);
void son_tic_tac(Player p,int k);
void son_turbo(Player p,int k);
void son_collision(Player p,int k);
void modifier_score_col(int collision,Player *p);//m
void afficher_score(Player p,SDL_Surface *ecran);//mm
void prochaine_position(SDL_Rect *nouvelle_position,int tab[],Voiture *v);//f
void changer_image_voiture(SDL_Surface *bg_collision,SDL_Rect position_camera,Voiture *v);//f
void deplacement_cas_enigme(SDL_Surface *bg_collision,SDL_Rect *position_camera, Voiture *v);
void gagner(Player *p,SDL_Rect position_camera);
void defaite(Player *p,temps t);
int convertir_milliseconde(int temps_milli);
void afficher_temps(temps t,SDL_Surface* ecran,int stage);


#endif