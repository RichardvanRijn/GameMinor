#include "level.h"
#include <iostream>
#include "Ogre.h"

Level::Level(char* lvlPath) :
    Controller(lvlPath)    
{

}

void Level::tick(gkScalar delta)
{        
	Controller::tick(delta);   
	bool playerWantsToUse = false;

	player->tick(playerWantsToUse);

	if (playerWantsToUse){
		gkWindow* mainWindow = gkWindowSystem::getSingletonPtr()->getMainWindow();
		Ogre::Ray* ray = player->getView()->getView()->getCamera()->getCameraToViewportRay();
		Ogre::RaySceneQuery* rayQuery = m_scene->getManager()->createRayQuery(*ray);
		rayQuery->setSortByDistance(true);
	}
}

void Level::loadLevel()
{
    Controller::loadLevel();	
	
	player = new Player(m_scene->getObject("banaan"), m_scene->getObject("Camera")->getCamera());	
	player->setKeyboard(m_keyboard);
	player->setMoveSpeed(2);
	player->getView()->setViewControl(m_mouse);
}