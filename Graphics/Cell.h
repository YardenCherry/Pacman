#pragma once
class Cell
{
private:
	int row;
	int col;
	int actualCost;
	Cell* parent;
	double G;
	double H;

public:
	Cell();
	Cell(int r, int c, Cell* p);
	int getActualCost()  { return actualCost; }
	void setActualCost(int cost) { actualCost = cost; }
	int getRow() { return row; }
	int getCol() { return col; }
	double getG() { return G; }
	double getH() { return H; }
	void setG(double g) { G = g; }
	void setH(double h) { H = h; }
	Cell* getParent() { return parent; }
	void setRow(int r) { row = r; }
	void setCol(int c) { col = c; }
	void setParent(Cell* p) { parent = p; }
};

