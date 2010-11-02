/*
 *  Teleportation.h
 *  WizardBattle
 */

#ifndef DEF_TELEPORTATION
#define DEF_TELEPORTATION

#include <SFML/Graphics.hpp>
#include "ImageManager.h"
#include "CollisionManager.h"
#include "Spell.h"

class Teleportation : public Spell
{
	public:
	Teleportation(sf::Vector2f Position, ImageManager& ImageManager_);
	bool Act(const TileMap& TileMap_, CollisionManager& CollisionManager_);
	bool clear(ImageManager& ImageManager_);
	
	private:
	int timeLeft;
};

#endif
