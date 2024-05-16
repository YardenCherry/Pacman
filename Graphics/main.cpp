
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "glut.h"
#include <queue>
#include <stack>
#include <vector>
#include "Cell.h"
#include <iostream>
#include "Functions.h"
#include "Pacman.h"
#include "State.h"
#include "Ghost.h"
#include "GhostState.h"
using namespace std;

const int MSZ = 100;

const int SPACE = 0;
const int WALL = 1;
const int PACMAN = 2;
const int PGRAY = 3;
const int GRAY = 4;
const int BLACK = 5;
const int PATH = 6;
const int GHOST = 7;
const int PBLACK = 8;

bool flags[3]={false};
int frame=0;
int Target_row, Target_col;
int targetRow, targetCol;
int maze[MSZ][MSZ] = {0}; // space
int coins[MSZ][MSZ] = { 0 };
bool runBFS = false, runAStar = false, showPath=false;
queue <Cell*> grays; // queue of gray cells
Pacman *pacman= nullptr;
Ghost* ghosts[3];
Cell* p = nullptr;
Cell* pinkPoint = nullptr;
Cell* pc;
Cell* GhostArr[3];
int iTarget_row, iTarget_col;
void GhostMoveFunc(int GhostNum);
void MoveRandom(Pacman* pacman);
void delay(double number_of_seconds)
{
	// Converting time into milli_seconds
	double milli_seconds = 1000 * number_of_seconds;

	// Storing start time
	clock_t start_time = clock();

	// looping till required time is not achieved
	while (clock() < start_time + milli_seconds);
}

int heuristic(int row, int col, int targetRow, int targetCol) {
	return abs(row - targetRow) + abs(col - targetCol);
}


struct CompareAStar {
	bool operator() (Cell* pn1, Cell* pn2) {
		return pn1->getG() + pn1->getH() > pn2->getG() + pn2->getH();

	}
};

priority_queue <Cell*, vector <Cell*>, CompareAStar> GhostSteps;





void InitMaze();
void initCoins();
void init()
{
	glClearColor(0.5,0.5,0.5,0);// color of window background
	glOrtho(0, MSZ, 0, MSZ, -1, 1); // set the coordinates system

	srand(time(0));

	pacman = new Pacman(MSZ / 2, MSZ / 2);
	InitMaze();
	initCoins();
}

void InitMaze()
{
	int i, j;

	for (i = 0;i < MSZ;i++)
	{
		maze[0][i] = WALL;
		maze[MSZ-1][i] = WALL;
		maze[i][0] = WALL;
		maze[i][MSZ - 1] = WALL;
	}

	for(i=1;i<MSZ-1;i++)
		for (j = 1;j < MSZ - 1;j++)
		{
			if (i % 2 == 1) // mostly spaces
			{
				if (rand() % 5000 < 2) // WALL
					maze[i][j] = WALL;
				else maze[i][j] = SPACE;
			}
			else // even lines
			{
				if (rand() % 10 < 4) // space
					maze[i][j] = SPACE;
				else
					maze[i][j] = WALL;
			}
		}
	maze[MSZ / 2][MSZ / 2] = PACMAN;


	targetRow = pacman->getX();
	targetCol = pacman->getY();
	Target_row = rand() % MSZ;
	Target_col = rand() % MSZ;

	for (int i = 0; i < 3; i++)
	{
		do
		{
			iTarget_row = rand() % MSZ;
			iTarget_col = rand() % MSZ;
		} while (iTarget_row == MSZ - 1 || iTarget_row == 0 || iTarget_col == MSZ - 1 || iTarget_col == 0);
		pc = new Cell(iTarget_row, iTarget_col, nullptr);
		GhostArr[i] = pc;
		ghosts[i] = new Ghost(iTarget_row, iTarget_col);
		maze[iTarget_row][iTarget_col] = GHOST;
	}
	pc = new Cell(targetRow, targetCol, nullptr);  // pointer to a cell
	pc->setG(0.0);
	pc->setH(heuristic(targetRow, targetCol, Target_row, Target_col));

	


	Cell* pc = new Cell(MSZ / 2, MSZ / 2,nullptr);  // pointer to a cell
	
	
}

void drawCoins() {
	int i, j;
	glPointSize(1.5);
	glColor3d(1, 0, 0);
	for (i = 0; i < MSZ; i++)
		for (j = 0; j < MSZ; j++)
		{
			if (coins[i][j] == 1) {
				glBegin(GL_POINTS);
				glVertex2d(j + 0.5, i + 0.5);
				glEnd();
			}
		}
}




