/*
 *  FlyingStar.cpp
 *  WizardBattle
 */

#include "FlyingStar.h"

FlyingStar::FlyingStar(sf::Vector2f Position, Direction Dir, ImageManager& ImageManager_)
{
	this->SetPosition(Position);
	Direction_ = Dir;
	this->SetImage(*ImageManager_.Get("Data/Spells/Star.png"));
	speed = 7;
	this->SetCenter(this->GetSubRect().GetWidth()/2, this->GetSubRect().GetHeight()/2);
}

bool FlyingStar::Act(const TileMap& TileMap_, CollisionManager& CollisionManager_)
{
	int top, bottom, left, right;
	Collisionable* touched = NULL;
	
	for(int i=0; i<speed; i++)
	{
		left = this->GetPosition().x - this->GetSubRect().GetWidth()/2;
		right = left + this->GetSubRect().GetWidth(); 
		top = this->GetPosition().y - this->GetSubRect().GetHeight()/2;
		bottom = top + this->GetSubRect().GetHeight();
		
		if(Direction_ == LEFT)
		{
			if(!TileMap_.blocksSpells((left-1)/TILE_WIDTH, top/TILE_USED_HEIGHT) &&
			   !TileMap_.blocksSpells((left-1)/TILE_WIDTH, bottom/TILE_USED_HEIGHT))
			{
				this->Move(-1, 0);
				for(int i=top; i<bottom; i+=((bottom-top)/5))
				{
					touched = CollisionManager_.Test(left, i);
					if(touched != NULL)
					{
						touched->touchedBy("FlyingStar");
						return false;
					}
				}
			}
			else
				return false;
		}		
		if(Direction_ == RIGHT)
		{
			if(!TileMap_.blocksSpells((right+1)/TILE_WIDTH, top/TILE_USED_HEIGHT) &&
			   !TileMap_.blocksSpells((right+1)/TILE_WIDTH, bottom/TILE_USED_HEIGHT))
			{
				this->Move(+1, 0);
				for(int i=top; i<bottom; i+=((bottom-top)/5))
				{
					touched = CollisionManager_.Test(right, i);
					if(touched != NULL)
					{
						touched->touchedBy("FlyingStar");
						return false;
					}
				}
			}
			else
				return false;
		}
		if(Direction_ == UP)
		{
			if(!TileMap_.blocksSpells(left/TILE_WIDTH, (top-1)/TILE_USED_HEIGHT) &&
			   !TileMap_.blocksSpells(right/TILE_WIDTH, (top-1)/TILE_USED_HEIGHT))
			{
				this->Move(0, -1);
				for(int i=left; i<right; i+=((right-left)/5))
				{
					touched = CollisionManager_.Test(i, top);
					if(touched != NULL)
					{
						touched->touchedBy("FlyingStar");
						return false;
					}
				}
			}
			else
				return false;
		}
		if(Direction_ == DOWN)
		{
			if(!TileMap_.blocksSpells(left/TILE_WIDTH, (bottom+1)/TILE_USED_HEIGHT)
			   && !TileMap_.blocksSpells(right/TILE_WIDTH, (bottom+1)/TILE_USED_HEIGHT))
			{
				this->Move(0, +1);
				for(int i=left; i<right; i+=((right-left)/5))
				{
					touched = CollisionManager_.Test(i, bottom);
					if(touched != NULL)
					{
						touched->touchedBy("FlyingStar");
						return false;
					}
				}
			}
			else
				return false;
		}
		this->Rotate(1);
	}
	
	return true;
}

bool FlyingStar::clear(ImageManager& ImageManager_)
{
	return ImageManager_.release("Data/Spells/Star.png");
}