/*
	entity.cpp
	
	Implementation file for entity.hpp
*/
#include <grrlib.h>

#include <stdlib.h>

#include "entity.hpp"
#include "dataTypes.hpp"

Entity::Entity(int x, int y, GRRLIB_texImg *texture)
{
	Entity::position.set(x, y);
	Entity::sprite = texture;
}

Entity::Entity(int x, int y)
{
	Entity::position.set(x, y);
}

void Entity::Render()
{
	GRRLIB_DrawImg(Entity::position.x, Entity::position.y, Entity::sprite, 0, aspectRatioX, 1, 0xFFFFFFFF);
}