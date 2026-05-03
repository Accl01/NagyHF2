#ifndef PLANNER_H
#define PLANNER_H

#include "graph.h"
#include "file.h"

class Planner {
    Graph graph;
    File file;
    int walkingSpeed;

public:
    Planner() : walkingSpeed(2){}

    void routePlanner(const std::string& startName, const std::string& endName) const;


    void setWalkingspeed(int speed) {
        if(speed == 1 || speed == 2 || speed == 3){
            walkingSpeed = speed;
        }
    }

    double timeofwalk(double len) const;

    void loadData(std::string filename);
    void saveData(std::string filename);

    void printRoute(std::vector<Node*> path) const;
};


#endif //PLANNER_H