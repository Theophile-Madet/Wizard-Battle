/*
 *  Collisionable.cpp
 *  WizardBattle
 */

#include "Collisionable.h"

using namespace sf;

Collisionable::Collisionable()
{
	HitBox = this->GetSubRect();
}

Collisionable::Collisionable(IntRect HitBox_)
{
	HitBox = HitBox_;
}

const IntRect& Collisionable::GetHitBox()
{
	return HitBox;
}