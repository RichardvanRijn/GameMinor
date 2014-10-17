#pragma once
#include "GameObject.h"
#include "view.h"

class InteractableObject;

class Player : public GameObject
{
public:
	Player(gkGameObject* object);
	Player(gkGameObject* object, gkCamera* cam);
	~Player();

	void setView(gkCamera* cam);
	void setMoveSpeed(float speed);
	void setKeyboard(gkKeyboard* board);
	void setPickedUpItem(InteractableObject* item);
	void setItemHoldPosition(gkVector3 position);

	void dropItem();
	void trowItem();
	void releaseItem();

	bool isMoveKeyPressed();
	void move();
	void stopMoving();
	void tick();
	void tick(bool& wantsToUse);

	void toggleCrouch();

	View* getView() const;
	InteractableObject* getPickedUpItem() const;

private:
	View* view;
	gkKeyboard* keyboard;	
	
	InteractableObject* pickedUpItem;

	bool interact();

	float moveSpeed;
	gkVector3 itemPosition;
};
