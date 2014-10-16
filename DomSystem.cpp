#include "DomSystem.h"


DomSystem::DomSystem()
{
}


DomSystem::~DomSystem()
{
}


void DomSystem::setState(int i){
	state = i;
}

int DomSystem::getState(){
	return state;
}

/*void DomSystem::doList(){
	UseableObject* oldProblem = toDoList.front();
	oldProblem->UndoInteract();
}*/