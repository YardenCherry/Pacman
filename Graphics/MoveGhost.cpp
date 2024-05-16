#include "MoveGhost.h"
#include "Ghost.h"
void MoveGhost::OnEnter(Ghost* pn)
{
	pn->SetIsMoving(true);
	pn->SetIsFighting(false);

}

void MoveGhost::Transition(Ghost* pn)
{
	OnExit(pn);
	
}

void MoveGhost::OnExit(Ghost* pn)
{
	pn->SetIsFighting(true);
}
