#include "MovePacman.h"
#include "Pacman.h"
#include "FightGhost.h"
#include "SearchGhost.h"
void MovePacman::OnEnter(Pacman* pn)
{
	pn->SetIsMoving(true);
}

void MovePacman::Transition(Pacman* pn)
{
	OnExit(pn);
	if (pn->GetGhostNear()>0) {
		pn->SetCurrentState(new FightGhost());
		pn->GetCurrentState()->OnEnter(pn);
	}
	if (pn->GetGhostNear()==0) {
		pn->SetCurrentState(new SearchGhost());
		pn->GetCurrentState()->OnEnter(pn); // OnEnter of the next state!
	}
}

void MovePacman::OnExit(Pacman* pn)
{
	pn->SetIsMoving(false);
}
