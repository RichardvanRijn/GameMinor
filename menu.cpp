#include "menu.h"
#include "OgreOverlayManager.h"
#include <regex>
#include "level.h"

Menu::Menu(char* lvlPath) :
	Controller(lvlPath),
	menuPosition(0),
	actualMenu(0)
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
	overlayManagerMenu->getByName("tutorialOverlays")->show();
	overlayManagerMenu->getByName("creditsOverlays")->show();


	menuButtons.push_back(overlayManagerMenu->getOverlayElement("startButtonText"));
	menuButtons.push_back(overlayManagerMenu->getOverlayElement("tutorialButtonText"));
	menuButtons.push_back(overlayManagerMenu->getOverlayElement("creditsButtonText"));
	menuButtons.push_back(overlayManagerMenu->getOverlayElement("exitButtonText"));
	
	tutorialButtons.push_back(overlayManagerMenu->getOverlayElement("tutorialBackButton"));
	tutorialButtons.push_back(overlayManagerMenu->getOverlayElement("tutorialNextButton"));
	tutorialButtons.push_back(overlayManagerMenu->getOverlayElement("tutorialPreviousButton"));

	creditsButtons.push_back(overlayManagerMenu->getOverlayElement("creditsBackButton"));

	menuItems.push_back(menuButtons);
	menuItems.push_back(tutorialButtons);
	menuItems.push_back(creditsButtons);

	menuStandard = overlayManagerMenu->getOverlayElement("fullMenu");
	credits = overlayManagerMenu->getOverlayElement("fullCredits");
	tutorial = overlayManagerMenu->getOverlayElement("fullTutorial");

	credits->hide();
	tutorial->hide();
}

void Menu::clearHighlights() {
	for (unsigned int i = 0; i != menuItems[actualMenu].size(); ++i)
		menuItems[actualMenu][i]->setColour(defaultColour);
}

void Menu::highlightItem() {
	clearHighlights();

	menuItems[actualMenu][menuPosition]->setColour(highlightColour);
}

void Menu::scrollUp() {
	if (menuPosition > 0)
		--menuPosition;
	else
		menuPosition = menuItems[actualMenu].size() - 1;
}

void Menu::scrollDown() {
	if (menuPosition < menuItems[actualMenu].size() - 1)
		++menuPosition;
	else
		menuPosition = 0;
}

void Menu::menuAction() {
	std::string menuItem = menuItems[actualMenu][menuPosition]->getName();
	menuStandard->hide();
	menuPosition = 0;

	std::tr1::regex checkStart("start");
	std::tr1::regex checkTutorial("tutorialButton");
	std::tr1::regex checkCredits("creditsButton");
	std::tr1::regex checkExit("exitButton");
	std::tr1::regex checkBack("Back");
	std::tr1::regex checkNext("tutorialNext");
	std::tr1::regex checkPrevious("tutorialPrevious");

	if (std::regex_search(menuItem.begin(), menuItem.end(), checkStart)) {
		Controller* game = new Level("kamers.blend");
		game->loadLevel(this);
	}
	else if (std::regex_search(menuItem.begin(), menuItem.end(), checkTutorial)){
		actualMenu = 1;
		tutorialSection = 1;
		tutorial->show();
		overlayManagerMenu->getOverlayElement("tutorialTextBox1")->show();
		overlayManagerMenu->getOverlayElement("tutorialTextBox2")->hide();
		overlayManagerMenu->getOverlayElement("tutorialTextBox3")->hide();
	}
	else if (std::regex_search(menuItem.begin(), menuItem.end(), checkCredits)){
		actualMenu = 2;
		tutorial->hide();
		menuStandard->hide();
		credits->show();
	}
	else if (std::regex_search(menuItem.begin(), menuItem.end(), checkExit)){
		gkEngine::getSingleton().requestExit();
	}
	else if (std::regex_search(menuItem.begin(), menuItem.end(), checkBack)){
		actualMenu = 0;
		tutorial->hide();
		credits->hide();
		menuStandard->show();
	}
	else if (std::regex_search(menuItem.begin(), menuItem.end(), checkNext)){
		tutorial->show();
		overlayManagerMenu->getOverlayElement(getCurrentSection())->hide();
		overlayManagerMenu->getOverlayElement(getNextSection())->show();
	}
	else if (std::regex_search(menuItem.begin(), menuItem.end(), checkPrevious)){
		tutorial->show();
		overlayManagerMenu->getOverlayElement(getCurrentSection())->hide();
		overlayManagerMenu->getOverlayElement(getPreviousSection())->show();
	}
}

std::string Menu::getCurrentSection(){
	std::string hidingSection = "tutorialTextBox";
	hidingSection += std::to_string(tutorialSection);
	return hidingSection;
}

std::string Menu::getPreviousSection() {
	if (tutorialSection == 1){
		tutorialSection = 3;
	}
	else{
		tutorialSection -= 1;
	}
	std::string hidingSection = "tutorialTextBox";
	hidingSection += std::to_string(tutorialSection);
	return hidingSection;
}

std::string Menu::getNextSection() {
	if (tutorialSection > 2){
		tutorialSection = 1;
	}
	else{
	tutorialSection += 1;
	}
	std::string hidingSection = "tutorialTextBox";
	hidingSection += std::to_string(tutorialSection);
	return hidingSection;
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