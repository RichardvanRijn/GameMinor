#include "player.h"
#include "view.h"

Player::Player(gkGameObject* object) :
	GameObject(object),
	view(NULL)
{
	
}

Player::Player(gkGameObject* object, gkCamera* cam) :
	GameObject(object)
{	
	//view = new View(cam);
	view = new View(cam, 0.6, -.5, .8);
}

Player::~Player()
{
	delete getObj();
	delete keyboard;
	delete view;
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

void Player::move() {
	static gkVector3 totalSpeed;
	gkVector3 viewDirection = view->getViewDirection();
	
	std::cout << "View Direction: " << viewDirection << std::endl;
	std::cout << "Move speed: " << moveSpeed << std::endl;

	gkVector3 buffer = getObj()->getLinearVelocity();

	if (keyboard->isKeyDown(KC_WKEY)) {	
		totalSpeed.x = -moveSpeed * viewDirection.x;
		totalSpeed.y = -moveSpeed * viewDirection.y;
	}
	else if (keyboard->isKeyDown(KC_SKEY)) {
		totalSpeed.x = moveSpeed * viewDirection.x;
		totalSpeed.y = moveSpeed * viewDirection.y;
	}

	if (keyboard->isKeyDown(KC_AKEY)) {
		totalSpeed.x += moveSpeed * viewDirection.y;
		totalSpeed.y += -moveSpeed * viewDirection.x;		
	}

	else if (keyboard->isKeyDown(KC_DKEY)) {
		totalSpeed.x += -moveSpeed * viewDirection.y;
		totalSpeed.y += moveSpeed * viewDirection.x;
	}
	
	if (!keyboard->isKeyDown(KC_WKEY) && !keyboard->isKeyDown(KC_SKEY) && !keyboard->isKeyDown(KC_AKEY)
		&& !keyboard->isKeyDown(KC_DKEY) && (totalSpeed != gkVector3(0, 0, 0)))
	{
		gkVector3 reverse = getObj()->getLinearVelocity();
		getObj()->setLinearVelocity(-0.1 * reverse);
		totalSpeed.x = 0;
		totalSpeed.y = 0;
		totalSpeed.z = buffer.z;
	}
	std::cout << "Total Speed: " << totalSpeed << std::endl;
	totalSpeed.z = buffer.z;
	getObj()->setLinearVelocity(totalSpeed);
}

void Player::tick() {		
	getView()->setViewpoint(getObj()->getWorldPosition());

	if (view->mouseIsMoved())
		view->moveView();
	
	//if (keyboard->text)
	//	move();
	
}

View* Player::getView() const {
	return view;
}
