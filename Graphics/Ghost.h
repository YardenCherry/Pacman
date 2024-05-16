#pragma once
#include "GhostState.h"
#include "Pacman.h"
#include <string.h>
class GhostState;


class Ghost
{
private:

	double x, y; // position
	double targetX, targetY;
	bool isMoving, isFighting, isHolding, isAlive, GhostsWon;
	bool flag;
	int distance;
	int color;
	Pacman* pc;
	GhostState* pCurrentState;
public:
	Ghost(int x, int y);
	void DoSomeWork();
	int GetNumOfGhostsNear();
	int GetNumOfGhosts();
	void SetIsMoving(bool value) { isMoving = value; }
	void SetIsFighting(bool value) { isFighting = value; }
	void SetIsHolding(bool value) { isHolding = value; }
	void SetCurrentState(GhostState* ps) { pCurrentState = ps; }
	void SetIsAlive(bool value) { this->isAlive = value; }
	bool GetIsAlive() { return this->isAlive; }
	bool GetIsMoving() { return this->isMoving; }
	void SetPacman(Pacman* pacman) { this->pc = pacman; }
	void SetColor(int value) { this->color = value; }
	double getDistance() { return this->distance; }
	int GetColor() { return this->color; }
	int GetX() { return this->x; }
	int GetY() { return this->y; }
	int GetPacmanX() { return this->pc->getX(); }
	int GetPacmanY() { return this->pc->getY(); }
	void SetPacmanX(int value) { this->pc->SetX(value); }
	void SetPacmanY(int value) { this->pc->SetY(value); }
	void SetX(int value) { this->x = value; }
	void SetY(int value) { this->y = value; }
	GhostState* GetCurrentState() { return pCurrentState; }
	void SetNumOfGhostsNear(int value);
	void SetNumOfGhosts(int value);

};