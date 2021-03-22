/*
	platform.cpp

	Implementation file for platform.hpp
*/

#include <grrlib.h>
#include <stdlib.h>
#include <time.h>

#include "platform.hpp"

void Platform::Update() {
	// If the platform reaches the bottom of the screen, go back up with a little variation of the y position
	if (Platform::position.y > 528)
	{
		Platform::position.x = rand() % 600;
		Platform::position.y = -50 - rand() % 30;
	}
}