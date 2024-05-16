#pragma once
#include "Ghost.h"

class Ghost;
class GhostState
{
public:
	virtual void OnEnter(Ghost* pn) = 0;
	virtual void Transition(Ghost* pn) = 0; // to another state
	virtual void OnExit(Ghost* pn) = 0;
};

