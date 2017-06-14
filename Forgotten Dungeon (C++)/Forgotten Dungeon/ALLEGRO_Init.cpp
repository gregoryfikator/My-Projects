#include "ALLEGRO_Init.h"

ALLEGRO_Init::ALLEGRO_Init()
{
	if (!al_init())
		delete this;
	if (!al_install_keyboard())
		//fprintf(stderr, "failed to initialize allegro keyboard!\n");
		delete this;
	if (!al_install_mouse())
		//fprintf(stderr, "failed to initialize allegro mouse!\n");
		delete this;
	if (!al_init_image_addon())
		//fprintf(stderr, "failed to initialize allegro image addon!\n");
		delete this;
	if (!al_init_primitives_addon())
		//fprintf(stderr, "failed to initialize allegro primitives addon!\n");
		delete this;

	if (!al_install_audio()) {
		fprintf(stderr, "failed to initialize audio!\n");
	}

	if (!al_init_acodec_addon()) {
		fprintf(stderr, "failed to initialize audio codecs!\n");
	}

	if (!al_reserve_samples(1)) {
		fprintf(stderr, "failed to reserve samples!\n");
	}
}