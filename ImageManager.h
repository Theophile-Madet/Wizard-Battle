/*
 *  ImageManager.h
 *  WizardBattle
 */

#ifndef DEF_IMAGEMANAGER
#define DEF_IMAGEMANAGER

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class ImageManager
{
	public:
	ImageManager();
	~ImageManager();
	const sf::Image* Get(std::string imageName); 
	bool release(std::string imageName);
	bool release(sf::Image* ImageToBeReleased);
	int countOwners(std::string imageName);
	
	private:
	std::vector<sf::Image*> ImageList;
	std::vector<std::string> imagesNames;
	std::vector<int> imagesOwners;
};

#endif
