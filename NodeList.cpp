#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){
    nodes = nullptr;
    length = 0;
}

NodeList::~NodeList(){
    if (length>0) {
        for (int i=0;i<length;i++){          
            delete nodes[i];                    
        }   
    }     
    delete[] nodes;
}

NodeList::NodeList(NodeList& other){
    nodes = nullptr;
    length = 0;

    for (int i=0; i<other.getLength(); i++) {
        this->addElement(new Node(*other.getNode(i)));
    }
}

int NodeList::getLength(){
    return length;
}

void NodeList::nodeListReverse() {
    //copy old node list to newNodes and delete the old nodes at the same time
    Node** newNodes = new Node*[length];
    for (int i=0; i< length; i++) {        
        newNodes[i] = new Node(*nodes[length - i - 1]);        
        delete nodes[length - i - 1];
    }
    delete[] nodes;

    // point old nodes to newNodes    
    nodes = newNodes;
    
}

void NodeList::addElement(Node* newPos){
    //copy old node list to newNodes and delete the old nodes at the same time
    Node** newNodes = new Node*[length+1];
    for (int i=0; i< length; i++) {        
        newNodes[i] = new Node(*nodes[i]);
        delete nodes[i];
    }
    delete[] nodes;

    // add new node and point old nodes to newNodes
    newNodes[length] = newPos;    
    nodes = newNodes;
    length +=1;
}

Node* NodeList::getNode(int i){
    if ((i>=0) && (i<length)){
        return nodes[i];
    }        
    else return nullptr;
}

int NodeList::findNode(int row, int col) {    
    for (int i=0; i<length; i++){
        if ((nodes[i]->getCol() == col) && (nodes[i]->getRow() == row)) {
            return i;
        }
    }    
    return NOT_IN_NODE_LIST;
}