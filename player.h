#pragma once
#include "GameObject.h"
#include "view.h"

class Player : public GameObject
{
public:
	Player(gkGameObject* object);
	Player(gkGameObject* object, gkCamera* cam);
	~Player();

	void setView(gkCamera* cam);
	void setMoveSpeed(float speed);
	void setKeyboard(gkKeyboard* board);

	void move();
	void tick();
	void tick(bool& wantsToUse);

	View* getView() const;

private:
	View* view;
	gkKeyboard* keyboard;	
	
	bool interact();

	float moveSpeed;
};

