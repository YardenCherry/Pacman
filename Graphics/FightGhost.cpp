#include "FightGhost.h"
#include "Pacman.h"
#include "PacManLose.h"
#include "SearchGhost.h"
void FightGhost::OnEnter(Pacman* pn)
{
	pn->SetIsMoving(false);
	pn->SetIsFighting(true);
}

void FightGhost::Transition(Pacman* pn)
{

	if (pn->GetGhostNear()==2) {
		pn->SetCurrentState(new PacManLose());
		pn->GetCurrentState()->OnEnter(pn);
	}
	if (pn->GetGhostNear()==0) {
		OnExit(pn);
		pn->SetCurrentState(new SearchGhost());
		pn->GetCurrentState()->OnEnter(pn); // OnEnter of the next state!
	}
}

void FightGhost::OnExit(Pacman* pn)
{
	pn->SetIsMoving(true);
	pn->SetIsFighting(false);
}
