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
	void scrollUp();
	void scrollDown();
	void highlightItem();
	void clearHighlights();
	void menuAction();

	unsigned int menuPosition;

	std::vector<Ogre::OverlayElement*> menuButtons;

	Ogre::ColourValue defaultColour;
	Ogre::ColourValue highlightColour;

	Ogre::OverlayManager* overlayManagerMenu;
	Ogre::OverlayElement* menuStandard;
	Ogre::OverlayElement* tutorial;
	Ogre::OverlayElement* credits;
};

