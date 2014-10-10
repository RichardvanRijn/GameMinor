#include "level.h"
#include <iostream>
#include "Ogre.h"
#include "door.h"
#include <algorithm>

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
		Ogre::Ray ray(player->getView()->getViewPosition(), -(player->getView()->getViewDirection()));
		//Ogre::Ray ray = player->getView()->getView()->getCamera()->getCameraToViewportRay((mainWindow->getWidth()/2),(-mainWindow->getHeight()/2));
//		player->getObj()->setLinearVelocity(2 * ray.getDirection());
		
		Ogre::RaySceneQuery* rayQuery = m_scene->getManager()->createRayQuery(ray);
		rayQuery->setSortByDistance(true);

		Ogre::RaySceneQueryResult& result = rayQuery->execute();

		Ogre::RaySceneQueryResult::iterator resultIterator, endOfResult;

//		std::cout << "Size of ray result: " << result.size() << std::endl;
		
		endOfResult = std::remove_if(result.begin(), result.end(), [](Ogre::RaySceneQueryResultEntry resultObj) {
				return(resultObj.distance == 0 || resultObj.distance > 1);
			}
		);

		InteractableObject* objectToInteract = NULL;

		for (resultIterator = result.begin(); resultIterator != endOfResult; resultIterator++) {
			gkGameObject* object = m_scene->getObject(resultIterator->movable->getName());
			

			for (auto currentObj = interactableObjects.begin(); currentObj != interactableObjects.end(); ++currentObj) {
				InteractableObject* currentObject = (*currentObj);
				
				if (currentObject->getObj() == object) {
					objectToInteract = currentObject;
					break;
				}
			}

//			std::cout << "Distance to Object: " << resultIterator->distance << std::endl;
//			std::cout << "Object name: " << resultIterator->movable->getName() << std::endl;
		}

		if (objectToInteract != NULL)
			objectToInteract->interact();
	}
}

void Level::loadLevel()
{
    Controller::loadLevel();	
	
	player = new Player(m_scene->getObject("banaan"), m_scene->getObject("Camera")->getCamera());	
	player->setKeyboard(m_keyboard);
	player->setMoveSpeed(2);
	player->getView()->setViewControl(m_mouse);

	interactableObjects.push_back(new Door(m_scene->getObject("deur"), "Deuropen"));
}