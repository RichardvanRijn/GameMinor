#include "level.h"
#include <iostream>
#include "Ogre.h"
#include "raam.h"
#include "door.h"
#include "useableobject.h"
#include <algorithm>
#include "OgreOverlayManager.h"
#include "DomSystem.h"
#include "OgreQuaternion.h"
#include <regex>

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
	
	/*if (!toDoList.empty() && GrannyGuard->getState() == IDLE){
		GrannyGuard->setState(BUSY);
	}*/

	Controller::tick(delta);   
	bool playerWantsToUse = false;

	player->tick(playerWantsToUse);
	
	for (UINT8 i = 0; i != UseableObjects.size(); ++i) {
		UseableObjects[i]->tick();
	}	

	/*Raam* window = NULL;
	
	auto iteratorToWindow = std::find_if(UseableObjects.begin(), UseableObjects.end(), [](UseableObject* object) {
			return ((dynamic_cast<Raam*>(object)) != NULL);
		}
	);

	if (iteratorToWindow != UseableObjects.end())  {
		window = dynamic_cast<Raam*>(*iteratorToWindow);

		if (m_keyboard->isKeyDown(KC_FKEY) && window->isBlocked()) {
			gkGameObject* obstruction = window->getObstruction();
			window->removeObstruction();
			UseableObjects.push_back(new UseableObject(obstruction, true));
		}
			
	}*/

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
				std::string objectName = objectToInteract->getObjName();
				std::tr1::regex trashCanRegex("Prullenbak");

				if ((window = dynamic_cast<Raam*>(objectToInteract)) != NULL 
					&& player->getPickedUpItem() != NULL 
					&& window->isOpen() && !window->hasObstruction()) 
				{					
					gkGameObject* obstructionObject = player->getPickedUpItem()->getObj();
					UseableObjects.erase(std::find(UseableObjects.begin(), UseableObjects.end(), player->getPickedUpItem()));
					player->releaseItem();
					window->setObstruction(obstructionObject);					
				}
				else {
					ov->hide();
					objectToInteract->interact();
					std::string string = objectToInteract->getObjName();
				}
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

std::deque <UseableObject*>& Level::giveList(){
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
	bool stop = false;

	for (int i = 0; i != 10; i++){
		std::string doorName = "deur.";
		std::string doorAnim = "Deuropen.";
		std::string windowName = "Raam.";
		std::string windowAnim = "RaamAction.";
		std::string windowBoxName = "WindowBox.";
		std::string panName = "Pan.";
		std::string counter = "00";
		
		counter += std::to_string(i);
		windowName += counter;
		windowAnim += counter;
		windowBoxName += counter;
		doorName += counter;
		doorAnim += counter;
		panName += counter;

		gkGameObject *object = NULL;

		if ((object = m_scene->getObject(doorName)) != NULL) {
			const char* anim = doorAnim.c_str();
			UseableObjects.push_back(new Door(object, false, anim));
		}
		if ((object = m_scene->getObject(windowName)) != NULL) {
			const char* anim = windowAnim.c_str();
			UseableObjects.push_back(new Raam(object, false, anim, m_scene->getObject(windowBoxName)));
		}
		if ((object = m_scene->getObject(panName)) != NULL) {
			UseableObjects.push_back(new UseableObject(object, true));
		}
	}

	//UseableObjects.push_back(new UseableObject(m_scene->getObject("Pan.001"), true));
	UseableObjects.push_back(new UseableObject(m_scene->getObject("Muis"), true));
	//UseableObjects.push_back(new Raam(m_scene->getObject("Raam.000"), false, "RaamAction.000", m_scene->getObject("WindowBox.000")));
	
	m_scene->getManager()->setSkyDome(true, "TestScriptSky", 8, 10, 2000, true, Ogre::Quaternion(.707,.707,0,0));
}