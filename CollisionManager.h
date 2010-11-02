/*
 *  CollisionManager.h
 *  WizardBattle
 */


#ifndef DEF_COLLISIONMANAGER
#define DEF_COLLISIONMANAGER

#include <SFML/Graphics.hpp>
#include "Collisionable.h"

class CollisionManager
{
	public:
	CollisionManager();
	Collisionable* Test(int x, int y);
	void add(Collisionable* ToAdd);
	
	private:
	std::vector<Collisionable*> Collisionables;
};

#endif