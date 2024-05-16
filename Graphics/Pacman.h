#pragma once
#include "State.h"
const double SPEED = 0.1;
const double REDUCER = 0.5;
class State;

class Pacman
{
private:
	double x, y, targetX, targetY; // position
	double dirx, diry;
	bool isMoving, isFighting, isAlive, isSearching;
	int numCoins;
	int ghostNear;
	double health,depth,timer;
	State* pCurrentState;
	
public:
	Pacman(int x, int y);
	void Draw();
	void DoSomeWork();

	void SetIsMoving(bool value) { isMoving = value; }
	int getX() { return this->x; }
	int getY() { return this->y; }
	int getNumOfCoins() { return this->numCoins; }
	void setNumOfCoins() {this->numCoins++; }
	void SetX(int newX) { this->x=newX; }
	void SetY(int newY) { this->y=newY; }
	void SetIsSearching(bool value) { isSearching = value; }
	void SetIsFighting(bool value) { isFighting = value; }
	bool getIsMoving() { return this->isMoving; }
	void SetCurrentState(State* ps) { pCurrentState = ps; }
	int GetGhostNear() { return this->ghostNear; }
	void SetGhostNear(int value) { this->ghostNear = value; }
	void SetAlive(bool value) { isAlive = value; }
	bool GetAlive() { return this->isAlive; }
	void SetDepth(int value) { this->depth = value; }
	void SetHealth(int value) { this->health = value; }
	bool getIsSearching() { return this->isSearching; }
	void SetTimer(int value) { this->timer = value; }
	State* GetCurrentState() { return pCurrentState; }

};