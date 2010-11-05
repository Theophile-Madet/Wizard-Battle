/*
 *  FlyingStar.h
 *  WizardBattle
 */

#ifndef DEF_FLYINGSTAR
#define DEF_FLYINGSTAR

#include <SFML/Graphics.hpp>
#include "define.h"
#include "ImageManager.h"
#include "CollisionManager.h"
#include "Spell.h"
#include "TileMap.h"

class FlyingStar : public Spell
{
	public:
	FlyingStar(sf::Vector2f Position, Direction Dir, ImageManager& ImageManager_);
	bool Act(const TileMap& TileMap_, CollisionManager& CollisionManager_);
	bool clear(ImageManager& ImageManager_);
	
	private :
	Direction Direction_;
	int speed;
};

#endif
