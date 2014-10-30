#include "level.h"
#include <regex>
#include "OgreFontManager.h"
#include "menu.h"

Level::Level(char* lvlPath) :
    Controller(lvlPath)    
{
	
}

Level::~Level() {
	UseableObjects.clear();

	//delete GUImanager;
	//delete player;
	//delete GrannyGuard;
	//delete progressSystem;
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

	GUImanager = new GUIman;
	GrannyGuard = new DomSystem;
	progressSystem = new ProgressSystem(GrannyGuard, GUImanager, 100, 1, 900000, 1000, 5);

	for (int i = 0; i != 25; i++){
		std::string doorName = "deur.";
		std::string doorAnim = "Deuropen.";
		std::string windowName = "Raam.";
		std::string windowAnim = "RaamAction.";
		std::string windowBoxName = "WindowBox.";
		std::string panName = "Pan.";
		std::string trashcanName = "Prullenbak.";
		std::string pillName = "Pil.";
		std::string toasterName = "Broodrooster.";
		std::string stoveSwitchName = "Knop.";
		std::string stoveSwitchAnim = "KnopAction.";
		std::string counter;

		if (i < 10)
			counter = "00";
		else if (i >= 10)
			counter = "0";

		counter += std::to_string(i);
		windowName += counter;
		toasterName += counter;
		windowAnim += counter;
		windowBoxName += counter;
		doorName += counter;
		stoveSwitchName += counter;
		stoveSwitchAnim += counter;
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
		if ((object = m_scene->getObject(toasterName)) != NULL)
			UseableObjects.push_back(new PickableObject(object));
		if ((object = m_scene->getObject(stoveSwitchName)) != NULL) {
			const char* anim = stoveSwitchAnim.c_str();
			UseableObjects.push_back(new Door(object, anim));
		}
	}

	//UseableObjects.push_back(new UseableObject(m_scene->getObject("Pan.001"), true));
	UseableObjects.push_back(new PickableObject(m_scene->getObject("Muis")));
	//UseableObjects.push_back(new Raam(m_scene->getObject("Raam.000"), false, "RaamAction.000", m_scene->getObject("WindowBox.000")));

	/*Ogre::ResourceGroupManager::getSingletonPtr();
	Ogre::OverlayManager* mg = Ogre::OverlayManager::getSingletonPtr();
	Ogre::Overlay* overlay = mg->getByName("GameOverlay");
	overlay->show();

	Ogre::OverlayElement* button = mg->getOverlayElement("ButtonOverlay");
	Ogre::OverlayElement* moneyText = mg->getOverlayElement("MoneyOverlay");
	Ogre::OverlayElement* healthText = mg->getOverlayElement("HealthOverlay");
	*/


	m_scene->getManager()->setSkyDome(true, "TestScriptSky", 8, 10, 2000, true, Ogre::Quaternion(.707, .707, 0, 0));
}

void Level::tick(gkScalar delta)
{        
	Controller::tick(delta);

	GrannyGuard->activate(); 
	progressSystem->tick();
	 
	bool playerWantsToUse = false;
	
	if (progressSystem->getHitPoints() != 0)
		player->tick(playerWantsToUse);
	else {
		GUImanager->showEndGame();

		if (m_keyboard->isKeyDown(KC_RETKEY)) {
			m_keyboard->clearKey(KC_RETKEY);
			gkEngine::getSingletonPtr()->requestExit();
		}
	}
	
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

	/*Ogre::OverlayManager* mg = Ogre::OverlayManager::getSingletonPtr();
	Ogre::OverlayElement* button = mg->getOverlayElement("ButtonOverlay");
	Ogre::OverlayElement* moneyText = mg->getOverlayElement("MoneyOverlay");
	Ogre::OverlayElement* healthText = mg->getOverlayElement("HealthOverlay");

	Ogre::OverlayManager::getSingletonPtr()->getOverlayElement("MoneyOverlay")->setCaption("$100");
	moneyText->setCaption("$100");
	moneyText->show();
	
	healthText->setCaption("73%");
	healthText->show();*/

//	GUImanager->setHealthCaption("73%");
//	GUImanager->setMoneyCaption("$456");
//	testing->show();
	

//	Ogre::OverlayContainer* testing = ov->getChild("GameOverlayText");
//	Ogre::OverlayElement* text = ov->getChild("GameOverlayText")->getChild("HelloWorldText");

//	button->show();
	//Ogre::ResourceManager::ResourceMapIterator font = Ogre::FontManager::getSingleton().getResourceIterator();

/*	while (font.hasMoreElements())
	{
		font.getNext()->load();
	}
*/
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
		GUImanager->showButtonE(true);
		if (playerWantsToUse) {
			if (objectToUse->isPickableObject(objectToUse)) {// dan is objectToUse een PickableObject
				PickableObject* tempPickableObj = dynamic_cast <PickableObject*> (objectToUse);
				if (tempPickableObj->isPickable())
					player->setPickedUpItem(tempPickableObj);
			}
			else if (InteractableObject* tempInteractObj = dynamic_cast <InteractableObject*> (objectToUse))
			{				
				Raam *window = NULL;				

				if ((window = dynamic_cast<Raam*>(tempInteractObj)) != NULL
					&& player->getPickedUpItem() != NULL
					&& window->isOpen() && !window->hasObstruction())
				{
					PickableObject* obstructionObject = player->getPickedUpItem();
					obstructionObject->setPickable(false);
					//UseableObjects.erase(std::find(UseableObjects.begin(), UseableObjects.end(), player->getPickedUpItem()));
					player->releaseItem();
					window->setObstruction(obstructionObject);
					GrannyGuard->addObject(window);
				}				
				else {
					GUImanager->showButtonE(false);
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
						progressSystem->setHitPoints(progressSystem->getHitPoints() - 20);
					}
				}
			}
		}
	}
	else
		GUImanager->showButtonE(false);

	delete rayQuery;
}
