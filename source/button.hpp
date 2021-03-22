/*
	button.hpp

	Button class that extends the entity class, handles the states of the buttons
*/

#pragma once

#include <grrlib.h>
#include <stdlib.h>
#include <string>

#include "entity.hpp"

class Button : public Entity {
public:
	// Class constructors
	// Button that uses a sprite
	Button(int x, int y, GRRLIB_texImg *texture) :Entity{ x, y, texture } {}
	// Button that uses text
	Button(int x, int y, GRRLIB_ttfFont *_font, const std::string _text) :Entity{x, y} {
		font = _font;
		text = _text;
	}
	void SetHighlighted(bool state);
	void SetSelected(bool state);
	void Render();
private:
	bool highlighted = false;
	bool selected = false;
	GRRLIB_ttfFont *font;
	std::string text;
};