void initCoins() {
	int i, j;
	glPointSize(1.5);
	glColor3d(1, 0, 0); // white
	
	for (i = 0; i < MSZ; i++)
		for (j = 0; j < MSZ; j++)
		{
			if (maze[i][j] == SPACE) {
				coins[i][j] = 1;
			}
		}
	coins[MSZ / 2][MSZ / 2] = 0;

}

void DrawMaze()
{
	int i, j;

	for(i=0;i<MSZ;i++)
		for (j = 0;j < MSZ;j++)
		{
			switch (maze[i][j]) // set convinient color of a cell
			{
			case SPACE:
				glColor3d(0.1, 0.1, 0.1); // white
				break;
			case PBLACK:
				if (showPath)
					glColor3d(0.8, 1, 0.8); // green
				else
					glColor3d(0.1, 0.1, 0.1); // black
				break;
			case WALL:
				glColor3d(0,0, 1); // black
				break;
			case PACMAN:
				glColor3d(1, 1, 0); // blue
				break;
			case GRAY:
				if(showPath)
					glColor3d(1, 0.7, 0); // orange
				else
					glColor3d(0.1, 0.1, 0.1); // black	
				break;
			case PGRAY:
				if (showPath)
					glColor3d(1, 0.7, 0); // orange
				else
					glColor3d(0.1, 0.1, 0.1); // black	
				break;
			case BLACK:
				if(showPath)
					glColor3d(0.8, 1, 0.8); // green
				else
					glColor3d(0.1, 0.1, 0.1); // black	
				break;
			case PATH:
				glColor3d(0.1, 0.1, 0.1); // magenta
				break;
			case GHOST:
				glColor3d(0, 1, 0);
				break;
			
			}// switch
	
			glBegin(GL_POLYGON);
			glVertex2d(j, i);
			glVertex2d(j, i + 1);
			glVertex2d(j+1, i + 1);
			glVertex2d(j+1 , i );
			glEnd();
		}
}


// BFS a cell on row,col can be either WHITE or TARGET
bool CheckNeighbour(int row, int col, Cell* pCurrent)
{
	Cell* pn = nullptr;
	if (maze[row][col] ==GHOST)
	{
		runBFS = false;
		//RestorePath(pCurrent);
		return false;
	}
	else // must be "White Neighbour" - SPACE
	{
		pn = new Cell(row, col, pCurrent); // create new Cell
		grays.push(pn);
		maze[row][col] = PGRAY;
		return true; // go_on = true
	}
}

void EmptyQueue(Cell* p) {

	while (!grays.empty()) {
		grays.pop();
	}
	p = new Cell(pacman->getX(), pacman->getY(), nullptr);
	grays.push(p); // insert first cell to grays

}
void RunBFSIteration()
{
	Cell* pc;
	int row, col;
	bool go_on = true;

	if (grays.empty())
	{
		runBFS = false;
		//cout << "Grays are empty. There is no solution\n";
		return;
	}
	else // grays is not empty
	{
		// pick the first Cell from grays
		pc = grays.front();
		
		grays.pop();
		
		// paint it black
		if (maze[pc->getRow()][pc->getCol()] != PACMAN) maze[pc->getRow()][pc->getCol()] = PBLACK;

		row = pc->getRow();
		col = pc->getCol();
		// now check all neighbors of pc and if they are white add them to grays
		// but if one of them is target then stop BFS because target has been found

		// up
		if (maze[row + 1][col] == SPACE || maze[row + 1][col] == GHOST)
			go_on = CheckNeighbour(row + 1, col, pc);
		// down
		if (go_on && (maze[row - 1][col] == SPACE || maze[row - 1][col] == GHOST))
			go_on = CheckNeighbour(row - 1, col, pc);
		// left
		if (go_on && (maze[row][col - 1] == SPACE || maze[row][col - 1] == GHOST))
			go_on = CheckNeighbour(row, col - 1, pc);
		// right
		if (go_on && (maze[row][col + 1] == SPACE || maze[row][col + 1] == GHOST))
			go_on = CheckNeighbour(row, col + 1, pc);

	}
	
}

