#ifndef COSC_ASSIGN_ONE_PATHSOLVER
#define COSC_ASSIGN_ONE_PATHSOLVER 

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathSolver{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Destructor
    PathSolver();
    ~PathSolver();

    // Execute forward search algorithm
    // To be implemented for Milestone 2
    void forwardSearch(Env env);

    // Get a DEEP COPY of the explored NodeList in forward search
    // To be implemented for Milestone 2
    NodeList* getNodesExplored();

    // Execute backtracking and Get a DEEP COPY of the path the 
    // robot should travel
    // To be implemented for Milestone 3
    NodeList* getPath(Env env);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

    void forwardSearch(Env env, int rows, int cols);

private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    // Nodes explored in forward search algorithm
    NodeList* nodesExplored;

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */
    
    //Select the node p from the open-list P that has the smallest estimated distance
    //to goal and, is not in the closed-list C
    Node* selectNode(NodeList* p, NodeList* c, Node* goal);

    //Select the node p from the open-list P that has the smallest estimated distance
    //to goal and, is not in the closed-list C
    Node* selectNode(NodeList* p, NodeList* c, Node* goal, int minDistanceThreshold);

    //Return the node contain the position in the env that has the character C
    Node* findPos(Env env, char c);
    //Return the node contain the position in the env that has the character C using dynamic array for env
    Node* findPos(Env env, int rows, int cols, char c);

    //Go to each position q that can be reached from p and do stuff
    void exploreSurroundingNodes(NodeList* p, Node* node, Env env);


    //recursively back tracking from goal to start to get the robot travel path
    void backTracking(Env env, NodeList* path, Node* currentPosition);


    // column shift when move in a certain direction in maze
    const int COL_SHIFT[DIRECTION_NO] = { -1, 1, 0, 0 };

    // row shift when move in a certain direction in maze
    const int ROW_SHIFT[DIRECTION_NO] = { 0, 0, -1, 1 };

    // direction in maze in reverse since we are backtracking
    const char DICRECTIONS[DIRECTION_NO] = {SYMBOL_RIGHT, SYMBOL_LEFT, SYMBOL_DOWN, SYMBOL_UP};
    
};




#endif //COSC_ASSIGN_ONE_PATHSOLVER