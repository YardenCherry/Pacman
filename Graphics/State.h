#pragma once
#include "Pacman.h"

class Pacman;



// pure abstract class (in Java it is interface)
class State
{
public:
	
	virtual void OnEnter(Pacman* pn) = 0;
	virtual void Transition(Pacman* pn) = 0; // to another state
	virtual void OnExit(Pacman* pn) = 0;

};