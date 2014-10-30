#include "GUIman.h"


GUIman::GUIman()
{
	
	GameOverlay = Ogre::OverlayManager::getSingletonPtr()->getByName("GameOverlay");
	GameOverlay->show();

	HealthOverlay = Ogre::OverlayManager::getSingletonPtr()->getOverlayElement("HealthOverlay");
	MoneyOverlay = Ogre::OverlayManager::getSingletonPtr()->getOverlayElement("MoneyOverlay");
	Button = Ogre::OverlayManager::getSingletonPtr()->getOverlayElement("ButtonOverlay");
	endGameOverlay = Ogre::OverlayManager::getSingletonPtr()->getOverlayElement("EndGameOverlayText");
	
	HealthOverlay->show();
	MoneyOverlay->show();
	endGameOverlay->hide();
}


GUIman::~GUIman()
{
	GameOverlay->hide();
	HealthOverlay->hide();
	MoneyOverlay->hide();
	endGameOverlay->hide();
}

void GUIman::setHealthCaption(std::string newCaption){
	
	HealthOverlay->setCaption(newCaption);
}

void GUIman::setMoneyCaption(std::string newCaption){
	MoneyOverlay->setCaption(newCaption);
}

void GUIman::showButtonE(bool show){
	if (show)
		Button->show();

	if (!show)
		Button->hide();
}

void GUIman::showEndGame() {
	endGameOverlay->show();
}
