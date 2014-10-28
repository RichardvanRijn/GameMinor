#include "DomSystemStates.h"
#include "DomSystem.h"
#include "DomState.h"





//--------------------------------------methods for idleState

idleState* idleState::Instance()
{
	static idleState instance;

	return &instance;
}


void idleState::execute(DomSystem* GrannyGuard)
{
	//the miner digs for gold until he is carrying in excess of MaxNuggets. 
	//If he gets thirsty during his digging he packs up work for a while and 
	//changes state to go to the saloon for a whiskey.
	
	if (!GrannyGuard->giveList()->empty())
	{
		GrannyGuard->setState(busyState::Instance());
	}
}




//----------------------------------------methods for busyState

busyState* busyState::Instance()
{
	static busyState instance;

	return &instance;
}




void busyState::execute(DomSystem* GrannyGuard)
{
	if (GrannyGuard->giveList()->empty())
		GrannyGuard->setState(idleState::Instance());

	else {
		if (GrannyGuard->giveFirstProblem()->animationDone() || GrannyGuard->giveFirstProblem()->isBlocked())
			GrannyGuard->giveFirstProblem()->UndoInteract();
		if (!GrannyGuard->giveFirstProblem()->isOpen())
			GrannyGuard->giveList()->pop_front();
	}

	
	if (false)
	{
		GrannyGuard->setState(alarmState::Instance());
	}
}




//----------------------------------------methods for alarmState

alarmState* alarmState::Instance()
{
	static alarmState instance;

	return &instance;
}



void alarmState::execute(DomSystem* GrannyGuard)
{
	if (GrannyGuard->giveList()->empty())
		GrannyGuard->setState(idleState::Instance());

}


