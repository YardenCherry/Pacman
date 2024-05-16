#include "GhostLose.h"


void GhostLose::OnEnter(Ghost* pn)
{
	pn->SetIsAlive(false);
	pn->SetIsFighting(false);
}

void GhostLose::Transition(Ghost* pn)
{

}

void GhostLose::OnExit(Ghost* pn)
{

}
