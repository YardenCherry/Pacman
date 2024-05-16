#pragma once
#include "State.h"
#include "GhostState.h"
class GhostsAttack :
    public GhostState
{
    void OnEnter(Ghost* pn);
    void Transition(Ghost* pn); // to another state
    void OnExit(Ghost* pn);
};

