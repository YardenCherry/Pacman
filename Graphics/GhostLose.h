#pragma once
#include "GhostState.h"
class GhostLose :
    public GhostState
{
    void OnEnter(Ghost* pn);
    void Transition(Ghost* pn); // to another state
    void OnExit(Ghost* pn);
};

