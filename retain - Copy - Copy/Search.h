#pragma once
#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include "Node.h"

class Search
{
public:
	Search();
	~Search();

	void GetSearchInfo(std::vector<Node> NodeGrid, Node* StartNode, Node* GoalNode);
	std::vector<Node*> InitialiseSearch();
	int GoalReached();
	void GetNextNode();
	void IfInList(std::vector<Node*> List, Node* neighbourNode, bool* checked);
	void RemoveCurrentNodeFromOpen();
	virtual void SearchAlgorithm(int i);
	
	void ForDrawing(std::shared_ptr<Surface> screen) { this->screen = screen; }
	void Draw();
	//For debugging

private:
	Node* StartNode;
	Node* GoalNode;
	Node* currentNode;
	std::vector<Node> NodeGrid;
	std::vector<Node*> CLOSED;
	std::vector<Node*> OPEN;
	std::vector<Node*> Path;

	std::shared_ptr<Surface> screen;

	std::shared_ptr<Surface> image;
	std::shared_ptr<Surface> goalImage;
	std::shared_ptr<Surface> pathImage;
	std::shared_ptr<Surface> startImage;
	std::shared_ptr<Surface> closedImage;
	std::shared_ptr<Surface> openImage;
};

#endif