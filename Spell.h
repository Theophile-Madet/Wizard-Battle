/*
 *  Spell.h
 *  WizardBattle
 */

#ifndef DEF_SPELL
#define DEF_SPELL

#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include "TileMap.h"
#include "ImageManager.h"
#include "CollisionManager.h"

class Spell : public AnimatedSprite
{
	public:
	Spell();
	virtual bool Act(const TileMap& TileMap_, CollisionManager& CollisionManager_) =0;
	virtual bool clear(ImageManager& ImageManager_) =0;
};
	
#endif