/*
 *  TileMap.h
 *  WizardBattle
 */

#ifndef DEF_TILEMAP
#define DEF_TILEMAP

#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "define.h"
#include "ImageManager.h"
#include "tinyxml.h"

struct Tile
{
	const sf::Image* Image_;
	std::string sourceFile;
	bool blocksCharacters;
	bool blocksSpells;
	Tile(const sf::Image* sourceImage) {
		Image_ = sourceImage;
		sourceFile="empty";
		blocksCharacters = false;
		blocksSpells = false;
	}
};

class TileMap
{
	public:
	TileMap(std::string sourceFile, ImageManager& ImageManager_);
	bool changeTile(int x, int y, int newValue);
	void draw(sf::RenderWindow &Window);
	void clear(ImageManager& ImageManader_);
	bool blocksCharacters(int x, int y) const;
	bool blocksSpells(int x, int y) const;
	int getWidth() const;
	int getHeight() const;
	
	private:
	std::vector<std::vector<int> > Tiles;
	std::vector<Tile> TileSet;
	sf::Sprite Sprite_;
};

#endif

