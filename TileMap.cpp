/*
 *  TileMap.cpp
 *  WizardBattle
 */

#include "TileMap.h"

using namespace std;
using namespace sf;

TileMap::TileMap(const char* sourceFile, ImageManager &ImageManager_)
{
	//Load the XML source file.
	string str = "Data/Arenas/";
	str = str + sourceFile;
	TiXmlDocument ArenaDocument(str.c_str());
	if(!ArenaDocument.LoadFile())
	{
		cerr<<"Error while loading "<<sourceFile<<endl;
		cerr<<ArenaDocument.ErrorDesc()<<endl;
	}
	
	TiXmlHandle ArenaHandle(&ArenaDocument);
	
	//Load the tile set.
	TiXmlNode* TileSetNode = ArenaHandle.FirstChild("Arena").FirstChild("TileSet").ToNode();
	TiXmlElement* TileElement = NULL;
	while(TileSetNode->IterateChildren("Tile", TileElement) != NULL)
	{
		TileElement = TileSetNode->IterateChildren("Tile", TileElement)->ToElement();
		str = "Data/Tiles/";
		str = str + TileElement->Attribute("file");
		TileSet.push_back(Tile(ImageManager_.Get(str)));
		TileSet.back().sourceFile = str;
		if(strcmp(TileElement->Attribute("isBlockingCharacters"),"true") == 0)
		{
			TileSet.back().blocksCharacters = true;
		}
		else
			TileSet.back().blocksCharacters = false;
		if(strcmp(TileElement->Attribute("isBlockingSpells"), "true") == 0)
			TileSet.back().blocksSpells = true;
		else
			TileSet.back().blocksSpells = false;
	}
	
	//Load the tile map.
	TiXmlNode* MapNode = ArenaHandle.FirstChildElement("Arena").FirstChild("Map").ToNode();
	TiXmlElement* Line = NULL;
	string tileLine;
	int temp;
	while(MapNode->IterateChildren("Line", Line) != NULL)
	{
		Line = MapNode->IterateChildren("Line", Line)->ToElement();
		tileLine = Line->Attribute("TileLine");
		Tiles.push_back(vector<int>(tileLine.size()));
		for(int i=0; i<tileLine.size(); i++)
		{
			temp = tileLine.c_str()[i] - '0';
			Tiles.back()[i] = temp;
		}
	}
}

bool TileMap::changeTile(int x, int y, int newValue)
{
	if(x < Tiles.size() && y < Tiles[0].size())
		Tiles[x][y] = newValue;
}

void TileMap::draw(RenderWindow &Window)
{
	int firstLineToDraw, lastLineToDraw, firstColumnToDraw, lastColumnToDraw, temp;
	const Vector2f&	ViewCenter = Window.GetView().GetCenter();
	firstLineToDraw = ((ViewCenter.y - (WINDOW_HEIGHT/2)) / TILE_USED_HEIGHT);
	lastLineToDraw = firstLineToDraw + (WINDOW_HEIGHT / TILE_USED_HEIGHT) + 2;
	firstColumnToDraw = ((ViewCenter.x - (WINDOW_WIDTH/2)) / TILE_WIDTH);
	lastColumnToDraw = firstColumnToDraw + (WINDOW_WIDTH / TILE_WIDTH) + 1;
	if(firstLineToDraw < 0)
		firstLineToDraw = 0;
	if(lastLineToDraw > (Tiles.size()-1))
		lastLineToDraw = Tiles.size()-1;
	if(firstColumnToDraw < 0)
		firstColumnToDraw = 0;
	if(lastColumnToDraw > Tiles[0].size() -1)
		lastColumnToDraw = Tiles[0].size() -1;
	
	for(int j=firstLineToDraw; j<=lastLineToDraw; j++)
	{
		for(int i=firstColumnToDraw; i<=lastColumnToDraw; i++)
		{
			temp = Tiles[j][i];
			Sprite_.SetPosition(i*TILE_WIDTH, (j*TILE_USED_HEIGHT) - TILE_UNUSED_HEIGHT);
			if(TileSet[temp].Image_ != NULL)
				Sprite_.SetImage(*(TileSet[temp].Image_));
			Window.Draw(Sprite_);
		}	
	}
}

void TileMap::clear(ImageManager& ImageManager_)
{
	for(int i=0; i<TileSet.size(); i++)
		ImageManager_.release(TileSet[i].sourceFile);
}

bool TileMap::blocksCharacters(int x, int y) const
{
	if(x >= Tiles[0].size() || x < 0)
		return true;
	if(y >= Tiles.size() || y < 0)
		return true;
	return TileSet[Tiles[y][x]].blocksCharacters;
}

bool TileMap::blocksSpells(int x, int y) const
{
	return TileSet[Tiles[y][x]].blocksSpells;
}

int TileMap::getWidth() const
{
	return Tiles.size();
}

int TileMap::getHeight() const
{
	return Tiles[0].size();
}