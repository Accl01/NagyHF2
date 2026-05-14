#ifndef PLANNER_H
#define PLANNER_H

#include <sstream>

#include "memtrace.h"
#include "graph.h"
#include "file.h"

//Planner class (Main function class, with all func of the 'útvonaltervező')
class Planner {
    Graph graph;
    File file;
    int walkingSpeed;

public:
//Planner konstruktor
    Planner() : walkingSpeed(2){}

//Routre planner algorithm with the dijkstra on the planners graph
    void routePlanner(const std::string& startName, const std::string& endName) const;

//Walking speed setter
    void setWalkingspeed(int speed) {
        if(speed == 1 || speed == 2 || speed == 3){
            walkingSpeed = speed;
        }
    }

//Calculates the time to walk a distance with the planners speed
    double timeofwalk(double len) const;

//Lists all nodes of planners graph
    void listNodes() const;
    
//Adds new edges and nodes to planners graph
    void addNewNode(const std::string name);
    void addNewEdge(const std::string name, int n1_id, int n2_id, double len);

//Lodes and saves planners graph from and to a txt
    void loadData(std::string filename);
    void saveData(std::string filename);

//Prints the route that the routePlanner made
    void printRoute(std::vector<Node*> path) const;
};


#endif //PLANNER_H