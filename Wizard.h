/*
 *  Wizard.h
 *  WizardBattle
 */

#ifndef DEF_WIZARD
#define DEF_WIZARD

#include <list>
#include <SFML/Graphics.hpp>
#include "define.h"
#include "ImageManager.h"
#include "AnimatedSprite.h"
#include "TileMap.h"
#include "Spell.h"
#include "Rune.h"
#include "FlyingStar.h"
#include "SpeedBuff.h"
#include "Collisionable.h"
#include "Teleportation.h"

class SpeedBuff;

class Wizard : public AnimatedSprite, public Collisionable
{
	public:
	Wizard(const sf::Vector2f Position, 
		   ImageManager& ImageManager_, 
		   std::string sourceFile);
	void ActUsingKeyboard(const sf::Input& Keyboard, 
						  const TileMap& TileMap_, 
						  std::vector<Spell*>& Spells,
						  ImageManager& ImageManager_);
	void ActUsingNetwork(/*Add stuff here*/);
	void touchedBy(std::string toucherType);
	bool clear(ImageManager& ImageManager);
	
	private:
	int hitPoints;
	int state;
	int speed;
	std::string sourceFile;
	Direction LookDirection;
	Direction SpellDirection;
	sf::Vector2f Center;
	std::list<RuneType> RuneQueue;
	
	friend class SpeedBuff;
};

#endif



