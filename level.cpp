#include "level.h"
#include <iostream>
#include "Ogre.h"
#include "door.h"
#include "raam.h"
#include <algorithm>
#include "OgreOverlayManager.h"

Level::Level(char* lvlPath) :
    Controller(lvlPath)    
{

}

Level::~Level() {
	interactableObjects.clear();
}

void Level::tick(gkScalar delta)
{        
	Controller::tick(delta);   
	DetectionResult spottedObjects;

	player->tick(spottedObjects);
	
	/*if (spottedObjects.size() != 0) {
		InteractableObject* objectToInteract = findInteractableObject(spottedObjects);

		bool playerWantsToUse = false;
		player->tick(playerWantsToUse);

		if (playerWantsToUse) {
			if (objectToInteract->isPickable())
				player->setPickedUpItem(objectToInteract);
			else
				objectToInteract->interact();
		}
	}*/

	/*if (m_keyboard->isKeyDown(KC_GKEY) && player->getPickedUpItem() != NULL)
		player->dropItem();


	Ogre::ResourceGroupManager::getSingletonPtr();
	Ogre::OverlayManager* mg = Ogre::OverlayManager::getSingletonPtr();
	Ogre::Overlay* ov = mg->getByName("TestScriptOverlay");

	Ogre::Ray ray(player->getView()->getViewPosition(), -(player->getView()->getViewDirection()));
	Ogre::RaySceneQuery* rayQuery = m_scene->getManager()->createRayQuery(ray);
	rayQuery->setSortByDistance(true);

	Ogre::RaySceneQueryResult& result = rayQuery->execute();
	Ogre::RaySceneQueryResult::iterator resultIterator, endOfResult;

	InteractableObject* playerObject = player->getPickedUpItem();
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

	InteractableObject* objectToInteract = NULL;

	for (resultIterator = result.begin(); resultIterator != endOfResult; resultIterator++) {
		std::cout << "Object: " + resultIterator->movable->getName() << ", distance: " << resultIterator->distance << std::endl;
		
		gkGameObject* object = m_scene->getObject(resultIterator->movable->getName());

		for (auto currentObj = interactableObjects.begin(); currentObj != interactableObjects.end(); ++currentObj) {
			InteractableObject* currentObject = (*currentObj);

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
			else
				objectToInteract->interact();
		}
	}
	else
		ov->hide();

	delete rayQuery;*/
}

InteractableObject* Level::findInteractableObject(DetectionResult& spottedObjects) {		
	DetectionIterator positionOfObject;//std::find_if(spottedObjects.begin(), spottedObjects.end(), std::bind1st(std::mem_fun(&Level::isInteractable), this));

	for (positionOfObject = spottedObjects.begin(); positionOfObject != spottedObjects.end(); ++positionOfObject) {
		gkGameObject* object = m_scene->getObject(positionOfObject->movable->getName());

		for (auto currentObj = interactableObjects.begin(); currentObj != interactableObjects.end(); ++currentObj) {
			InteractableObject* currentObject = *(currentObj);

			if (currentObject->getObj() == object)
				return currentObject;
		}
	}

	return NULL;

}

bool Level::isInteractable(DetectedObject object) const {
	return(std::find_if(interactableObjects.begin(), interactableObjects.end(), [object](InteractableObject* interactable) {
			return(interactable->getObjName() == object.movable->getName());
		}
	) != interactableObjects.end());
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
		interactableObjects.push_back(new Door(m_scene->getObject(name), false, anim));
	}

	interactableObjects.push_back(new InteractableObject(m_scene->getObject("Pan.001"), true));
	interactableObjects.push_back(new InteractableObject(m_scene->getObject("Muis"), true));
	interactableObjects.push_back(new Raam(m_scene->getObject("Raam"), false, "RaamAction"));
}