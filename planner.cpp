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

void Planner::listNodes() const{
    graph.listNodes();
}


//Fileok kezelése

void Planner::loadData(std::string filename){
    std::vector<std::string> input = file.readTXT(filename);
    if(input.empty()) return;

    std::string mode = "";

    for(std::string line: input){

        if(line.empty() || line[0] == '#'){
            continue;
        }

        if(line.find("[Pontok]") != std::string::npos){
            mode = "P";
            std::cout << "Pontok beolvasása folyamatban." << std::endl;
            continue;
        }

        if(line.find("[Vonalak]") != std::string::npos){
            mode = "V";
            std::cout << "Vonalak beolvasása folyamatban." << std::endl;
            continue;
        }

        std::stringstream ss(line);
        std::string i;                             //Input
        std::vector<std::string> iline;            //Input line

        while(std::getline(ss, i, ';')){
            iline.push_back(i);
        }

        try{
            if(mode == "P" && iline.size() >= 2){
                int id = std::stoi(iline[0]);
                graph.addNode(new Node(id, iline[1]));
            }
            else if(mode == "V" && iline.size() >= 5){
                int n1_id = std::stoi(iline[2]);
                int n2_id = std::stoi(iline[3]);
                double len = std::stod(iline[4]);

                Node* startnode = nullptr;
                Node* endnode = nullptr;

                for(Node* n : graph.getNodes()){
                    if(n->getId() == n1_id){startnode = n;}
                    if(n->getId() == n2_id){endnode = n;}
                }
                if(startnode && endnode){
                    graph.addEdge(startnode, endnode, iline[1], len);
                }
            }
        }catch(const std::exception& e){
            std::cerr << "Hiba sorbeolvasásbál" << e.what() << iline[0] << mode <<  std::endl;
            continue;
        }
    }
}

void Planner::saveData(std::string filename){
    std::vector<std::string> output;
    output.push_back("[Pontok]");
    output.push_back("# ID;Név");

    for(Node* n : graph.getNodes()){
        std::stringstream ss;
        ss << n->getId() << ";" << n->getName();
        output.push_back(ss.str()); 
    }

    output.push_back("[Vonalak]");
    output.push_back("# ID;Név;Honnan_ID;Hova_ID;Hossz(m)");

    for(Edge* e : graph.getEdges()){
        std::stringstream ss;
        ss << e->getId() << ";" << e->getName() << ";" << e->getNode1()->getId() << ";" << e->getNode2()->getId() << ";" << e->getLen();
        output.push_back(ss.str());
    }
    file.writeTXT(filename, output);
}