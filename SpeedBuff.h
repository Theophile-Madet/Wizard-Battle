/*
 *  SpeedBuff.h
 *  WizardBattle
 */

#ifndef DEF_SPEEDBUFF
#define DEF_SPEEDBUFF

#include <SFML/Graphics.hpp>
#include "ImageManager.h"
#include "CollisionManager.h"
#include "Spell.h"
#include "Wizard.h"

class Wizard;

class SpeedBuff : public Spell
{
	public:
	SpeedBuff(Wizard* Caster_, ImageManager& ImageManager_);
	bool Act(const TileMap& TileMap_, CollisionManager& CollisionManager_);
	bool clear(ImageManager& ImageManager_);
	
	private:
	int timeLeft;
	Wizard* Caster;
};

#endif

