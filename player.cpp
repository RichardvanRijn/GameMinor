#include "player.h"
#include "PickableObject.h"

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
	pickedUpItem->getObj()->setLinearVelocity(gkVector3(0, 0, -0.01));

	Player::releaseItem();
}

void Player::releaseItem() {
	pickedUpItem = NULL;
}

void Player::trowItem(){

	pickedUpItem->getObj()->translate(-2 * view->getViewDirection());
	pickedUpItem->getObj()->setLinearVelocity(gkVector3(0, 0, -0.01));
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

void Player::setPickedUpItem(PickableObject* item) {
	pickedUpItem = item;
}

void Player::move() {
	gkVector3 totalSpeed(0, 0, 0);
	gkVector3 buffer = getObj()->getLinearVelocity();
	gkVector3 viewDirection = view->getViewDirection();
	
	if (keyboard->isKeyDown(KC_WKEY)) {
		totalSpeed.x += -moveSpeed * viewDirection.x;
		totalSpeed.y += -moveSpeed * viewDirection.y;
	}
	else if (keyboard->isKeyDown(KC_SKEY)) {
		totalSpeed.x += moveSpeed * viewDirection.x;
		totalSpeed.y += moveSpeed * viewDirection.y;
	}

	if (keyboard->isKeyDown(KC_AKEY)) {
		totalSpeed.x += moveSpeed * viewDirection.y;
		totalSpeed.y += -moveSpeed * viewDirection.x;		
	}
	else if (keyboard->isKeyDown(KC_DKEY)) {
		totalSpeed.x += -moveSpeed * viewDirection.y;
		totalSpeed.y += moveSpeed * viewDirection.x;
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
	if (keyboard->isKeyDown(KC_EKEY))
	{
		keyboard->clearKey(KC_EKEY);
		return true;
	}
	return false;
}

bool Player::isMoveKeyPressed(){
	if (keyboard->isKeyDown(KC_DKEY) || keyboard->isKeyDown(KC_AKEY) || keyboard->isKeyDown(KC_WKEY) || keyboard->isKeyDown(KC_SKEY))
		return true;
	else
		return false;
}


void Player::toggleCrouch(){
	if (view->getViewHeight() >= 0.8)
	{
		view->setViewHeight(0.4);
		setMoveSpeed(moveSpeed * 0.5);
	}
	else
	{
		view->setViewHeight(0.8);
		setMoveSpeed(2);
	}
}

void Player::tick(bool& wantsToUse) {
	getView()->setViewpoint(getObj()->getWorldPosition());

	if (view->mouseIsMoved())
		view->moveView();

	if (isMoveKeyPressed())
		move();
	else
		stopMoving();
	
	if (keyboard->isKeyDown(KC_CKEY)){
		toggleCrouch();
		keyboard->clearKey(KC_CKEY);
	}

	if (keyboard->isKeyDown(KC_GKEY) && getPickedUpItem() != NULL)
		dropItem();

	if (pickedUpItem != NULL) {
		pickedUpItem->getObj()->setPosition(view->getViewPosition() - view->getViewDirection());
	}

	wantsToUse = interact();
}

View* Player::getView() const {
	return view;
}

PickableObject* Player::getPickedUpItem() const {
	return pickedUpItem;
}
