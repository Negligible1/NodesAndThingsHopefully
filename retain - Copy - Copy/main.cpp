#include <SDL/SDL.h>
#undef main

#ifdef _MSC_VER
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Surface.h"
#include "Node.h"
#include "Search.h"

int main(int argc, char *argv[])
{
	std::shared_ptr<Surface> image;
	std::shared_ptr<Surface> goalImage;
	std::shared_ptr<Surface> pathImage;
	std::shared_ptr<Surface> startImage;
	std::shared_ptr<Surface> closedImage;
	std::shared_ptr<Surface> openImage;
	//makes a surface called image

	std::shared_ptr<Surface> screen;
	//makes a surface called screen

	SDL_Init(SDL_INIT_EVERYTHING);
	//initialise SDL

	screen = Surface::setVideoMode();
	
	image = Surface::loadBmp("Images/node.bmp");
	goalImage = Surface::loadBmp("Images/goalNode.bmp");
	pathImage = Surface::loadBmp("Images/pathNode.bmp");
	startImage = Surface::loadBmp("Images/startNode.bmp");
	closedImage = Surface::loadBmp("Images/closedNode.bmp");
	openImage = Surface::loadBmp("Images/openNode.bmp");
	//instantiates a bunch of images for us to use
	
	int imageHeight = 50;
	int imageWidth = 50;
	int noOfNodesW = 1280 / imageWidth;
	int noOfNodesH = 720 / imageHeight;
	//numbers control the number of nodes we'll make so that they don't go beyond the screens borders

	std::vector<Node> nodes;
	//generate a vector of our Node class

	for (size_t y = 0; y < noOfNodesH; y++)
	{
		for (size_t x = 0; x < noOfNodesW; x++)
		{
			Node node(image);
			//makes a node, passes in 'image' which is the nodes texture representation, also the x and y, which we'll use as the column and row, hence why we add 1 to each, so that 0 becomes 1 etc

			node.SetX(x*50);
			node.SetY(y*50);
			//x and y being effectively the grid points of our node, we times that by 50 (which is the size of the image) to determine the x and y coordinate position to draw our image

			nodes.push_back(node);
			//pushes our newly defined class into the vector
		}
	}
	//this makes our grid of nodes

	int i = 0;
	
	for (size_t y = 0; y < noOfNodesH; y++)
	{
		for (size_t x = 0; x < noOfNodesW; x++, i++)
		{
			Node* thisnode = &nodes.at(i);

			if (x == 0) //left boundary
			{
				thisnode->AddNeighbour(thisnode + 1);
			}
			else if (x == noOfNodesW - 1) //right boundary
			{
				thisnode->AddNeighbour(thisnode - 1);
			}
			else
			{
				thisnode->AddNeighbour(thisnode + 1);
				thisnode->AddNeighbour(thisnode - 1);
			}

			if (y == 0)	//top boundary
			{
				thisnode->AddNeighbour(thisnode + noOfNodesW);
			}
			else if (y == noOfNodesH - 1) //bottom boundary
			{
				thisnode->AddNeighbour(thisnode - noOfNodesW);
				
			}
			else //no boundary
			{
				thisnode->AddNeighbour(thisnode + noOfNodesW);
				thisnode->AddNeighbour(thisnode - noOfNodesW);
			}

			//Diagonals
			if (y == 0) //top boundary
			{
				if (x == 0) //left boundary
				{
					thisnode->AddNeighbour(thisnode + noOfNodesW + 1); //bottom right node
				}
				else if (x == noOfNodesW - 1) //right boundary
				{
					thisnode->AddNeighbour(thisnode + noOfNodesW - 1); //bottom left node
				}
				else
				{
					thisnode->AddNeighbour(thisnode + noOfNodesW - 1); //bottom left node
					thisnode->AddNeighbour(thisnode + noOfNodesW + 1); //bottom right node
				}
			}
			else if (y == noOfNodesH - 1) //bottom boundary
			{
				if (x == 0) //left boundary
				{
					thisnode->AddNeighbour(thisnode - noOfNodesW + 1); //top right node
				}
				else if (x == noOfNodesW - 1) //right boundary
				{
					thisnode->AddNeighbour(thisnode - noOfNodesW - 1); //top left node
				}
				else
				{
					thisnode->AddNeighbour(thisnode - noOfNodesW - 1); //top left node
					thisnode->AddNeighbour(thisnode - noOfNodesW + 1); //top right node
				}
			}
			else if (x == 0) //left boundary
			{
				thisnode->AddNeighbour(thisnode - noOfNodesW + 1); //top right node
				thisnode->AddNeighbour(thisnode + noOfNodesW + 1); //bottom right node
			}
			else if (x == noOfNodesW - 1) //right boundary
			{
				thisnode->AddNeighbour(thisnode - noOfNodesW - 1); //top left node
				thisnode->AddNeighbour(thisnode + noOfNodesW - 1); //bottom left node
			}
			else //no boundary
			{
				thisnode->AddNeighbour(thisnode + noOfNodesW - 1); //bottom left node
				thisnode->AddNeighbour(thisnode + noOfNodesW + 1); //bottom right node
				thisnode->AddNeighbour(thisnode - noOfNodesW - 1); //top left node
				thisnode->AddNeighbour(thisnode - noOfNodesW + 1); //top right node
			}
		}
	}
	//gives all our nodes neighbours

	Node* StartNode;
	Node* GoalNode;
	StartNode = &nodes.at(268);
	GoalNode = &nodes.at(100);
	//provides us with a start and goal node, for testing purposes

	
	Search searching;

	searching.ForDrawing(screen);
	searching.GetSearchInfo(nodes, StartNode, GoalNode);
	std::vector<Node*>Path = searching.InitialiseSearch();
	/**/
	/*
	std::vector<Node*> CLOSED;
	std::vector<Node*> OPEN;
	std::vector<Node*> Path;	

	OPEN.push_back(StartNode);
	
	bool GoalReached = false;

	for (int it = 0; it != nodes.size(); ++it) //this'll iterate us through our vector
	{
		if (OPEN.empty())
		{
			break;
		}
		//breaks us from the loop if open is empty, no path availible

		Node* currentNode = OPEN.front();
		//we set this variable to be equal to the first value in OPEN

		
		for (size_t i = 1; i < OPEN.size(); i++)
		{
			//if ((currentNode->GetestValueToGoal() + currentNode->GetrealValueToStart()) > (OPEN.at(i)->GetestValueToGoal() + OPEN.at(i)->GetrealValueToStart())) //A*
			if (currentNode->GetestValueToGoal() > OPEN.at(i)->GetestValueToGoal()) //Greedy Best First
			{
				currentNode = OPEN.at(i);
			}
		}
		//Greedy and A*, different IF statements for each
		

		if (currentNode == GoalNode)
		{
			GoalReached = true;
			while (currentNode->GetParent() != NULL)
			{
				Path.push_back(currentNode);
				//we add our current node to our path vector

				currentNode = currentNode->GetParent();
				//then grab that nodes parents for our next loop iteration
			}
			break;
		}
		//checks if we've reached the goal, if we have breaks us out of the loop

		else
		{

			for (int i = 0; i < currentNode->GetNeighbours().size(); i++)
			{
				bool checked = false;
				Node* neighbourNode = currentNode->GetNeighbours().at(i);

				for (int rat = 0; rat < CLOSED.size(); ++rat)
				{
					if (neighbourNode == CLOSED.at(rat))
					{
						checked = true;
						break;
					}
				}//checks if the neighbour we're examining is in CLOSED

				for (int rat = 0; rat < OPEN.size(); ++rat)
				{
					if (neighbourNode == OPEN.at(rat))
					{
						checked = true;
						break;
					}
				}//or in OPEN

				if (!checked)
				{
					int xToGoal = neighbourNode->GetX() - GoalNode->GetX();
					int yToGoal = neighbourNode->GetY() - GoalNode->GetY();
					if (xToGoal < 0)
					{
						xToGoal = 0 - xToGoal;
					}
					if (yToGoal < 0)
					{
						yToGoal = 0 - yToGoal;
					}

					neighbourNode->SetestValueToGoal(xToGoal + yToGoal);

					int xToStart = neighbourNode->GetX() - StartNode->GetX();
					int yToStart = neighbourNode->GetY() - StartNode->GetY();
					if (xToStart < 0)
					{
						xToStart = 0 - xToStart;
					}
					if (yToStart < 0)
					{
						yToStart = 0 - yToStart;
					}

					neighbourNode->SetrealValueToStart(xToStart + yToStart);

					//OPEN.insert(OPEN.begin(), neighbourNode);
					//DEPTH FIRST
					OPEN.push_back(neighbourNode);
					//BREADTH FIRST, ALSO NEEDED FOR A* AND GREEDY

					neighbourNode->SetParent(currentNode);
					//this should add our currently neighbour to OPEN but ONLY if its not present in CLOSED, as well as parent all expanded nodes with our current node
				}
			}

			int i = 0;
			while (currentNode != OPEN.at(i))
			{
				i++;
			}
			CLOSED.push_back(OPEN.at(i));
			OPEN.erase(OPEN.begin() + i);
			//these add our current node to closed, then removes it from open. We make sure we're dealing with current node by getting its position in open then dealing with that (for depth first as its no longer the first node)
		}
		

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

		for (size_t i = 0; i < nodes.size(); i++)
		{
			nodes.at(i).Draw(screen);
		}
		//draws our nodes
		screen->flip();
	}
	
	if (GoalReached)
	{
		std::cout << "Path avaliable" << std::endl;
	}
	else
	{
		std::cout << "No path availible" << std::endl;
	}
	//just debug console messages
	/**/


	for (int i = 0; i < Path.size(); i++)
	{
		Path.at(i)->SetImage(pathImage);
	}

	GoalNode->SetImage(goalImage);
	StartNode->SetImage(startImage);
	//replaces the image of the start and goal node, we do this last because they may be in the path

	for (size_t i = 0; i < nodes.size(); i++)
	{
		nodes.at(i).Draw(screen);
	}
	//draws our nodes

	screen->flip();
	//draws our screen
	
#ifdef _MSC_VER
	Sleep(3000);
#else
	sleep(3);
#endif
	
	return 0;
}
