#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input. - added env size as argument for milestone 4
Env readEnvStdin(int* rows, int* cols);

/*
 * This function is to help you delete a 
 * dynamically allocated 2D Environment.
 */
void delete_env(Env env, int rows, int cols);

/*
 * This function is to help you dynamically allocate
 *  memory for a generic 2D Environemnt.
 */
Env make_env(const int rows, const int cols);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3 - added env size as argument for milestone 4
void printEnvStdout(Env env, NodeList* solution, int* rows, int* cols);


int main(int argc, char** argv){
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!

    /*
    std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    testNode();
    testNodeList();
    std::cout << "DONE TESTING" << std::endl << std::endl;
    */

    // Load Environment 
    
    // row count of the env
    int* rows = new int(0);
    // col count of the env
    int* cols = new int(0);
    
    Env env = readEnvStdin(rows, cols);


    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    
    
    PathSolver* pathSolver = new PathSolver();    
    
    pathSolver->forwardSearch(env, *rows, *cols);

    NodeList* exploredPositions = nullptr;
    
    exploredPositions = pathSolver->getNodesExplored();
    
    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathSolver->getPath(env);    
    
    printEnvStdout(env, solution, rows, cols);
    
    
    delete pathSolver;        
    delete exploredPositions;
    delete solution;
    delete_env(env, *rows, *cols);
    delete rows;
    delete cols;    
    
}

Env make_env(const int rows, const int cols) {
   Env env = nullptr;

   if (rows >= 0 && cols >= 0) {
      env = new char*[rows];
      for (int i = 0; i != rows; ++i) {
         env[i] = new char[cols];
      }
   }

   return env;
}

void delete_env(Env env, int rows, int cols) {
   if (rows >= 0 && cols >= 0) {
      for (int i = 0; i != rows; ++i) {
         delete env[i];
      }
      delete[] env;
   }
   return;
}

Env readEnvStdin(int* rows, int* cols) {
    //TODO
    //read file
    *rows = 0;
    Env env = nullptr;
    std::string oneLine;
    while (!std::cin.eof()) {        
        std::cin >> oneLine;
        *cols = oneLine.length();

        //copy old env to newEnv
        Env newEnv = make_env(*rows+1, *cols);
        for (int i=0; i<*rows; i++) {
            for (int j=0; j<*cols; j++) {
                newEnv[i][j] = env[i][j];
            }
        }

        // delete old env
        delete_env(env, *rows, *cols);

        // point old env to new env
        env = newEnv;

        // add the newline just read to the env
        for (int j=0; j<*cols; j++) {            
            env[*rows][j] = oneLine[j];                                    
        }                
        *rows += 1;

    }  
    
    return env;
}

void printEnvStdout(Env env, NodeList* solution, int* rows, int* cols) {
    //TODO
    // change the env to reflect the robot moves
    for (int i=0; i<solution->getLength(); i++) {
        env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = solution->getNode(i)->getDirection();    
    }

    // print env
    for (int i=0;i<*rows;i++) {        
        for ( int j=0;j<*cols;j++) {    
            std::cout << env[i][j];
        }

        if (i!=*rows-1) {
            std::cout<<std::endl;
        }
    }
}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}