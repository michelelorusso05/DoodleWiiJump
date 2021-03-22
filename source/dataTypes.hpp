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
	// Componenti del punto nello spazio 2D
	int x;
	int y;

	// Costruttore default
	Vector2() : x(0), y(0) {}

	// Costruttore classe
	Vector2(int posX, int posY) : x(posX), y(posY) {}

	// Aggiorna i componenti x e y
	void set(int posX, int posY) {
		x = posX;
		y = posY;
	}
};