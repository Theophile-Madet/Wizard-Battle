/*
 *  AnimatedSprite.h
 *  WizardBattle
 */

#ifndef DEF_ANIMATEDSPRITE
#define DEF_ANIMATEDSPRITE

#include <SFML/Graphics.hpp>

class AnimatedSprite : virtual public sf::Sprite
{
	public:
	AnimatedSprite();
	void draw(sf::RenderWindow& Window);
	
	private:
	std::vector< std::vector<sf::IntRect> > SubRectangles;
};

#endif