// drawings are here
void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer with background color

	DrawMaze();
	drawCoins();
	

	glutSwapBuffers(); // show all
}
void StartGame()
{
	int i, j;
	int distance;
	frame++;
	Cell* pc;
	
	targetRow = pacman->getX();
	targetCol = pacman->getY();
	if (!pacman->GetAlive())
	{
		printf("Pacman died, num of coins : %d ", pacman->getNumOfCoins());
		delay(3);
		exit(1);
	}
	if (pacman->getIsSearching()) {
		RunBFSIteration();
	}

	for (i = 0; i < 3; i++)
	{

		ghosts[i]->SetPacman(pacman);
		ghosts[i]->DoSomeWork();
		pc = GhostArr[i];
		pc->setG(0.0);
		pc->setH(heuristic(pc->getRow(), pc->getCol(), targetRow, targetCol));
		distance = pc->getH();
		if (distance <= 5) {
			if (flags[i] == false) {
				ghosts[i]->SetNumOfGhostsNear(ghosts[i]->GetNumOfGhostsNear() + 1);
				flags[i] = true;
			}
		}
		else
			if (flags[i]==true) {
				ghosts[i]->SetNumOfGhostsNear(ghosts[i]->GetNumOfGhostsNear() - 1);
				flags[i] = false;
			}
		
		if (distance <= 7) {
			if (ghosts[i]->GetNumOfGhostsNear() < 2) {
				ghosts[i]->SetIsMoving(false);
			}
			else
				ghosts[i]->SetIsMoving(true);
		}
		else
			ghosts[i]->SetIsMoving(true);
		
		if (distance <= 1) {
			
			if (ghosts[i]->GetNumOfGhostsNear() >= 2) {
				delay(1);
				pacman->SetAlive(false);
			}
			else
				ghosts[i]->SetIsAlive(false);

			/*ghosts[i]->SetNumOfGhostsNear(ghosts[i]->GetNumOfGhostsNear() - 1);
			ghosts[i]->SetNumOfGhosts(ghosts[i]->GetNumOfGhosts() - 1);*/


			//maze[ghosts[i]->GetX()][ghosts[i]->GetY()] = SPACE;
			//pacman->SetIsFighting(true);
		}
		GhostSteps.push(pc);
		if (ghosts[i]->GetIsMoving() && pacman->getIsMoving() && ghosts[i]->GetIsAlive()) {
			GhostMoveFunc(i);
		}
	}


	if (pacman->GetGhostNear() == 0 && !pacman->getIsSearching()) {
		pacman->SetDepth(20);
		pacman->SetTimer(2);
		MoveRandom(pacman);
	}
}

		
	
	
		
	

	
		
	

