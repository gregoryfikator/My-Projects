#include "Resources.h"

Resources::Resources()
{
	background = al_load_bitmap("data//textures//menu.png");
	cursor = al_load_bitmap("data//textures//cursor.png");
	heroWarrior = al_load_bitmap("data//textures//war.jpg");
	heroWizard = al_load_bitmap("data//textures//wiz.jpg");

	ui_eq = al_load_bitmap("data//textures//ui_eq.png");
	ui_eq_list = al_load_bitmap("data//textures//ui_eq_list.png");
	ui_eq_wear = al_load_bitmap("data//textures//ui_eq_wear.png");
	ui_quick = al_load_bitmap("data//textures//ui_quick.png");
	ui_xp_bar = al_load_bitmap("data//textures//ui_xp_bar.png");
	ui_bin = al_load_bitmap("data//textures//ui_bin.png");

	soundtrack1 = al_load_sample("data//sounds//main00.ogg");
	soundtrack2 = al_load_sample("data//sounds//main01.ogg");

	experienceThreshold[0] = 50;
	experienceThreshold[1] = 100;
	experienceThreshold[2] = 150;
	experienceThreshold[3] = 200;
	experienceThreshold[4] = 25000;
}

Resources::~Resources()
{
	al_destroy_bitmap(ui_bin);
	al_destroy_bitmap(ui_xp_bar);
	al_destroy_bitmap(ui_quick);
	al_destroy_bitmap(ui_eq_wear);
	al_destroy_bitmap(ui_eq_list);
	al_destroy_bitmap(ui_eq);

	al_destroy_bitmap(heroWizard);
	al_destroy_bitmap(heroWarrior);
	al_destroy_bitmap(cursor);
	al_destroy_bitmap(background);

	al_destroy_sample(soundtrack1);
	al_destroy_sample(soundtrack2);
}
