#ifndef _DomSystem_H_
#define _DomSystem_H_

#include <deque>
#include "useableobject.h"
#include "interactableobject.h"
//#include "DomState.h"


class DomState;

//the amount of hitpoints the Granny can withstand
//const int hitPoints = 100;

using namespace std;

class DomSystem
{
public:
	DomSystem();
	~DomSystem();
	void setState(DomState*);
	DomState* getState();
	deque < InteractableObject* >* giveList();
	InteractableObject* giveFirstProblem();
	void addObject(InteractableObject*);
	
	void activate();
//	void reduceHP(int damage);

private:
	DomState* currentState;
	deque < InteractableObject* > toDoList;
	
	//the current amount of hitpoints 
//	int currentHP;

};

#endif _DomSystem_H_