/*
 *  AnimatedSprite.cpp
 *  WizardBattle
 */

#include "AnimatedSprite.h"

using namespace sf;

AnimatedSprite::AnimatedSprite() {}

void AnimatedSprite::draw(RenderWindow& Window)
{
	Window.Draw(*this);
}