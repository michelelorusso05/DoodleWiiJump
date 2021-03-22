/*
	platform.hpp

	Platform class that extends the entity class, handles the platforms behaviour
*/

#pragma once

#include <grrlib.h>
#include <stdlib.h>

#include "entity.hpp"

class Platform : public Entity {
public:
	// Class constructor
	Platform(int x, int y, GRRLIB_texImg *texture) :Entity{ x, y, texture } {}

	void Update();

	// Future features
	//bool canBreak;
	//bool canMove;
};