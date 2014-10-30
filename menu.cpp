#include "menu.h"
#include "OgreOverlayManager.h"
#include <regex>
#include "level.h"

Menu::Menu(char* lvlPath) :
	Controller(lvlPath),
	menuPosition(0)
{
	overlayManagerMenu = Ogre::OverlayManager::getSingletonPtr();
	defaultColour = Ogre::ColourValue(0.6, 0.6, 0.6);
	highlightColour = Ogre::ColourValue(1.0, 1.0, 1.0);
}


Menu::~Menu()
{	
	//Ogre::OverlayManager::getSingletonPtr()->destroyAllOverlayElements();

	for (int i = 0; i != menuButtons.size(); ++i)
		menuButtons[i]->hide();

	menuStandard->hide();
	tutorial->hide();
	credits->hide();

	//overlayManagerMenu->destroy(menuStandard->getName());
	//overlayManagerMenu->destroy(tutorial->getName());
	//overlayManagerMenu->destroy(credits->getName());
	//overlayManagerMenu->destroyAll();
	//delete overlayManagerMenu;
	//delete menuStandard;
	//delete tutorial;
	//delete credits;
	//for (unsigned int i = 0; i != menuButtons.size(); ++i)
	//	delete menuButtons[i];
}

void Menu::loadLevel(){
	Controller::loadLevel();
	
	Ogre::Overlay* fullMenu= overlayManagerMenu->getByName("menuOverlays");
	fullMenu->show();

	menuButtons.push_back(overlayManagerMenu->getOverlayElement("startButtonText"));
	menuButtons.push_back(overlayManagerMenu->getOverlayElement("tutorialButtonText"));
	menuButtons.push_back(overlayManagerMenu->getOverlayElement("creditsButtonText"));
	menuButtons.push_back(overlayManagerMenu->getOverlayElement("exitButtonText"));
	
	menuStandard = overlayManagerMenu->getOverlayElement("fullMenu");
	credits = overlayManagerMenu->getOverlayElement("credits");
	tutorial = overlayManagerMenu->getOverlayElement("tutorial");

	credits->hide();
	tutorial->hide();
}

void Menu::clearHighlights() {
	for (unsigned int i = 0; i != menuButtons.size(); ++i)
		menuButtons[i]->setColour(defaultColour);
}

void Menu::highlightItem() {
	clearHighlights();

	menuButtons[menuPosition]->setColour(highlightColour);
}

void Menu::scrollUp() {
	if (menuPosition > 0)
		--menuPosition;
	else
		menuPosition = menuButtons.size() - 1;
}

void Menu::scrollDown() {
	if (menuPosition < menuButtons.size() - 1)
		++menuPosition;
	else
		menuPosition = 0;
}

void Menu::menuAction() {
	std::string menuItem = menuButtons[menuPosition]->getName();

	if (menuItem == "exitButtonText")
		gkEngine::getSingleton().requestExit();
	else if (menuItem == "startButtonText") {
		Controller* game = new Level("kamers.blend");
		game->loadLevel(this);
	}
}

void Menu::tick(gkScalar delta) {
	Controller::tick(delta);
	
	if (m_keyboard->isKeyDown(KC_UPARROWKEY)) {
		m_keyboard->clearKey(KC_UPARROWKEY);
		scrollUp();
	}
	else if (m_keyboard->isKeyDown(KC_DOWNARROWKEY)) {
		m_keyboard->clearKey(KC_DOWNARROWKEY);
		scrollDown();
	}

	highlightItem();

	if (m_keyboard->isKeyDown(KC_RETKEY)) {
		m_keyboard->clearKey(KC_RETKEY);
		menuAction();
	}

	//menuStandard->show();
}