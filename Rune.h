/*
 *  Rune.h
 *  WizardBattle
 */

#ifndef DEF_RUNE
#define DEF_RUNE

#include <SFML/Graphics.hpp>
#include "define.h"
#include "ImageManager.h"
#include "Spell.h"

class Rune : public Spell
{
	public:
	Rune(std::string runeType_, sf::Vector2f Position, ImageManager& ImageManager_);
	bool Act(const TileMap& TileMap_, CollisionManager& CollisionManager_);
	bool clear(ImageManager& ImageManager_);
	
	private:
	std::string runeType;
};

#endif

