/*
 *  main.cpp
 *  WizardBattle
 */

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "define.h"
#include "TileMap.h"
#include "ImageManager.h"
#include "Wizard.h"
#include "CollisionManager.h"

int main()
{
    // Create main window
    sf::RenderWindow Window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Wizard Battle");
	Window.UseVerticalSync(true);
	
	ImageManager ImageManager_;
	CollisionManager CollisionManager_;
	
	std::string currentArena = "bridge.xml";
	TileMap TileMap_(currentArena, ImageManager_);
	
	std::vector<Wizard> Wizards;
	Wizards.push_back(Wizard(sf::Vector2f(10*TILE_WIDTH, 10*TILE_USED_HEIGHT), ImageManager_, "Boy.png"));
	Wizards.push_back(Wizard(sf::Vector2f(9*TILE_WIDTH, 9*TILE_USED_HEIGHT), ImageManager_, "CatGirl.png"));
	Wizards.push_back(Wizard(sf::Vector2f(11*TILE_WIDTH, 9*TILE_USED_HEIGHT), ImageManager_, "HornGirl.png"));
	int currentWizard = 0;
	
	for(int i=0; i<Wizards.size(); i++)
		CollisionManager_.add(&Wizards[i]);
	
	std::vector<Spell*> Spells;
	
	sf::View MainView(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	Window.SetView(MainView);
	
	bool takeScreenshot = false;
	
    // Start game loop
    while (Window.IsOpened())
    {
		Window.Clear(sf::Color::Black);
        // Process events
        sf::Event Event;
        while (Window.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                Window.Close();
			if (Event.Type == sf::Event::KeyPressed)
			{
				if (Event.Key.Code == sf::Key::Escape)
					Window.Close();
				if (Event.Key.Code == sf::Key::Add)
				{
					if(currentWizard < Wizards.size()-1)
						currentWizard++;
					else
						currentWizard = 0;
				}
				if (Event.Key.Code == sf::Key::Subtract)
				{
					if(currentWizard > 0)
						currentWizard--;
					else
						currentWizard = Wizards.size()-1;
				}	
				if (Event.Key.Code == sf::Key::F1)
					takeScreenshot = true;
			}
        }
		
		for(int i=0; i<Wizards.size(); i++)
		{
			if(i == currentWizard)
				Wizards[i].ActUsingKeyboard(Window.GetInput(), TileMap_, Spells, ImageManager_);
			else
				Wizards[i].ActUsingNetwork();
		}
		for(int i=0; i<Spells.size(); i++)
		{
			if(!Spells[i]->Act(TileMap_, CollisionManager_))
			{
				Spells[i]->clear(ImageManager_);
				delete Spells[i];
				Spells.erase(Spells.begin() + i);
			}
		}
		
		MainView.SetCenter(Wizards[currentWizard].TransformToGlobal(Wizards[currentWizard].GetCenter()));
		
        TileMap_.draw(Window);
		for(int i=0; i<Wizards.size(); i++)
		{
			if(i == currentWizard)
				Wizards[i].drawOn(Window, ImageManager_);
			else
				Window.Draw(Wizards[i]);
		}
		for(int i=0; i<Spells.size(); i++)
			Window.Draw(*Spells[i]);
		
        // Finally, display the rendered frame on screen
        Window.Display();
		if(takeScreenshot)
		{
			sf::Image Screenshot = Window.Capture();
			Screenshot.SaveToFile("../../../../../Screenshot.jpg");
			takeScreenshot = false;
		}
    }
	
	for(int i=0; i<Wizards.size(); i++)
		Wizards[i].clear(ImageManager_);
	for(int i=0; i<Spells.size(); i++)
	{
		Spells[i]->clear(ImageManager_);
		delete Spells[i];
	}
	TileMap_.clear(ImageManager_);
    return EXIT_SUCCESS;
}
