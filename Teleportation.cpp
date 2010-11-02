/*
 *  Teleportation.cpp
 *  WizardBattle
 */

#include "Teleportation.h"

using namespace sf;

Teleportation::Teleportation(Vector2f Position, ImageManager& ImageManager_)
{
	this->SetImage(*ImageManager_.Get("Data/Spells/SpeedBuff.png"));
	this->SetPosition(Position);
	timeLeft = 50;
}

bool Teleportation::Act(const TileMap& TileMap_, CollisionManager& CollisionManager_)
{
	timeLeft--;
	Color currentColor = this->GetColor();
	currentColor.a -= 255/50;
	if(currentColor.a <= 0)
		return false;
	else
		this->SetColor(currentColor);
	return true;
}

bool Teleportation::clear(ImageManager& ImageManager_)
{
	return ImageManager_.release("Data/Spells/SpeedBuff.png");
}