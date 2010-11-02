/*
 *  Wizard.cpp
 *  WizardBattle
 */

#include "Wizard.h"

using namespace std;
using namespace sf;

Wizard::Wizard(const Vector2f Position, ImageManager& ImageManager_, string sourceFile)
{
	this->SetImage(*(ImageManager_.Get("Data/Characters/" + sourceFile)));
	this->SetPosition(Position);
	speed = 3;
	this->sourceFile = sourceFile;
	Center = Vector2f(this->GetSubRect().GetWidth()/2, this->GetSubRect().GetHeight()/2);
	LookDirection = DOWN;
	SpellDirection = DOWN;
	hitPoints = 100;
	HitBox = this->GetSubRect();
	RuneQueue.assign(15, NONE);
}

void Wizard::ActUsingKeyboard(const Input& Keyboard, const TileMap& TileMap_, vector<Spell*>& Spells, ImageManager& ImageManager_)
{
	//Makes the wizard act using the keyboard.
	int top, bottom, left, right;
	
	//Movement
	for(int i=0; i<speed; i++)
	{
		left = this->GetPosition().x;
		right = left + this->GetSubRect().GetWidth(); 
		top = this->GetPosition().y;
		bottom = top + this->GetSubRect().GetHeight();
		
		if(Keyboard.IsKeyDown(Key::Left) && !Keyboard.IsKeyDown(Key::Right))
		{
			LookDirection = LEFT;
			if(!TileMap_.blocksCharacters((left-1)/TILE_WIDTH, top/TILE_USED_HEIGHT) &&
			   !TileMap_.blocksCharacters((left-1)/TILE_WIDTH, bottom/TILE_USED_HEIGHT))
				this->Move(-1, 0);
		}
		if(Keyboard.IsKeyDown(Key::Right) && !Keyboard.IsKeyDown(Key::Left))
		{
			LookDirection = RIGHT;
			if(!TileMap_.blocksCharacters((right+1)/TILE_WIDTH, top/TILE_USED_HEIGHT) &&
			   !TileMap_.blocksCharacters((right+1)/TILE_WIDTH, bottom/TILE_USED_HEIGHT))	
				this->Move(1, 0);
		}
		if(Keyboard.IsKeyDown(Key::Up) && !Keyboard.IsKeyDown(Key::Down))
		{
			LookDirection = UP;
			if(!TileMap_.blocksCharacters(left/TILE_WIDTH, (top-1)/TILE_USED_HEIGHT) &&
			   !TileMap_.blocksCharacters(right/TILE_WIDTH, (top-1)/TILE_USED_HEIGHT))
				this->Move(0, -1);
		}
		if(Keyboard.IsKeyDown(Key::Down) && !Keyboard.IsKeyDown(Key::Up))
		{
			LookDirection = DOWN;
			if(!TileMap_.blocksCharacters(left/TILE_WIDTH, (bottom+1)/TILE_USED_HEIGHT) &&
			   !TileMap_.blocksCharacters(right/TILE_WIDTH, (bottom+1)/TILE_USED_HEIGHT))
				this->Move(0, 1);
		}
	}
	
	//Spells
	if(Keyboard.IsKeyDown(Key::Q))
		SpellDirection = LEFT;
	if(Keyboard.IsKeyDown(Key::S))
		SpellDirection = DOWN;
	if(Keyboard.IsKeyDown(Key::D))
		SpellDirection = RIGHT;
	if(Keyboard.IsKeyDown(Key::Z))
		SpellDirection = UP;
	
	bool newRune = false;
	
	if(Keyboard.IsKeyDown(Key::A) &&
	   !Keyboard.IsKeyDown(Key::E) &&
	   !Keyboard.IsKeyDown(Key::W) &&
	   !Keyboard.IsKeyDown(Key::C) &&
	   RuneQueue.front() != RED)
	{
		RuneQueue.pop_back();
		RuneQueue.push_front(RED);
		newRune = true;
		Spells.push_back(new Rune("Red", Vector2f(left-RUNE_WIDTH, top-RUNE_HEIGHT), ImageManager_));
	}
	else if(Keyboard.IsKeyDown(Key::E) &&
			!Keyboard.IsKeyDown(Key::W) &&
			!Keyboard.IsKeyDown(Key::C) &&
			!Keyboard.IsKeyDown(Key::A) &&
			RuneQueue.front() != GREEN)
	{
		RuneQueue.pop_back();
		RuneQueue.push_front(GREEN);
		newRune = true;
		Spells.push_back(new Rune("Green", Vector2f(right, top-RUNE_HEIGHT), ImageManager_));
	}
	else if(Keyboard.IsKeyDown(Key::W) &&
			!Keyboard.IsKeyDown(Key::C) &&
			!Keyboard.IsKeyDown(Key::A) &&
			!Keyboard.IsKeyDown(Key::E) &&
			RuneQueue.front() != BLUE)
	{
		RuneQueue.pop_back();
		RuneQueue.push_front(BLUE);
		newRune = true;
		Spells.push_back(new Rune("Blue", Vector2f(left-RUNE_WIDTH, bottom), ImageManager_));
	}
	else if(Keyboard.IsKeyDown(Key::C) &&
			!Keyboard.IsKeyDown(Key::A) &&
			!Keyboard.IsKeyDown(Key::E) &&
			!Keyboard.IsKeyDown(Key::W) &&
			RuneQueue.front() != YELLOW)
	{
		RuneQueue.pop_back();
		RuneQueue.push_front(YELLOW);
		newRune = true;
		Spells.push_back(new Rune("Yellow", Vector2f(right, bottom), ImageManager_));
	}
	
	list<RuneType>::iterator currentRune;
	
	if(newRune == true)
	{
		//Flying Star
		currentRune = RuneQueue.begin();
		if(*currentRune == GREEN)
		{
			currentRune++;
			if(*currentRune == YELLOW)
			{
				currentRune++;
				if(*currentRune == RED)
				{
					Spells.push_back(new FlyingStar(this->TransformToGlobal(Center), SpellDirection, ImageManager_));
				}
			}
		}
		
		//Speed Buff
		currentRune = RuneQueue.begin();
		if(*currentRune == BLUE)
		{
			currentRune++;
			if(*currentRune == GREEN)
			{
				currentRune++;
				if(*currentRune == YELLOW)
				{
					Spells.push_back(new SpeedBuff(this, ImageManager_));
				}
			}
		}
		
		//Teleportation
		currentRune = RuneQueue.begin();
		if(*currentRune == BLUE)
		{
			currentRune++;
			if(*currentRune == YELLOW)
			{
				currentRune++;
				if(*currentRune == BLUE)
				{
					currentRune++;
					if(*currentRune == YELLOW)
					{
						currentRune++;
						if(*currentRune == BLUE)
						{
							Vector2f TargetPosition = this->GetPosition();
							if(SpellDirection == LEFT)
								TargetPosition.x -= TELEPORTATION_RANGE;
							if(SpellDirection == UP)
								TargetPosition.y -= TELEPORTATION_RANGE;
							if(SpellDirection == RIGHT)
								TargetPosition.x += TELEPORTATION_RANGE;
							if(SpellDirection == DOWN)
								TargetPosition.y += TELEPORTATION_RANGE;
							
							left = TargetPosition.x;
							right = left + this->GetSubRect().GetWidth(); 
							top = TargetPosition.y;
							bottom = top + this->GetSubRect().GetHeight();
							
							while(TileMap_.blocksCharacters(left/TILE_WIDTH, bottom/TILE_USED_HEIGHT) ||
								  TileMap_.blocksCharacters(right/TILE_WIDTH, bottom/TILE_USED_HEIGHT) ||
								  TileMap_.blocksCharacters(left/TILE_WIDTH, top/TILE_USED_HEIGHT) ||
								  TileMap_.blocksCharacters(right/TILE_WIDTH, top/TILE_USED_HEIGHT))
							{
								if(SpellDirection == LEFT)
								{
									left++;
									right++;
								}
								else if(SpellDirection == UP)
								{
									top++;
									bottom++;
								}
								else if(SpellDirection == RIGHT)
								{
									right--;
									left--;
								}
								else if(SpellDirection == DOWN)
								{
									top--;
									bottom--;
								}
							}
							TargetPosition.x = left;
							TargetPosition.y = top;
							Spells.push_back(new Teleportation(this->GetPosition(), ImageManager_));
							Spells.push_back(new Teleportation(TargetPosition, ImageManager_));
							this->SetPosition(TargetPosition);
						}
					}
				}
			}
		}
	}
}

