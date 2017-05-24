#include "Button.h"

Button::Button(int x1_new, int y1_new, int x2_new, int y2_new, bool clickable_new, bool editable_new, string label_new)
{
	x1 = x1_new;
	y1 = y1_new;
	x2 = x2_new;
	y2 = y2_new;

	clickable		= clickable_new;
	editable		= editable_new;
	cursorOnButton	= false;
	label			= label_new;
}

void Button::DrawButton(ALLEGRO_Font *allegro_font, int offSet, ALLEGRO_COLOR borderColor, int roundRadius, float borderThickness)	//flaga sterujaca kolorem (NAME_EDIT)
{
	if (!editable)
	{
		if (!clickable)
		{
			al_draw_filled_rounded_rectangle(x1, y1, x2, y2, roundRadius, roundRadius, al_map_rgba(0, 0, 0, (borderColor.a / 2)));
			al_draw_rounded_rectangle(x1, y1, x2, y2, roundRadius, roundRadius, borderColor, borderThickness);
			al_draw_text(allegro_font->font18, allegro_font->WHITE, ((x1 + x2) / 2), ((y1 + y2 - offSet) / 2), ALLEGRO_ALIGN_CENTRE, label.c_str());
			al_draw_filled_rounded_rectangle(x1, y1, x2, y2, roundRadius, roundRadius, borderColor);
		}
		else
		{
			al_draw_filled_rounded_rectangle(x1, y1, x2, y2, roundRadius, roundRadius, borderColor);

			if (!cursorOnButton)
			{
				al_draw_rounded_rectangle(x1, y1, x2, y2, roundRadius, roundRadius, borderColor, borderThickness);
				al_draw_text(allegro_font->font18, allegro_font->WHITE, ((x1 + x2) / 2), ((y1 + y2 - offSet) / 2), ALLEGRO_ALIGN_CENTRE, label.c_str());
			}
			else
			{
				al_draw_rounded_rectangle(x1, y1, x2, y2, roundRadius, roundRadius, allegro_font->DARK_RED, borderThickness - 0.5);
				al_draw_text(allegro_font->font18, allegro_font->DARK_RED, ((x1 + x2) / 2), ((y1 + y2 - offSet) / 2), ALLEGRO_ALIGN_CENTRE, label.c_str());
			}
		}
	}
	else
	{
		al_draw_filled_rounded_rectangle(x1, y1, x2, y2, roundRadius, roundRadius, borderColor);
		al_draw_rounded_rectangle(x1, y1, x2, y2, roundRadius, roundRadius, borderColor, borderThickness);

		if (!cursorOnButton)
		{
			al_draw_rounded_rectangle(x1, y1, x2, y2, roundRadius, roundRadius, borderColor, borderThickness);
			al_draw_text(allegro_font->font18, allegro_font->WHITE, ((x1 + x2) / 2), ((y1 + y2 - offSet) / 2), ALLEGRO_ALIGN_CENTRE, label.c_str());
		}
		else
		{
			al_draw_rounded_rectangle(x1, y1, x2, y2, roundRadius, roundRadius, allegro_font->DARK_RED, borderThickness - 0.5);
			al_draw_text(allegro_font->font18, allegro_font->DARK_RED, ((x1 + x2) / 2), ((y1 + y2 - offSet) / 2), ALLEGRO_ALIGN_CENTRE, label.c_str());
		}
	}
	return;
}

void Button::SetMouseOn(bool newState)
{
	cursorOnButton = newState;
	return;
}

bool Button::CompareCoords(int mouseY)
{
	if (mouseY >= y1 && mouseY <= y2)
	{
		cursorOnButton = true;
		return true;
	}
	else
	{
		cursorOnButton = false;
		return false;
	}
}

bool Button::CompareCoords(int mouseX, int mouseY)
{
	if (mouseX >= x1 && mouseX <= x2 && mouseY >= y1 && mouseY <= y2)
	{
		cursorOnButton = true;
		return true;
	}
	else
	{
		cursorOnButton = false;
		return false;
	}
}


bool Button::CompareLabel(string comparedLabel)
{
	if (label == comparedLabel)
		return true;
	return false;
}

void Button::SetLabel(string newLabel)
{
	label = newLabel;
	return;
}