#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <string>
#include "ALLEGRO_Font.h"

using namespace std;

class Button
{
	int		x1;
	int		y1;
	int		x2;
	int		y2;

	bool	clickable;
	bool	editable;
	bool	cursorOnButton;
	string	label;

public:
	Button(int x1_new, int y1_new, int x2_new, int y2_new, bool clickable_new, bool editable_new, string label_new);

	void DrawButton(ALLEGRO_Font *allegro_font, int offSet, ALLEGRO_COLOR borderColor, int roundRadius, float borderThickness);
	void SetMouseOn(bool newState);
	bool CompareCoords(int mouseY);
	bool CompareCoords(int mouseX, int mouseY);
	bool CompareLabel(string comparedLabel);
	void SetLabel(string newLabel);
};