/*
	button.cpp

	Implementation file for button.hpp
*/

#include <grrlib.h>
#include <stdlib.h>
#include <vector>

#include "button.hpp"

void Button::SetHighlighted(bool state) {
	Button::highlighted = state;
}

void Button::SetSelected(bool state) {
	Button::selected = state;
}

void Button::Render() {
	// The button has a graphic
	if (Button::text.empty())
	{
		if (Button::highlighted)
		{
			GRRLIB_DrawImg(Entity::position.x, Entity::position.y, Entity::sprite, 0, aspectRatioX, 1, 0xE4A9B2FF);
		}
		else
			GRRLIB_DrawImg(Entity::position.x, Entity::position.y, Entity::sprite, 0, aspectRatioX, 1, 0xFFFFFFFF);
	}
	// The button uses text
	else
	{
		if (Button::highlighted)
		{
			GRRLIB_PrintfTTF(Button::position.x, Button::position.y, Button::font, Button::text.c_str(), 20, 0x000000FF);
		}
		else if (Button::selected)
		{
			GRRLIB_PrintfTTF(Button::position.x, Button::position.y, Button::font, Button::text.c_str(), 20, 0xFF0000FF);
		}
		else
		{
			GRRLIB_PrintfTTF(Button::position.x, Button::position.y, Button::font, Button::text.c_str(), 20, 0x888888FF);
		}
	}
}