#include "SearchGhost.h"
#include "MovePacman.h"


void SearchGhost::OnEnter(Pacman* pn)
{
	pn->SetIsMoving(false);
	pn->SetIsSearching(true);
}

void SearchGhost::Transition(Pacman* pn)
{
	OnExit(pn);
	pn->SetCurrentState(new MovePacman());
	pn->GetCurrentState()->OnEnter(pn); // OnEnter of the next state!

}

void SearchGhost::OnExit(Pacman* pn)
{
	pn->SetIsMoving(true);
	pn->SetIsSearching(false);
}
