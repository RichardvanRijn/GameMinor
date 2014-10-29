#pragma once
#include "Controller.h"
class Menu :
	public Controller
{
public:
	Menu(char* lvlPath);
	~Menu();

	void loadLevel();
	void tick(gkScalar delta);
private:
	Ogre::OverlayElement* menuStandard;
	Ogre::OverlayElement* tutorial;
	Ogre::OverlayElement* credits;
};

