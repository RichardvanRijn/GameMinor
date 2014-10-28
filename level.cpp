#include "level.h"
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
	GrannyGuard->activate(); //GrannyGuard aanzetten

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

	UseableObject* objectToUse = NULL;

	for (resultIterator = result.begin(); resultIterator != endOfResult; resultIterator++) {
		gkGameObject* object = m_scene->getObject(resultIterator->movable->getName());

		for (auto currentObj = UseableObjects.begin(); currentObj != UseableObjects.end(); ++currentObj) {
			UseableObject* currentObject = (*currentObj);

			if (currentObject->getObj() == object) {
				objectToUse = currentObject;
				break;
			}
		}
	}

	if (objectToUse != NULL){
		ov->show();
		if (playerWantsToUse) {
			if (objectToUse->isPickable(objectToUse)) {// dan is objectToUse een PickableObject
				PickableObject* tempPickableObj = dynamic_cast <PickableObject*> (objectToUse);
				player->setPickedUpItem(tempPickableObj);
			}
			else if (InteractableObject* tempInteractObj = dynamic_cast <InteractableObject*> (objectToUse))
			{				
				Raam *window = NULL;				

				if ((window = dynamic_cast<Raam*>(tempInteractObj)) != NULL
					&& player->getPickedUpItem() != NULL
					&& window->isOpen() && !window->hasObstruction())
				{
					gkGameObject* obstructionObject = player->getPickedUpItem()->getObj();
					UseableObjects.erase(std::find(UseableObjects.begin(), UseableObjects.end(), player->getPickedUpItem()));
					player->releaseItem();
					window->setObstruction(obstructionObject);
					GrannyGuard->addObject(window);
				}				
				else {
					ov->hide();
					tempInteractObj->interact();
					GrannyGuard->addObject(tempInteractObj);
					std::string string = tempInteractObj->getObjName();
				}
			}
			else {
				std::tr1::regex trashCanRegex("Prullenbak");
				std::tr1::regex medicineRegex("Pil");
				std::string objectName = objectToUse->getObjName();
				if (player->getPickedUpItem() != NULL) {
					std::string dumpObjectName = player->getPickedUpItem()->getObjName();

					if (std::regex_search(objectName.begin(), objectName.end(), trashCanRegex)
						&& std::regex_search(dumpObjectName.begin(), dumpObjectName.end(), medicineRegex))
					{
						gkGameObject* objectToDump = player->getPickedUpItem()->getObj();
						UseableObjects.erase(std::find(UseableObjects.begin(), UseableObjects.end(), player->getPickedUpItem()));
						player->releaseItem();
						objectToDump->setPosition(objectToUse->getObj()->getWorldPosition());
						objectToDump->setOrientation(objectToUse->getObj()->getWorldOrientation());
						objectToDump->getPhysicsController()->suspend(true);
					}
				}
			}
		}
	}
	else
		ov->hide();

	delete rayQuery;
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

	GrannyGuard = new DomSystem;

	for (int i = 0; i != 10; i++){
		std::string doorName = "deur.";
		std::string doorAnim = "Deuropen.";
		std::string windowName = "Raam.";
		std::string windowAnim = "RaamAction.";
		std::string windowBoxName = "WindowBox.";
		std::string panName = "Pan.";
		std::string trashcanName = "Prullenbak.";
		std::string pillName = "Pil.";
		std::string counter = "00";
		
		counter += std::to_string(i);
		windowName += counter;
		windowAnim += counter;
		windowBoxName += counter;
		doorName += counter;
		doorAnim += counter;
		panName += counter;
		pillName += counter;
		trashcanName += counter;

		gkGameObject *object = NULL;

		if ((object = m_scene->getObject(doorName)) != NULL) {
			const char* anim = doorAnim.c_str();
			UseableObjects.push_back(new Door(object, anim));
		}
		if ((object = m_scene->getObject(windowName)) != NULL) {
			const char* anim = windowAnim.c_str();
			UseableObjects.push_back(new Raam(object, anim, m_scene->getObject(windowBoxName)));
		}
		if ((object = m_scene->getObject(panName)) != NULL) {
			UseableObjects.push_back(new PickableObject(object));
		}
		if ((object = m_scene->getObject(pillName)) != NULL)
			UseableObjects.push_back(new PickableObject(object));
		if ((object = m_scene->getObject(trashcanName)) != NULL)
			UseableObjects.push_back(new UseableObject(object));

	}

	//UseableObjects.push_back(new UseableObject(m_scene->getObject("Pan.001"), true));
	UseableObjects.push_back(new PickableObject(m_scene->getObject("Muis")));
	//UseableObjects.push_back(new Raam(m_scene->getObject("Raam.000"), false, "RaamAction.000", m_scene->getObject("WindowBox.000")));
	

	m_scene->getManager()->setSkyDome(true, "TestScriptSky", 8, 10, 2000, true, Ogre::Quaternion(.707,.707,0,0));
}