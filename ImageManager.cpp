/*
 *  ImageManager.cpp
 *  WizardBattle
 */

#include "ImageManager.h"

using namespace std;
using namespace sf;

ImageManager::ImageManager()
{
	//Constructor does nothing;
}

ImageManager::~ImageManager()
{
	for(int i=0; i<ImageList.size(); i++)
	{
		delete ImageList[i];
		cerr<<"The owner of "<<imagesNames[i]<<" haven't released it."<<endl;
		cerr<<"Owners left : "<<imagesOwners[i]<<endl;
	}
}

const Image* ImageManager::Get(string imageName)
{
	//Return a pointer to the requiered image. Loads it if necessary.
	//Gives responsability over the image by incrementing imagesOwners.
	
	for(int i=0; i<imagesNames.size(); i++)
	{
		if(imagesNames[i] == imageName)
		{
			imagesOwners[i]++;
			return ImageList[i];
		}
	}
	
	ImageList.push_back(new Image());
	if(!(*(ImageList.back())).LoadFromFile(imageName))
	{
		cerr<<"Error while loading "<<imageName<<endl;
		return NULL;
	}
	imagesNames.push_back(imageName);
	imagesOwners.push_back(1);
	return ImageList.back();
}

bool ImageManager::release(string imageName)
{
	for(int i=0; i<imagesNames.size(); i++)
	{
		if(imagesNames[i] == imageName)
		{
			imagesOwners[i]--;
			if(imagesOwners[i] == 0)
			{
				delete ImageList[i];
				ImageList.erase(ImageList.begin() + i);
				imagesNames.erase(imagesNames.begin() + i);
				imagesOwners.erase(imagesOwners.begin() + i);
			}
			return true;
		}
	}
	
	return false;
}


bool ImageManager::release(Image* ImageToBeReleased)
{
	for(int i=0; i<imagesNames.size(); i++)
	{
		if(ImageList[i] == ImageToBeReleased)
		{
			imagesOwners[i]--;
			if(imagesOwners[i] == 0)
			{
				delete ImageList[i];
				ImageList.erase(ImageList.begin() + i);
				imagesNames.erase(imagesNames.begin() + i);
				imagesOwners.erase(imagesOwners.begin() + i);
			}
			return true;
		}
	}
	
	return false;
}

int ImageManager::countOwners(string imageName)
{
	for(int i=0; i<imagesNames.size(); i++)
	{
		if(imagesNames[i] == imageName)
			return imagesOwners[i];
	}
	return 0;
}