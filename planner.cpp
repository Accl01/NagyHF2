#include "planner.h"

void Planner::routePlanner(const std::string& startName, const std::string& endName) const{
    Node* start = graph.findNodebyname(startName);
    Node* end = graph.findNodebyname(endName);

    std::vector<Node*> route;
    if(start != nullptr && end != nullptr){
        route = graph.findPath(start, end);
    }else{
        std::cout << "Az egyik pont nem található!!" << std::endl;
    }

    //Miutan megvan a legjobb utvonal itt kiírja és kiszamolja mennyi idő a timeofWalk al.

    printRoute(route);
    

}


void Planner::printRoute(std::vector<Node*> path) const{
    if(path.empty()){
        std::cout << "Nincs kiírható útvonal" << std::endl;
    }

    double length = 0;

    for(size_t i = 0; i < path.size() - 1; i++){
        Node* current = path[i];
        Node* after = path[i+1];

        std::vector<Edge*> connenctions = graph.getConnection(current);
        for(Edge* e : connenctions){
            if(e->getNode1() == after || e->getNode2() == after){
                length += e->getLen();
            }
        }
    }
    double time = timeofwalk(length);

    std::cout << "\nA leggyorsabb útvonal" << std::endl;
    std::cout << "Osszesen: " << length << "m, " << time << " perc" << std::endl;

    std::cout << " Az utvonal: " << std::endl;
    for(size_t i = 0; i < path.size(); ++i){
        std::cout << path[i]->getName() << std::endl;
    }
}


double Planner::timeofwalk(double len) const{
    double speed;
    switch(this->walkingSpeed){
        case 1:
            speed = 60; //Lassu
            break;

        case 2:
            speed = 80; //Kozepes
            break;

        case 3:
            speed = 100; //Gyors
            break;

        default:
            speed = 80;
            break;
    }
    return len / speed;
}