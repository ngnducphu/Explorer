#include "Node.h"
#include <iostream>


Node::Node(int row, int col, int dist_traveled)
{
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled;
    this->direction = SYMBOL_EMPTY;
}

Node::~Node(){
    // nothing to delete since all is saved on the stack
}

Node::Node(Node& other) {
    this->col = other.getCol();
    this->row = other.getRow();
    this->dist_traveled = other.getDistanceTraveled();
    this->direction = other.getDirection();
}

int Node::getRow(){
    return row;
}

int Node::getCol(){
    return col;
}   

int Node::getDistanceTraveled(){
    return dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node* goal){
    //will write my own abs function when have time, using std::abs in the mean time
    return dist_traveled + std::abs((col - goal->getCol())) + std::abs((row - goal->getRow()));
}

void Node::setDirection(char direction) {
    this->direction = direction;
}

char Node::getDirection() {
    return direction;
}
    
//--------------------------------                             