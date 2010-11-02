/*
 *  Rune.cpp
 *  WizardBattle
 */

#include "Rune.h"

using namespace std;
using namespace sf;

Rune::Rune(string runeType_, Vector2f Position, ImageManager& ImageManager_)
{
	this->SetPosition(Position);
	this->SetImage(*(ImageManager_.Get("Data/Spells/"+runeType_+"Gem.png")));
	runeType = runeType_;
}

bool Rune::Act(const TileMap& TileMap_, CollisionManager& CollisionManager_)
{
	Color currentColor = this->GetColor();
	if(currentColor.a <= 10)
		return false;
	else
	{
		currentColor.a -= 10;
		this->SetColor(currentColor);
		return true;
	}
}

bool Rune::clear(ImageManager& ImageManager_)
{
	return ImageManager_.release("Data/Spells/"+runeType+"Gem.png");
}