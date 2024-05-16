#pragma once
#include "State.h"
class MovePacman :
    public State
{
    void OnEnter(Pacman* pn);
    void Transition(Pacman* pn); // to another state
    void OnExit(Pacman* pn);
};

