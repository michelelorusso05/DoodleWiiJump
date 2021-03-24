/*
	dataTypes.hpp

	Defines the Vector2 class as well as the aspect ratio global variable.
*/

#pragma once

#ifndef _doodle_jump_
#define _doodle_jump_
extern float aspectRatioX;
#endif

class Vector2 {
public:
	// Components of a point in the 2D space
	int x;
	int y;

	// Class constructor
	Vector2() : x(0), y(0) {}

	// Class constructor (with x and y passed as parameters)
	Vector2(int posX, int posY) : x(posX), y(posY) {}

	// Update the x and y components
	void set(int posX, int posY) {
		x = posX;
		y = posY;
	}
};
