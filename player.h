#pragma once
#include "GameObject.h"
#include "view.h"

class UseableObject;

class Player : public GameObject
{
public:
	Player(gkGameObject* object);
	Player(gkGameObject* object, gkCamera* cam);
	~Player();

	void setView(gkCamera* cam);
	void setMoveSpeed(float speed);
	void setKeyboard(gkKeyboard* board);
	void setPickedUpItem(UseableObject* item);
	void setItemHoldPosition(gkVector3 position);

	void dropItem();

	bool isMoveKeyPressed();
	void move();
	void stopMoving();
	void tick(bool& wantsToUse);

	View* getView() const;
	UseableObject* getPickedUpItem() const;

private:
	View* view;
	gkKeyboard* keyboard;	
	
	UseableObject* pickedUpItem;

	bool interact();

	float moveSpeed;
	gkVector3 itemPosition;
};

