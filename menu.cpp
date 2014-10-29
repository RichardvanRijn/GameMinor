#include "menu.h"
#include "OgreOverlayManager.h"


Menu::Menu(char* lvlPath) : Controller(lvlPath)
{

}


Menu::~Menu()
{
}

void Menu::loadLevel(){
	Controller::loadLevel();
	Ogre::OverlayManager* overlayManagerMenu = Ogre::OverlayManager::getSingletonPtr();
	Ogre::Overlay* fullMenu= overlayManagerMenu->getByName("menuOverlays");
	fullMenu->show();
	menuStandard = overlayManagerMenu->getOverlayElement("fullMenu");
	credits = overlayManagerMenu->getOverlayElement("credits");
	tutorial = overlayManagerMenu->getOverlayElement("tutorial");
	credits->hide();
	tutorial->hide();
}

void Menu::tick(gkScalar delta) {
	Controller::tick(delta);
	menuStandard->show();
}