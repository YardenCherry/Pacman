#include "Pacman.h"
#include "State.h"
#include "SearchGhost.h"



Pacman::Pacman(int x, int y)
{
	this->x = x;
	this->y = y;
	isAlive = true;
	pCurrentState = new SearchGhost();
	pCurrentState->OnEnter(this);
	isFighting = false;
	numCoins = 0;
	health = 2;
	timer = 2;
	depth = 20;

}

void Pacman::Draw()
{

}

void Pacman::DoSomeWork()
{

		if (isSearching) {
			if(depth>0)
				depth -= REDUCER;
			else
				pCurrentState->Transition(this);
			
		}


	 
		if (isMoving) {
			timer -= REDUCER;
			if(timer<=0)
				pCurrentState->Transition(this);	
			}



		if (isFighting) {
			ghostNear = 1;
			if (ghostNear == 2) {
				pCurrentState->Transition(this);
			}

			if (ghostNear == 1) {
				if (health > 0) {
					if(ghostNear==1)
						health -= REDUCER;
					else
						pCurrentState->Transition(this);
				}
				else{
					pCurrentState->Transition(this);
				}
			}

		}
	


}
