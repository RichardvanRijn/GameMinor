#ifndef DOMSYSTEMSTATES_H
#define DOMSYSTEMSTATES_H


#include "DomState.h"


class DomSystem;



class idleState : public DomState
{
private:

	idleState(){}

	idleState(const idleState&);
	idleState& operator=(const idleState&);

public:

	static idleState* Instance();

	virtual void execute(DomSystem*);

};


class busyState : public DomState
{
private:

	busyState(){}

	busyState(const busyState&);
	busyState& operator=(const busyState&);

public:

	static busyState* Instance();

	virtual void execute(DomSystem* GrannyGuard);

};



class alarmState : public DomState
{
private:

	alarmState(){}

	alarmState(const alarmState&);
	alarmState& operator=(const alarmState&);

public:

	static alarmState* Instance();


	virtual void execute(DomSystem* GrannyGuard);

};


#endif //DOMSYSTEMSTATES_H