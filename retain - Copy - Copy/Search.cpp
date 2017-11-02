#include "Search.h"

Search::Search()
{
}

Search::~Search()
{
}

void Search::GetSearchInfo(std::vector<Node> NodeGrid, Node* StartNode, Node* GoalNode)
{
	this->NodeGrid = NodeGrid;
	this->GoalNode = GoalNode;
	this->StartNode = StartNode;

	OPEN.push_back(this->StartNode);


	//
	image = Surface::loadBmp("Images/node.bmp");
	goalImage = Surface::loadBmp("Images/goalNode.bmp");
	pathImage = Surface::loadBmp("Images/pathNode.bmp");
	startImage = Surface::loadBmp("Images/startNode.bmp");
	closedImage = Surface::loadBmp("Images/closedNode.bmp");
	openImage = Surface::loadBmp("Images/openNode.bmp");

	this->GoalNode->SetImage(goalImage);
	this->StartNode->SetImage(startImage);
}

void Search::Draw()
{
	for (size_t i = 0; i < NodeGrid.size(); i++)
	{
		NodeGrid.at(i).Draw(screen);
	}
	//draws our nodes
	screen->flip();
}

int Search::GoalReached()
{
	if (currentNode == GoalNode)
	{
		while (currentNode->GetParent() != NULL)
		{
			Path.push_back(currentNode);
			//we add our current node to our path vector

			currentNode = currentNode->GetParent();
			//then grab that nodes parents for our next loop iteration
		}
		return 1;
	}

	return 0;
}

void Search::GetNextNode()
{
	currentNode = OPEN.front();
}

void Search::IfInList(std::vector<Node*> List, Node* neighbourNode, bool* checked)
{
	for (int rat = 0; rat < List.size(); ++rat)
	{
		if (neighbourNode == List.at(rat))
		{
			*checked = true;
			break;
		}
	}
}

void Search::RemoveCurrentNodeFromOpen()
{
	int i = 0;
	while (currentNode != OPEN.at(i))
	{
		i++;
	}
	CLOSED.push_back(OPEN.at(i));
	OPEN.erase(OPEN.begin() + i);
}

std::vector<Node*> Search::InitialiseSearch()
{
	while (0 < OPEN.size())
	{
		GetNextNode();
		//we set this variable to be equal to the first value in OPEN

		if (GoalReached())
		{
			return Path;
		}
		//checks if we've reached the goal, if we have return Path

		else
		{
			for (int i = 0; i < currentNode->GetNeighbours().size(); i++)
			{
				bool checked = false;
				Node* neighbourNode = currentNode->GetNeighbours().at(i);

				IfInList(CLOSED, neighbourNode, &checked);
				IfInList(OPEN, neighbourNode, &checked);

				if (!checked)
				{
					SearchAlgorithm(i);
					neighbourNode->SetParent(currentNode);
					//this should add our current neighbour to OPEN but ONLY if its not present in OPEN||CLOSED, as well as parent all expanded nodes with our current node
				}
			}
			RemoveCurrentNodeFromOpen();


			for (int i = 0; i < OPEN.size(); i++)
			{
				OPEN.at(i)->SetImage(openImage);
			}
			for (int i = 0; i < CLOSED.size(); i++)
			{
				CLOSED.at(i)->SetImage(closedImage);
			}
			GoalNode->SetImage(goalImage);
			StartNode->SetImage(startImage);
			//these colour our nodes

			Draw();
			//these add our current node to closed, then removes it from open. We make sure we're dealing with current node by getting its position in open then dealing with that (for depth first as its no longer the first node)
		}
	}
	
	std::cout << "Program should not reached here, Search.cpp InitialiseSearch, after for loop" << std::endl;
}

void Search::SearchAlgorithm(int i)
{
	OPEN.push_back(currentNode->GetNeighbours().at(i));
}