#include "GUIman.h"


GUIman::GUIman()
{
	
	GameOverlay = Ogre::OverlayManager::getSingletonPtr()->getByName("GameOverlay");
	GameOverlay->show();

	HealthOverlay = Ogre::OverlayManager::getSingletonPtr()->getOverlayElement("HealthOverlay");
	MoneyOverlay = Ogre::OverlayManager::getSingletonPtr()->getOverlayElement("MoneyOverlay");
	Button = Ogre::OverlayManager::getSingletonPtr()->getOverlayElement("ButtonOverlay");

	
	HealthOverlay->show();
	MoneyOverlay->show();
}


GUIman::~GUIman()
{
	GameOverlay->hide();
	HealthOverlay->hide();
	MoneyOverlay->hide();
}

void GUIman::setHealthCaption(const char* newCaption){
	HealthOverlay->setCaption(newCaption);
}

void GUIman::setMoneyCaption(const char* newCaption){
	MoneyOverlay->setCaption(newCaption);
}

void GUIman::showButtonE(bool show){
	if (show)
		Button->show();

	if (!show)
		Button->hide();
}
