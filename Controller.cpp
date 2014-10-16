#include "Controller.h"
#include "gkGameObjectManager.h"

Controller::Controller(char *lvlPath) :    
    pathToLevel(lvlPath)       
{
	m_keyboard = gkWindowSystem::getSingleton().getKeyboard();
	m_mouse    = gkWindowSystem::getSingleton().getMouse();
}

Controller::~Controller()
{
	if (m_scene)
		gkSceneManager::getSingleton().destroy(m_scene->getResourceHandle());
}

void Controller::loadLevel()
{
    gkBlendFile* mapData = gkBlendLoader::getSingleton().loadFile(gkUtils::getFile(pathToLevel), "", "");
	m_scene = mapData->getMainScene();

	m_scene->createInstance();
}

void Controller::tick(gkScalar delta)
{    
	if (m_keyboard->isKeyDown(KC_ESCKEY))
		gkEngine::getSingleton().requestExit();   
	
}