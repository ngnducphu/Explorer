#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver(){
    // TODO
    nodesExplored = new NodeList();
}

PathSolver::~PathSolver(){
    // TODO
    delete nodesExplored;
}

Node* PathSolver::selectNode(NodeList* p, NodeList* c, Node* goal) {
    //initialize
    Node* currentPos = nullptr;
    int min_distance = ENV_DIM * ENV_DIM;

    //select node in p with min distance and not in c
    for (int i=0; i<p->getLength();i++) {
        int estimatedDist2Goal = p->getNode(i)->getEstimatedDist2Goal(goal) + p->getNode(i)->getDistanceTraveled();
        if ( (estimatedDist2Goal<min_distance)  && (c->findNode(p->getNode(i)->getRow(), p->getNode(i)->getCol())==NOT_IN_NODE_LIST) ) {
            min_distance = estimatedDist2Goal;
            currentPos = p->getNode(i);
        }
    }
    
    return currentPos;
}

Node* PathSolver::selectNode(NodeList* p, NodeList* c, Node* goal, int minDistanceThreshold) {
    //initialize
    Node* currentPos = nullptr;
    int min_distance = minDistanceThreshold;

    //select node in p with min distance and not in c
    for (int i=0; i<p->getLength();i++) {
        //std::cout << p->getNode(i)->getRow() << " " << p->getNode(i)->getCol() << std::endl;
        int estimatedDist2Goal = p->getNode(i)->getEstimatedDist2Goal(goal) + p->getNode(i)->getDistanceTraveled();
        if ( (estimatedDist2Goal<min_distance)  && (c->findNode(p->getNode(i)->getRow(), p->getNode(i)->getCol())==NOT_IN_NODE_LIST) ) {
            min_distance = estimatedDist2Goal;
            currentPos = p->getNode(i);
        }
    }
    
    return currentPos;
}

void PathSolver::exploreSurroundingNodes(NodeList* p, Node* node, Env env) {
    int col = node->getCol();
    int row = node->getRow();
    int currentDistance = node->getDistanceTraveled();

    for (int i=0; i < DIRECTION_NO; i++) {

        int newCol = col + COL_SHIFT[i];
        int newRow = row + ROW_SHIFT[i];     
        
        if ((env[newRow][newCol]!=SYMBOL_WALL) && (p->findNode(newRow, newCol)==NOT_IN_NODE_LIST)) {   
            Node* newNode = new Node(newRow, newCol, currentDistance + 1);            
            p->addElement(newNode);
        }

    }
    
}

Node* PathSolver::findPos(Env env, char c) {
    Node* node = nullptr;
    for (int i=0;i<ENV_DIM;i++) {
        for (int j=0;j<ENV_DIM;j++) {
            if (env[i][j] == c) {
                node = new Node(i, j, 0);                
                return node;
            }
        }
    }

    return node;
}

void PathSolver::forwardSearch(Env env){
    // TODO 
    
    // Get G - goal position
    Node* goal = findPos(env, SYMBOL_GOAL);

    // Get S - starting position
    Node* start = findPos(env, SYMBOL_START);
    
    // Current Position
    Node* currentPos = nullptr;
    
    // initiate P with S in it
    NodeList* openList = new NodeList();
    openList->addElement(new Node(*start));    


    // start exploring until see the goal
    do
    {
        currentPos = selectNode(openList, nodesExplored, goal);       
        
        exploreSurroundingNodes(openList,currentPos,env);

        nodesExplored->addElement(new Node(*currentPos));

    }
    while ((currentPos->getCol() != goal->getCol()) || (currentPos->getRow() != goal->getRow()));

    
    delete goal;    
    delete start;            
    delete openList;
    

}


Node* PathSolver::findPos(Env env, int rows, int cols, char c) {
    Node* node = nullptr;
    for (int i=0;i<rows;i++) {
        for (int j=0;j<cols;j++) {
            if (env[i][j] == c) {
                node = new Node(i, j, 0);                
                return node;
            }
        }
    }

    return node;
}


void PathSolver::forwardSearch(Env env, int rows, int cols){
    // TODO 
    // Get G - goal position
    
    Node* goal = findPos(env, rows, cols, SYMBOL_GOAL);
    
    
    // Get S - starting position
    Node* start = findPos(env, rows, cols, SYMBOL_START);
    
    
    // Current Position (should be nullptr but need sthing to delete when go in the do while loop so ..., probably need better implementation if have time to fix)
    Node* currentPos = new Node(*start);
    

    // initiate P with S in it
    NodeList* openList = new NodeList();
    openList->addElement(new Node(*start));    
    
    

    // start exploring until see the goal (also since we assumed always find a path from S to G so the while condition is like this, better have a safety condition just in case, implement when have time)
    do
    {
        delete currentPos;
        
        currentPos = new Node(*selectNode(openList, nodesExplored, goal, rows * cols));       
        
        exploreSurroundingNodes(openList,currentPos,env);
        
        nodesExplored->addElement(new Node(*currentPos));
        
                
    }
    while ((currentPos->getCol() != goal->getCol()) || (currentPos->getRow() != goal->getRow()));

    
    delete goal;    
    delete start;   
    delete openList;
    delete currentPos;

}

NodeList* PathSolver::getNodesExplored(){
    //TODO    
    return new NodeList(*nodesExplored);
}

void PathSolver::backTracking(Env env, NodeList* path, Node* currentPosition) {
    int row = currentPosition->getRow();
    int col = currentPosition->getCol();
    
    //maybe change to do while loop instead of using return this much.
    //loop through the 4 direction the robot can move to determine the previous position, as well as the direction.
    for (int i = 0; i<DIRECTION_NO; i++) {
        int newRow = row + ROW_SHIFT[i];
        int newCol = col + COL_SHIFT[i];
        if (nodesExplored->findNode(newRow, newCol)!=NOT_IN_NODE_LIST) {
            Node* newNode = nodesExplored->getNode(nodesExplored->findNode(newRow, newCol));
            if (newNode->getDistanceTraveled() + 1 == currentPosition->getDistanceTraveled()) {
                if (env[newRow][newCol] == SYMBOL_START) {
                    newNode->setDirection(SYMBOL_START);
                    path->addElement(new Node(*newNode));
                    return;   
                }                
                
                newNode->setDirection(DICRECTIONS[i]);
                path->addElement(new Node(*newNode));
                backTracking(env, path, newNode);
                return;
            }
        }
    }
}

NodeList* PathSolver::getPath(Env env){
    // TODO
    for (int i = 0; i<nodesExplored->getLength(); i++){
        int row = nodesExplored->getNode(i)->getRow();
        int col = nodesExplored->getNode(i)->getCol();

        //find the goal node
        if (env[row][col] == SYMBOL_GOAL) {
            //initiate path
            NodeList* path = new NodeList();

            //add goal node to the start of the the path
            Node* goal = new Node(*nodesExplored->getNode(i));
            goal->setDirection(SYMBOL_GOAL);
            path->addElement(goal);

            //start backtracking
            backTracking(env, path, goal);

            //reverse
            path->nodeListReverse();

            return path;
        }
    }
    return nullptr;
}



//-----------------------------