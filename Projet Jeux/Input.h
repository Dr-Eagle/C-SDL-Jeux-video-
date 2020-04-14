#ifndef _INPUT_H_
#define _INPUT_H_

typedef struct input
{
	int tab_clavier[11];
	int tab_claviersolo[5];
	char key[SDLK_LAST];
}input;

void initialiser_input_multi(input *touch);
void recuperer_touch_multi(input *touch,SDL_Event press);

void initialiser_input(input *touch);
void recuperer_touch(input *touch,SDL_Event press);

#endif