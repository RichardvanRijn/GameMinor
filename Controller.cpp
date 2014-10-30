#include "Controller.h"
#include "gkGameObjectManager.h"
#include "level.h"

Controller::Controller(char *lvlPath) :    
    pathToLevel(lvlPath)       
{
	m_keyboard = gkWindowSystem::getSingleton().getKeyboard();
	m_mouse    = gkWindowSystem::getSingleton().getMouse();
}

Controller::~Controller()
{
	/*if (m_scene)
		gkSceneManager::getSingleton().destroy(m_scene->getResourceHandle());*/
	gkGameObjectHashMap objects = m_scene->getObjects();

	for (int i = 0; i != objects.size(); ++i)
		m_scene->destroyObject(objects[i]);

	m_scene->getCreator()->destroy(m_scene->getResourceHandle());
}

void Controller::loadLevel(Controller* oldController) {		
	gkEngine::getSingleton().removeListener(oldController);	
	delete oldController;

	this->loadLevel();
	gkEngine::getSingleton().addListener(this);
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