#include "PacManLose.h"

void PacManLose::OnEnter(Pacman* pn)
{
	pn->SetAlive(false);
}

void PacManLose::Transition(Pacman* pn)
{
	OnExit(pn);
	pn->SetIsMoving(false);
	pn->SetIsFighting(false);
}

void PacManLose::OnExit(Pacman* pn)
{
}