void Wizard::ActUsingNetwork(/*stuff*/)
{
	if(hitPoints <= 0)
		this->FlipY(true);
}

bool Wizard::clear(ImageManager& ImageManager_)
{
	return ImageManager_.release(sourceFile);
}

void Wizard::touchedBy(string toucherType)
{
	if(toucherType == "FlyingStar")
		hitPoints -= FLYINGSTAR_DAMAGE;
}

void Wizard::drawOn(RenderWindow& Window, ImageManager& ImageManager_)
{
	Sprite RuneSprite;
	float x, y;
	Window.Draw(*this);
	
	list<RuneType>::iterator currentRune = RuneQueue.begin();
	for(int i=0; i<RuneQueue.size(); i++)
	{
		if(*currentRune != NONE)
		{
			switch(*currentRune)
			{
				case RED:
					RuneSprite.SetImage(*ImageManager_.Get("Data/Spells/RedGem.png"));
					break;
				case BLUE:
					RuneSprite.SetImage(*ImageManager_.Get("Data/Spells/BlueGem.png"));
					break;
				case YELLOW:
					RuneSprite.SetImage(*ImageManager_.Get("Data/Spells/YellowGem.png"));
					break;
				case GREEN:
					RuneSprite.SetImage(*ImageManager_.Get("Data/Spells/GreenGem.png"));
					break;
			}
			x = this->GetPosition().x - (WINDOW_WIDTH/2);
			x += ((WINDOW_WIDTH-RUNE_WIDTH) / RuneQueue.size()) * i;
			y = this->GetPosition().y + (WINDOW_HEIGHT/2) - RUNE_HEIGHT;
			RuneSprite.SetPosition(x, y);
			Window.Draw(RuneSprite);
			switch(*currentRune)
			{
				case RED:
					ImageManager_.release("Data/Spells/RedGem.png");
					break;
				case BLUE:
					ImageManager_.release("Data/Spells/BlueGem.png");
					break;
				case YELLOW:
					ImageManager_.release("Data/Spells/YellowGem.png");
					break;
				case GREEN:
					ImageManager_.release("Data/Spells/GreenGem.png");
					break;
			}
		}
		currentRune++;
	}
}
