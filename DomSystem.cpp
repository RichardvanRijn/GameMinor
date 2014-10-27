#include "DomSystem.h"
#include "DomSystemStates.h"

DomSystem::DomSystem() : currentState(idleState::Instance())
{
}


DomSystem::~DomSystem()
{
}


void DomSystem::setState(DomState* newState){
	currentState = newState;
}

DomState* DomSystem::getState(){
	return currentState;
}

void DomSystem::activate(){
	if (this->currentState)
		currentState->execute(this);

}

/*void DomSystem::reduceHP(int damage){

}*/

InteractableObject* DomSystem::giveFirstProblem() {
	if (!toDoList.empty())
		return toDoList.front();
	else
		return NULL;
}

void DomSystem::addObject(InteractableObject* object){
	toDoList.push_back(object);
}

deque <InteractableObject*>* DomSystem::giveList(){
	return &toDoList;
}