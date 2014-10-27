#ifndef DOMSTATE_H
#define DOMSTATE_H

class DomSystem;

class DomState
{
public:
	DomState();
	~DomState();

	virtual void execute(DomSystem*) = 0;
};

#endif
