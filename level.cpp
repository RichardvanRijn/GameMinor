#include "level.h"
#include <iostream>
#include "Ogre.h"
#include "raam.h"
#include "door.h"
#include "useableobject.h"

#include <algorithm>
#include "OgreOverlayManager.h"

#include "OgreQuaternion.h"

Level::Level(char* lvlPath) :
    Controller(lvlPath)    
{

}

Level::~Level() {
	UseableObjects.clear();
}

void Level::tick(gkScalar delta)
{        
	
	//GrannyGuard->doList();
	
	if (!toDoList.empty() && GrannyGuard->getState() == IDLE){
		GrannyGuard->setState(BUSY);
	}

	Controller::tick(delta);   
	bool playerWantsToUse = false;

	player->tick(playerWantsToUse);
	
	if (m_keyboard->isKeyDown(KC_GKEY) && player->getPickedUpItem() != NULL)
		player->dropItem();

	//if (m_keyboard->isKeyDown(KC_FKEY) && player->getPickedUpItem() != NULL)
	//	player->trowItem();

	Ogre::ResourceGroupManager::getSingletonPtr();
	Ogre::OverlayManager* mg = Ogre::OverlayManager::getSingletonPtr();
	Ogre::Overlay* ov = mg->getByName("TestScriptOverlay");

	Ogre::Ray ray(player->getView()->getViewPosition(), -(player->getView()->getViewDirection()));
	Ogre::RaySceneQuery* rayQuery = m_scene->getManager()->createRayQuery(ray);
	rayQuery->setSortByDistance(true);

	Ogre::RaySceneQueryResult& result = rayQuery->execute();
	Ogre::RaySceneQueryResult::iterator resultIterator, endOfResult;

	UseableObject* playerObject = player->getPickedUpItem();
	gkScene* scene = m_scene;

	if (playerObject != NULL) {
		endOfResult = std::remove_if(result.begin(), result.end(), [scene, playerObject](Ogre::RaySceneQueryResultEntry resultObj) {
			return(resultObj.distance == 0 || resultObj.distance > 1 || scene->getObject(resultObj.movable->getName()) == playerObject->getObj());
		}
		);
	}
	else {
		endOfResult = std::remove_if(result.begin(), result.end(), [scene, playerObject](Ogre::RaySceneQueryResultEntry resultObj) {
			return(resultObj.distance == 0 || resultObj.distance > 1);
		}
		);
	}

	UseableObject* objectToInteract = NULL;

	for (resultIterator = result.begin(); resultIterator != endOfResult; resultIterator++) {
		//std::cout << "Object: " + resultIterator->movable->getName() << ", distance: " << resultIterator->distance << std::endl;
		
		gkGameObject* object = m_scene->getObject(resultIterator->movable->getName());

		for (auto currentObj = UseableObjects.begin(); currentObj != UseableObjects.end(); ++currentObj) {
			UseableObject* currentObject = (*currentObj);

			if (currentObject->getObj() == object) {
				objectToInteract = currentObject;
				break;
			}
		}
	}

	if (objectToInteract != NULL){
		ov->show();
		if (playerWantsToUse) {
			if (objectToInteract->isPickable())
				player->setPickedUpItem(objectToInteract);
			else {
				Raam *window = NULL;
				UseableObject* playerItem = player->getPickedUpItem();

				if ((window = dynamic_cast<Raam*>(objectToInteract)) != NULL && playerItem != NULL && window->isOpen() && !window->hasObstruction()) {
					gkGameObject* obstructionObject = player->getPickedUpItem()->getObj();
					UseableObjects.erase(std::find(UseableObjects.begin(), UseableObjects.end(), player->getPickedUpItem()));
					player->releaseItem();
					window->setObstruction(obstructionObject);					
				}
				else
					objectToInteract->interact();
			}
		}
	}
	else
		ov->hide();

	delete rayQuery;
}

UseableObject* Level::giveFirstProblem() {
	if (!toDoList.empty())
		return toDoList.front();
	else
		return NULL;
}

void Level::addObject(UseableObject* object){
	toDoList.push_back(object);
}

deque <UseableObject*>& Level::giveList(){
	return toDoList;
}

void Level::loadLevel()
{
    Controller::loadLevel();	
	
	player = new Player(m_scene->getObject("banaan"), m_scene->getObject("Camera")->getCamera());	
	player->setKeyboard(m_keyboard);
	player->setMoveSpeed(2);
	player->setItemHoldPosition(gkVector3(0, -0.4, 0));

	player->getView()->setViewControl(m_mouse);
	for (int i = 0; i < 4; i++){
		std::string name = "deur.00";
		name += std::to_string(i);
		std::string anima = "Deuropen.00";
		anima += std::to_string(i);
		const char* anim = anima.c_str();	
		UseableObjects.push_back(new Door(m_scene->getObject(name), false, anim));
	}

	UseableObjects.push_back(new UseableObject(m_scene->getObject("Pan.001"), true));
	UseableObjects.push_back(new UseableObject(m_scene->getObject("Muis"), true));
	UseableObjects.push_back(new Raam(m_scene->getObject("Raam"), false, "RaamAction", m_scene->getObject("WindowBox")));

	m_scene->getManager()->setSkyDome(true, "TestScriptSky", 8, 10, 2000, true, Ogre::Quaternion(.707,.707,0,0));
}