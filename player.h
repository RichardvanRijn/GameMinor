#pragma once
#include "GameObject.h"
#include "view.h"

class PickableObject;

class Player : public GameObject
{
public:
	Player(gkGameObject* object);
	Player(gkGameObject* object, gkCamera* cam);
	~Player();

	void setView(gkCamera* cam);
	void setMoveSpeed(float speed);
	void setKeyboard(gkKeyboard* board);
	void setPickedUpItem(PickableObject* item);
	void setItemHoldPosition(gkVector3 position);

	void dropItem();
	void trowItem();
	void releaseItem();

	bool isMoveKeyPressed();
	void move();
	void stopMoving();
	void tick(bool& wantsToUse);

	void toggleCrouch();

	View* getView() const;
	PickableObject* getPickedUpItem() const;

private:
	View* view;
	gkKeyboard* keyboard;	
	
	PickableObject* pickedUpItem;

	bool interact();

	float moveSpeed;
	gkVector3 itemPosition;
};
