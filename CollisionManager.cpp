/*
 *  CollisionManager.cpp
 *  WizardBattle
 */

#include "CollisionManager.h"

using namespace sf;

CollisionManager::CollisionManager() {}

Collisionable* CollisionManager::Test(int x, int y)
{
	IntRect currentHitBox;
	Vector2f currentPosition;
	for(int i=0; i<Collisionables.size(); i++)
	{
		currentPosition = Collisionables[i]->GetPosition();
		currentHitBox = Collisionables[i]->GetHitBox();
		if(x > (currentPosition.x + currentHitBox.Left) &&
		   x < (currentPosition.x + currentHitBox.Right) &&
		   y > (currentPosition.y + currentHitBox.Top) &&
		   y < (currentPosition.y +currentHitBox.Bottom))
			return Collisionables[i];
	}
	
	return NULL;	
}

void CollisionManager::add(Collisionable* ToAdd)
{
	Collisionables.push_back(ToAdd);
}

