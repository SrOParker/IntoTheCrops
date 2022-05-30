#include "PathA.hpp"
#include <cmath>
#include <list>
#include <iostream>

float PathA::distance(float x1, float z1, float x2, float z2){
    
	return std::sqrt((x2-x1)*(x2-x1) + (z2-z1)*(z2-z1));
	
}

glm::vec2 PathA::direction(float x1, float z1, float x2, float z2){
	return {x2-x1, z2-z1};
}


float PathA::heuristic(PathNode* a, PathNode* b) {
    return distance(a->_x, a->_z, b->_x, b->_z);
}

PathNode* PathA::setUpPlace(glm::vec2 position, std::vector<PathNode>& world){
	PathNode* closest = &world[0];
	
	float cost = 99999;
	for(auto& a : world){
		float node_cost = distance(position.x, position.y, a._x, a._z);
		if(node_cost < 5 && cost > node_cost && !a.bObstacle){
			cost = node_cost;
			closest = &a;
		}
	}
	return closest;
}

void PathA::reset(std::vector<PathNode> &world){
	
    for(auto& i : world){
		i.bVisited = false;
		i.fGlobalGoal = 99999;
		i.fLocalGoal  = 99999;
		i.parent = nullptr;
    }
}

void PathA::solve(std::vector<PathNode>& world, glm::vec2 posenemy, glm::vec2 posplayer){
    //nodeStart = posicion actual de la IA
    //nodeEnd   = posicion actual del jugador

	reset(world);
	nodeStart = setUpPlace(posenemy, world);
	nodeEnd   = setUpPlace(posplayer, world);
	
	PathNode *nodeCurrent = nodeStart;
	nodeStart->fLocalGoal = 0.0f;
	nodeStart->fGlobalGoal = heuristic(nodeStart, nodeEnd);

    std::list<PathNode*> listNotTestedNodes; 
    listNotTestedNodes.push_back(nodeStart);

	//std::vector <glm::vec2> path;

		while (!listNotTestedNodes.empty() && nodeCurrent != nodeEnd)
		{
			listNotTestedNodes.sort([](const PathNode* lhs, const PathNode* rhs){ return lhs->fGlobalGoal < rhs->fGlobalGoal; } );
			
			while(!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
				listNotTestedNodes.pop_front();
			
			if (listNotTestedNodes.empty())
				break;

			nodeCurrent = listNotTestedNodes.front();
			nodeCurrent->bVisited = true;
			
			for (auto nodeNeighbour : nodeCurrent->vecNeighbours)
			{
                if (!nodeNeighbour->bVisited && nodeNeighbour->bObstacle == 0)
					listNotTestedNodes.push_back(nodeNeighbour);

				float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + distance(nodeCurrent->_x, nodeCurrent->_z, nodeNeighbour->_x, nodeNeighbour->_z);
				
				if (fPossiblyLowerGoal < nodeNeighbour->fLocalGoal)
				{
					//std::cout << direction(nodeCurrent->_x, nodeCurrent->_z, nodeNeighbour->_x, nodeNeighbour->_z).x << ":" << direction(nodeCurrent->_x, nodeCurrent->_z, nodeNeighbour->_x, nodeNeighbour->_z).y << "\n";
					
					nodeNeighbour->parent = nodeCurrent;
					nodeNeighbour->fLocalGoal = fPossiblyLowerGoal;
                	nodeNeighbour->fGlobalGoal = nodeNeighbour->fLocalGoal + heuristic(nodeNeighbour, nodeEnd);
					
				}
			}
		}
}
