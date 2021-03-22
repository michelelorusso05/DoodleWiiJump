/*
	player.cpp

	Implementation file for player.hpp
*/

#include <grrlib.h>
#include <stdlib.h>
#include <vector>

#include "player.hpp"
#include "platform.hpp"

Player::Player(int x, int y, GRRLIB_texImg *textureRightParam, GRRLIB_texImg *textureLeftParam)
	:Entity{ x, y, textureRightParam } 
{
	Player::textureRight = textureRightParam;
	Player::textureLeft = textureLeftParam;
}

void Player::Update() {
	// If player moves over the left limit of the screen, go to the right
	if (Player::position.x + deltaX < -60)
		Player::position.x = 640;
	// And viceversa
	else if (Player::position.x + deltaX > 640)
		Player::position.x = -65;
	// Move normally if the player is not crossing a limit
	else
		Player::position.x += Player::deltaX;

	// If on ground, jump
	if (onGround)
	{
		Player::deltaY = -13;
	}
	// Update Y position
	Player::position.y += Player::deltaY;
	// Gravity
	if (Player::deltaY <= 10)
		Player::deltaY += 0.4f;

}

// Handles X movement and turning animation
void Player::SetX(int x) {
	Player::deltaX = x; 
	if (x > 0)
	{
		Entity::sprite = Player::textureRight;
	}
	else if (x < 0)
	{
		Entity::sprite = Player::textureLeft;
	}
}

void Player::CheckCollisionWithPlatform(std::vector<Platform> platforms) {
	for (Platform platform : platforms) {
		// If is colliding with the upper part of the platform
		if (Player::position.y + 60 > platform.position.y 
			&& Player::position.y + 60 < platform.position.y + 11
			// And is falling
			&& Player::deltaY > 0
			// And is colliding on the X axis with the platform
			&& Player::position.x <= platform.position.x + 48 * aspectRatioX
			&& Player::position.x + 40 * aspectRatioX >= platform.position.x)
		{
			// Then the player is on a platform
			Player::onGround = true;
			Player::position.y = platform.position.y - 60;
			return;
		}
	}
	Player::onGround = false;
}

void Player::Reset(Vector2 newPos) {
	Player::position = newPos;
}