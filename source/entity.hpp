/*
	entity.hpp

	Base class for every entity in the game
*/

#pragma once

#include <grrlib.h>
#include <stdlib.h>

#include "dataTypes.hpp"

class Entity {
public:
	// Class constructors
	Entity(int x, int y, GRRLIB_texImg *texture);
	Entity(int x, int y);
	void Render();

	Vector2 position = Vector2();

protected:
	GRRLIB_texImg *sprite;
};