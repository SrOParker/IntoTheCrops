#pragma once
#include <vector>
#include <glm/vec2.hpp>
struct PathNode{
	
	PathNode(bool obs, float x, float z) : bObstacle{obs}, _x{x}, _z{z}{};
	bool  bObstacle = false;			    // Is the node an obstruction?
	bool  bVisited  = false;			    // Have we searched this node before?
	float fGlobalGoal{};					    // Distance to goal so far
	float fLocalGoal{};					    // Distance to goal if we took the alternative route
	float _x{};							    // Nodes position in 2D space (only x and z)
	float _z{};
	std::vector<PathNode*> vecNeighbours;	// Connections to neighbours
	PathNode* parent{};				    	// Node connecting to this node that offers shortest parent

};

struct PathA{

    PathNode* nodeStart{};
    PathNode* nodeEnd{};

    void  solve(std::vector<PathNode>&, glm::vec2 , glm::vec2);
    void  reset(std::vector<PathNode>&);
    float distance(float, float, float, float);
    float heuristic(PathNode *a, PathNode *b);
	PathNode* setUpPlace(glm::vec2, std::vector<PathNode>& world);
	glm::vec2 direction(float, float, float, float);

};