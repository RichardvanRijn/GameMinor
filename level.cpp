#include "level.h"
#include <iostream>

Level::Level(char* lvlPath) :
    Controller(lvlPath)    
{

}

void Level::tick(gkScalar delta)
{        
	Controller::tick(delta);   

	player->tick();
}

void Level::loadLevel()
{
    Controller::loadLevel();	
	
	player = new Player(m_scene->getObject("banaan"), m_scene->getObject("Camera")->getCamera());	
	player->setKeyboard(m_keyboard);
	player->setMoveSpeed(2);
	player->getView()->setViewControl(m_mouse);
}