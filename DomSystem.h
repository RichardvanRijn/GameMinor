#ifndef _DomSystem_H_
#define _DomSystem_H_

#include <deque>
#include "useableobject.h"

#define IDLE 0
#define BUSY 1
#define ALARM 2

using namespace std;

class DomSystem
{
public:
	DomSystem();
	~DomSystem();
	void setState(int);
	int getState();
	
	

	//void doList();
private:
	int state;

};

#endif _DomSystem_H_