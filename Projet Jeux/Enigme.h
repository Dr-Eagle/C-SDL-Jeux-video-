#ifndef _ENIGME_H_
#define _ENIGME_H_

typedef struct Enigme
{
	SDL_Surface *enigme[18];
	SDL_Rect position;
	int reponses[18];
	int choix;
}Enigme;

void initialiser_enigmes(Enigme *e);
void afficher_enigme(Enigme e,SDL_Rect position,SDL_Surface *ecran,int indice_enigme);
int generation_enigme();
int verifier_enigme(Enigme e,int choix_user,int indice_enigme);
void modifier_score(Enigme e,int *score,int choix_user,int indice_enigme);
void saisir_reponse(SDL_Event touch,int *choix_user);
void afficher_reponse_saisie(SDL_Surface *ecran,int choix_user);



#endif
