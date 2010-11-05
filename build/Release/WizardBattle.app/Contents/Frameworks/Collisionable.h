/*
 *  Collisionable.h
 *  WizardBattle
 */

#ifndef DEF_COLLISIONABLE
#define DEF_COLLISIONABLE

#include <SFML/Graphics.hpp>

class Collisionable : virtual public sf::Sprite
{
	public:
	Collisionable();
	Collisionable(sf::IntRect HitBox_);
	const sf::IntRect& GetHitBox();
	virtual void touchedBy(std::string toucherType) =0;
	
	protected:
	sf::IntRect HitBox;
};

#endif