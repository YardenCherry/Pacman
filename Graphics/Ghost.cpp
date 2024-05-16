#include "Ghost.h"
#include <math.h>
#include "MoveGhost.h"
#include "Pacman.h"
#include "GhostState.h"


static int numOfGhosts=0;
static int numOfGhostsNear = 0;

int Gheuristic(int row, int col, int targetRow, int targetCol) {
	return abs(row - targetRow) + abs(col - targetCol);
}
Ghost::Ghost(int x, int y)
{
	
	this->x = x;
	this->y = y;
	flag = false;
	numOfGhosts++;
	GhostsWon = false;
	isAlive = true;
	pCurrentState = new MoveGhost();
	pCurrentState->OnEnter(this);
	this->distance = Gheuristic(this->GetX(), this->GetY(), this->targetX, this->targetY);
}


void Ghost::DoSomeWork()
{
	targetX = pc->getX();
	targetY = pc->getY();
	if (isMoving) {
		if (distance <= 5) {
			pCurrentState->Transition(this);
			if (!flag)
				numOfGhostsNear++;
			flag = true;	
		}
		else
		{
			if(flag)
				numOfGhostsNear--;
			flag = false;
		}
		
			this->distance = Gheuristic(this->GetX(), this->GetY(), this->targetX, this->targetY);
	}
}
int Ghost:: GetNumOfGhostsNear() { return numOfGhostsNear; }
int Ghost::GetNumOfGhosts() { return numOfGhosts; }
void Ghost::SetNumOfGhostsNear(int value) {numOfGhostsNear=value; }
void Ghost::SetNumOfGhosts(int value) {  numOfGhosts=value; }
