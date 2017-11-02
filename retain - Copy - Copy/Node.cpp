#include "Node.h"

Node::Node(std::shared_ptr <Surface> thenodessurface)
{
	this->thenodessurface = thenodessurface;
	this->parent = NULL;

	estValueToGoal = NULL;
	realValueToStart = NULL;
}

Node::~Node()
{
}

void Node::AddNeighbour(Node* neighbour)
{
	neighbours.push_back(neighbour);
}

void Node::Draw(std::shared_ptr<Surface> screen)
{
	thenodessurface->blit(screen, x, y);
}