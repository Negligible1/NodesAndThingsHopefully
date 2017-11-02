#pragma once

#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Surface.h"

class Node
{
public:
	Node(std::shared_ptr <Surface> thenodessurface);
	~Node();
	
	int GetY() { return y; }
	int GetX() { return x; }
	Node* GetParent() { return parent; }

	void SetY(int Yv2) { y = Yv2; }
	void SetX(int Xv2) { x = Xv2; }
	void SetParent(Node* parent) { this->parent = parent; }
	void SetImage(std::shared_ptr <Surface> changedsurface) { thenodessurface = changedsurface; }

	void SetestValueToGoal(int value) { estValueToGoal = value; }
	void SetrealValueToStart(int value) { realValueToStart = value; }
	int GetestValueToGoal() { return estValueToGoal; }
	int GetrealValueToStart() { return realValueToStart; }

	void Draw(std::shared_ptr<Surface> screen);
	void AddNeighbour(Node* neighor);

	std::vector<Node*> GetNeighbours() { return neighbours; }

private:
	//position, scope, draw node or put on screen, etc
	int y;
	int x;

	int estValueToGoal;
	int realValueToStart;

	std::vector<Node*> neighbours;

	Node* parent;

	std::shared_ptr <Surface> thenodessurface;
};

#endif
