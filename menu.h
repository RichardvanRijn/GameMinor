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
	std::string getNextSection();
	std::string getPreviousSection();
	std::string getCurrentSection();

	unsigned int menuPosition;
	int actualMenu;
	int tutorialSection;

	std::vector<Ogre::OverlayElement*> menuButtons;
	std::vector<Ogre::OverlayElement*> tutorialButtons;
	std::vector<Ogre::OverlayElement*> creditsButtons;
	std::vector<std::vector<Ogre::OverlayElement*>> menuItems;

	Ogre::ColourValue defaultColour;
	Ogre::ColourValue highlightColour;

	Ogre::OverlayManager* overlayManagerMenu;
	Ogre::OverlayElement* menuStandard;
	Ogre::OverlayElement* tutorial;
	Ogre::OverlayElement* credits;
};

