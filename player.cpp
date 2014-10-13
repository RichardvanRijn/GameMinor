#include "player.h"
#include "interactableobject.h"

Player::Player(gkGameObject* object) :
	GameObject(object),
	view(NULL),
	pickedUpItem(NULL)
{
	
}

Player::Player(gkGameObject* object, gkCamera* cam) :
	GameObject(object),
	pickedUpItem(NULL)
{	
	//view = new View(cam);
	view = new View(cam, 0.8, -.5, .8);
}

Player::~Player()
{
	delete keyboard;
	delete view;
}

void Player::setItemHoldPosition(gkVector3 position) {
	itemPosition = position;
}

void Player::dropItem() {
	pickedUpItem = NULL;
}

void Player::setMoveSpeed(float speed) {
	moveSpeed = speed;
}

void Player::setKeyboard(gkKeyboard* board) {
	keyboard = board;
}

void Player::setView(gkCamera* cam) {
	if (view != NULL)
		view->setView(cam);
	else
		view = new View(cam);
}

void Player::setPickedUpItem(InteractableObject* item) {
	pickedUpItem = item;
}

void Player::move() {
	gkVector3 totalSpeed(0, 0, 0);
	gkVector3 buffer = getObj()->getLinearVelocity();
	gkVector3 viewDirection = view->getViewDirection();
	
	/*if (!keyboard->isKeyDown(KC_WKEY) && !keyboard->isKeyDown(KC_SKEY) && !keyboard->isKeyDown(KC_AKEY)
		&& !keyboard->isKeyDown(KC_DKEY) && (totalSpeed != gkVector3(0, 0, 0)))
	{
		//gkVector3 reverse = getObj()->getLinearVelocity();
		getObj()->setLinearVelocity(-0.1 * buffer);
		totalSpeed.x = 0;
		totalSpeed.y = 0;
		totalSpeed.z = buffer.z;
	}*/
	if (keyboard->isKeyDown(KC_WKEY)) {
		totalSpeed.x += -moveSpeed * viewDirection.x;
		totalSpeed.y += -moveSpeed * viewDirection.y;
	}
	else if (keyboard->isKeyDown(KC_SKEY)) {
		totalSpeed.x += moveSpeed * viewDirection.x;
		totalSpeed.y += moveSpeed * viewDirection.y;
	}

	if (keyboard->isKeyDown(KC_AKEY)) {
		totalSpeed.x += moveSpeed * viewDirection.y * 0.4;
		totalSpeed.y += -moveSpeed * viewDirection.x * 0.4;		
	}
	else if (keyboard->isKeyDown(KC_DKEY)) {
		totalSpeed.x += -moveSpeed * viewDirection.y * 0.4;
		totalSpeed.y += moveSpeed * viewDirection.x * 0.4;
	}
			
	totalSpeed.z = buffer.z;
	getObj()->setLinearVelocity(totalSpeed);
}

void Player::stopMoving() {
	gkVector3 reverse = getObj()->getLinearVelocity();
	getObj()->setLinearVelocity(0.1 * reverse);

	getObj()->setLinearVelocity(gkVector3(0, 0, reverse.z));
}

bool Player::interact(){
	return (keyboard->isKeyDown(KC_EKEY));
}

void Player::tick() {
	getView()->setViewpoint(getObj()->getWorldPosition());

	if (view->mouseIsMoved())
		view->moveView();
	
	std::cout << "Keyboard text: " << keyboard->text << std::endl;
	
	if (keyboard->text > 0)	
		move();	
	else
		stopMoving();

	if (pickedUpItem != NULL) {
		pickedUpItem->getObj()->setPosition(view->getViewPosition() -view->getViewDirection());
	}
}

void Player::tick(bool& wantsToUse) {
	Player::tick();

	wantsToUse = interact();
}

View* Player::getView() const {
	return view;
}
