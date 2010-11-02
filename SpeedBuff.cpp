/*
 *  SpeedBuff.cpp
 *  WizardBattle
 */

#include "SpeedBuff.h"


SpeedBuff::SpeedBuff(Wizard* Caster_, ImageManager& ImageManager_)
{
	Caster = Caster_;
	this->SetImage(*ImageManager_.Get("Data/Spells/SpeedBuff.png"));
	this->SetPosition(Caster->GetPosition());
	timeLeft = 100;
	Caster->speed += 5;
}

bool SpeedBuff::Act(const TileMap& TileMap_, CollisionManager& CollisionManager_)
{
	timeLeft--;
	this->SetPosition(Caster->GetPosition());
	
	if(timeLeft == 0)
	{
		Caster->speed -= 5;
		return false;
	}
	
	return true;
}

bool SpeedBuff::clear(ImageManager& ImageManager_)
{
	return ImageManager_.release("Data/Spells/SpeedBuff.png");
}

