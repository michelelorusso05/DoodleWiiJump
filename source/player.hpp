/*
	player.hpp

	Player class that extends the entity class, handles pretty
	much every event related to the player
*/

#include <grrlib.h>
#include <stdlib.h>
#include <vector>

#include "entity.hpp"
#include "platform.hpp"

class Player : public Entity {
public:
	// Fixed delta for moving right and left
	const int velocity = 5;

	// Class constructor
	Player(int x, int y, GRRLIB_texImg *textureRightParam, GRRLIB_texImg *textureLeftParam);
	// Update function
	void Update();
	// Collision detection
	void CheckCollisionWithPlatform(std::vector<Platform> platforms);
	// Set movement for the X axis (also handles the turning right/left animation)
	void SetX(int x);
	// Reset function
	void Reset(Vector2 newPos);
	// Returns true if moving down, return false otherwise
	bool IsFalling() { return deltaY > 0; }

private:
	// Textures facing right and left
	GRRLIB_texImg *textureRight;
	GRRLIB_texImg *textureLeft;
	float deltaX = 0;
	// Set to upwards movement for the first frame
	float deltaY = -13;
	bool onGround = true;
};