void GhostMoveOneBlock(int row, int col, Cell* pc, int GhostNum)
{
	while (pc != nullptr)
	{
		if (pc->getParent() == nullptr)
		{
			maze[row][col] = SPACE;
			while (!GhostSteps.empty())
				GhostSteps.pop();
		}

		else if (pc->getParent()->getParent() == nullptr)
		{
			maze[pc->getRow()][pc->getCol()] = GHOST;
			maze[pc->getParent()->getRow()][pc->getParent()->getCol()] = SPACE;
			
			GhostArr[GhostNum]->setRow(pc->getRow());
			GhostArr[GhostNum]->setCol(pc->getCol());
			pc->setParent(nullptr);
			while (!GhostSteps.empty())
				GhostSteps.pop();
		}
		pc = pc->getParent();
	}
}
bool CheckGhostNeighbours(int row, int col, Cell* pCurrent, int GhostNum)
{
	Cell* pn = nullptr;
	if (maze[row][col] == PACMAN)
	{
		GhostMoveOneBlock(row, col, pCurrent, GhostNum);
		return false;
	}
	else // must be "White Neighbour" - SPACE
	{
		
		
		pn = new Cell(row, col, pCurrent); // create new Cell
		pn->setG(heuristic(row, col, GhostArr[GhostNum]->getRow(), GhostArr[GhostNum]->getCol()));
		pn->setH(heuristic(row, col, targetRow, targetCol));
		GhostSteps.push(pn);
		maze[row][col] = GRAY;
		return true; // go_on = true
	}
}
void GhostMoveFunc(int GhostNum)
{
	Cell* pc;
	int row, col;
	bool go_on = true;
	//delay(0.01);
	while (!GhostSteps.empty() && go_on)
	{
		
		// pick the first Cell from grays
		pc = GhostSteps.top();
		GhostSteps.pop();
		// paint it black
		if (maze[pc->getRow()][pc->getCol()] != GHOST) maze[pc->getRow()][pc->getCol()] = BLACK;

		row = pc->getRow();
		col = pc->getCol();
		// now check all neighbors of pc and if they are white add them to grays
		// but if one of them is target then stop BFS because target has been found

		// up
		if (maze[row + 1][col] == SPACE || maze[row + 1][col] == PACMAN||
			maze[row + 1][col]==PGRAY|| maze[row + 1][col] == PATH|| maze[row + 1][col] == PBLACK)
			go_on = CheckGhostNeighbours(row + 1, col, pc, GhostNum);
		// down
		if (go_on && (maze[row - 1][col] == SPACE || maze[row - 1][col] == PACMAN||
			maze[row - 1][col] == PGRAY|| maze[row - 1][col] ==PATH || maze[row - 1][col] == PBLACK))
			go_on = CheckGhostNeighbours(row - 1, col, pc, GhostNum);
		// left
		if (go_on && (maze[row][col - 1] == SPACE || maze[row][col - 1] == PACMAN||
			maze[row][col - 1] == PGRAY|| maze[row][col - 1] == PATH|| maze[row][col - 1] == PBLACK))
			go_on = CheckGhostNeighbours(row, col - 1, pc, GhostNum);
		// right
		if (go_on && (maze[row][col + 1] == SPACE || maze[row][col + 1] == PACMAN||
			maze[row][col + 1] == PGRAY|| maze[row][col + 1] == PATH|| maze[row][col + 1] == PBLACK))
			go_on = CheckGhostNeighbours(row, col + 1, pc, GhostNum);
	}

	for (int i = 0; i < MSZ; i++)
	{
		for (int j = 0; j < MSZ; j++)
		{
			if (maze[i][j] == BLACK || maze[i][j] == GRAY)
				maze[i][j] = SPACE;
		}
	}

}
void MoveRandom(Pacman *pacman) {

	int place;
	bool flag=true;
	int stuck=20;
	int row = pacman->getX();
	int col = pacman->getY();
	do {
		place = rand() % 4;
		stuck--;
		switch (place)
		{
		case 0: // up
			if ((maze[row + 1][col] != WALL)&& ((maze[row + 1][col] != PATH)||(stuck<=0))) {
				pacman->SetX(row + 1);
				maze[row][col] = PATH;
				maze[row + 1][col] = PACMAN;
				if (coins[row + 1][col] == 1) {
					coins[row + 1][col] = 0;
					pacman->setNumOfCoins();
				}
				flag = false;
			}
			break;
		case 1: // down
			if ((maze[row - 1][col] !=WALL)&& ((maze[row - 1][col] != PATH)||(stuck<=0))) {
				pacman->SetX(row - 1);
				maze[row][col] = PATH;
				maze[row -1][col] = PACMAN;
				if (coins[row - 1][col] == 1) {
					coins[row - 1][col] = 0;
					pacman->setNumOfCoins();
				}
				flag = false;
			}
			break;
		case 2: // left
			if ((maze[row][col - 1] !=WALL)&& ((maze[row][col - 1] != PATH)||(stuck<=0))) {
				pacman->SetY(col - 1);
				maze[row][col] = PATH;
				maze[row][col-1] = PACMAN;
				if (coins[row][col - 1] == 1) {
					coins[row][col - 1] = 0;
					pacman->setNumOfCoins();
				}
				flag = false;
			}
			break;
		case 3: // right
			if ((maze[row][col + 1]!=WALL)&& ((maze[row][col + 1] != PATH)||(stuck<=0))) {
				pacman->SetY(col + 1);
				maze[row][col] = PATH;
				maze[row][col+1] = PACMAN;
				if (coins[row][col + 1] == 1) {
					coins[row][col + 1] = 0;
					pacman->setNumOfCoins();
				}
				flag = false;
			}
			break;
		}

	} while (flag);
	pacman->GetCurrentState()->Transition(pacman);


	EmptyQueue(p);

	
}


void idle() 
{
	pacman->DoSomeWork();
	
	StartGame();
		
	

	glutPostRedisplay(); // call to display indirectly
}

void menu(int choice)
{
	if (choice == 1) // BFS
		showPath = !showPath;
	
}

void main(int argc, char* argv[]) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("Pacman");

	glutDisplayFunc(display); // refresh function
	glutIdleFunc(idle);  // updates function
	// menu
	glutCreateMenu(menu);
	glutAddMenuEntry("show path", 1);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();

	glutMainLoop();
}