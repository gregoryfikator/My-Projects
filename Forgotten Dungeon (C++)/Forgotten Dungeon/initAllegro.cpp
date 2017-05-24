#include "initAllegro.h"

int initAllegro()	// funkcja zwaraca "1" jezeli inicjalizacja funkcjonalnosci biblioteki Allegro zakonczyla sie sukcesem, "0" jesli wystapil blad
{
	if (!al_init())
		return 0;
	if (!al_install_keyboard())
		//fprintf(stderr, "failed to initialize allegro keyboard!\n");
		return 0;
	if (!al_install_mouse())
		//fprintf(stderr, "failed to initialize allegro mouse!\n");
		return 0;
	if (!al_init_image_addon())
		//fprintf(stderr, "failed to initialize allegro image addon!\n");
		return 0;
	if (!al_init_primitives_addon())
		//fprintf(stderr, "failed to initialize allegro primitives addon!\n");
		return 0;
	al_init_font_addon();  // typ void

	if (!al_init_ttf_addon())
		//fprintf(stderr, "failed to initialize allegro ttf addon!\n");
		return 0;

	return 1;
}