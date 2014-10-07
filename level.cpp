#include "level.h"
#include <iostream>

Level::Level(char* lvlPath) :
    Controller(lvlPath)    
{

}

void Level::tick(gkScalar delta)
{        
	Controller::tick(delta);   

	static float movespeed = 2;	
	static gkVector3 totalspeed;
	
	gkVector3 buffer = player->getObj()->getLinearVelocity();
	if (m_keyboard->isKeyDown(KC_WKEY)) {
		gkQuaternion cameraqua = m_camera->getOrientation();
		gkVector3 cameravect = (cameraqua.xAxis(), cameraqua.yAxis(), cameraqua.zAxis());
		totalspeed.x = -movespeed * cameravect.x;
		totalspeed.y = -movespeed * cameravect.y;
	}
	else if (m_keyboard->isKeyDown(KC_SKEY)){
		gkQuaternion cameraqua = m_camera->getOrientation();
		gkVector3 cameravect = (cameraqua.xAxis(), cameraqua.yAxis(), cameraqua.zAxis());
		totalspeed.x = movespeed * cameravect.x;
		totalspeed.y = movespeed * cameravect.y;
	}
	if (m_keyboard->isKeyDown(KC_AKEY)){
		gkQuaternion cameraqua = m_camera->getOrientation();
		gkVector3 cameravect = (cameraqua.xAxis(), cameraqua.yAxis(), cameraqua.zAxis());
		totalspeed.x += movespeed * cameravect.y;
		totalspeed.y += -movespeed * cameravect.x;
		totalspeed *= 0.5;
	}
	else if (m_keyboard->isKeyDown(KC_DKEY)){
		gkQuaternion cameraqua = m_camera->getOrientation();
		gkVector3 cameravect = (cameraqua.xAxis(), cameraqua.yAxis(), cameraqua.zAxis());
		totalspeed.x += -movespeed * cameravect.y;
		totalspeed.y += movespeed * cameravect.x;
		totalspeed *= 0.5;
	}
	if ((!m_keyboard->isKeyDown(KC_AKEY) && !m_keyboard->isKeyDown(KC_SKEY) && !m_keyboard->isKeyDown(KC_DKEY) && !m_keyboard->isKeyDown(KC_WKEY)) && (totalspeed != gkVector3(0, 0, 0))){
		gkVector3 reverse = player->getObj()->getLinearVelocity();
		player->getObj()->setLinearVelocity(-0.1 * reverse);
		totalspeed.x = 0;
		totalspeed.y = 0;
		totalspeed.z = buffer.z;
	}
	totalspeed.z = buffer.z;
	player->getObj()->setLinearVelocity(totalspeed);

	player->tick();
}

void Level::loadLevel()
{
    Controller::loadLevel();
	
	m_camera = m_scene->getObject("Camera")->getCamera();

	player = new Player(m_scene->getObject("banaan"), m_scene->getObject("Camera")->getCamera());	
	player->setKeyboard(m_keyboard);
	player->setMoveSpeed(2);
	player->getView()->setViewControl(m_mouse);

	//gamePlayers.push_back(player);
}